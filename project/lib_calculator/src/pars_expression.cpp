#include "pars_expression.h"


#include <exception>
#include <iostream>
#include <unordered_map>
#include <numeric>
#include <cstring>

const std::string ASIN_TOKEN = "asin";
const std::string ACOS_TOKEN = "acos"; 
const std::string POINT_TOKEN = ".";
const std::string OPEN_BRACKET_TOKEN = "(";
const std::string CLOSE_BRACKET_TOKEN = ")";
const std::string MULTIPLY_TOKEN = "*";
const std::string MINUS_TOKEN = "-";
const std::string PLUS_TOKEN = "+";
const std::string ZERO_NUMBER_TOKEN = "0";
const std::string NINE_NUMBER_TOKEN = "9";
const size_t SIZE_TOKEN_TRIGFUNC = 4;
const size_t FIRST_PRIORITY = 1;
const size_t SECOND_PRIORITY = 2;
const size_t THIRD_PRIORITY = 3;
const size_t SIZE_SIMPLE_TOKEN = 1;
const std::string INVALID_EXPRESSION = "Invalid expression";
const std::string INVALID_TOKEN = "Invalid token";


std::unordered_map<std::string, size_t> Priority{{ASIN_TOKEN, FIRST_PRIORITY},
                                                 {ACOS_TOKEN, FIRST_PRIORITY},
                                                 {MULTIPLY_TOKEN, SECOND_PRIORITY},
                                                 {PLUS_TOKEN, THIRD_PRIORITY},
                                                 {MINUS_TOKEN, THIRD_PRIORITY}};


calculator::ptrToICalc parsePassedExpressionToCalc(const char* buffer) {
    std::string expression(buffer);

    auto tokens = stringSplitToToken(expression);

    if (!checkValidBracket(tokens)) {
        throw std::runtime_error(INVALID_EXPRESSION);
    }

    auto result = parseTokensToCalc(tokens);
    return result;
}


auto checkSimpleToken = [](const char* value) {
    return std::string(value, SIZE_SIMPLE_TOKEN) == MULTIPLY_TOKEN ||
           std::string(value, SIZE_SIMPLE_TOKEN) == PLUS_TOKEN ||
           std::string(value, SIZE_SIMPLE_TOKEN) == MINUS_TOKEN ||
           std::string(value, SIZE_SIMPLE_TOKEN) == POINT_TOKEN ||
           std::string(value, SIZE_SIMPLE_TOKEN) == OPEN_BRACKET_TOKEN ||
           std::string(value, SIZE_SIMPLE_TOKEN) == CLOSE_BRACKET_TOKEN ||
           (ZERO_NUMBER_TOKEN <= std::string(value, SIZE_SIMPLE_TOKEN) && std::string(value, SIZE_SIMPLE_TOKEN) <= NINE_NUMBER_TOKEN);
};

auto checkCompositeToken = [](stringIter& iterCurr, stringIter& iterEnd, std::vector<std::string>& tokens) {
    if (iterCurr+SIZE_TOKEN_TRIGFUNC > iterEnd) {
        return false;
    }
    std::string buffer(iterCurr, iterCurr+SIZE_TOKEN_TRIGFUNC);
    if (buffer != ASIN_TOKEN && buffer != ACOS_TOKEN) {
        return false;
    }
    tokens.push_back(buffer);
    iterCurr += SIZE_TOKEN_TRIGFUNC;
    return true;
};

std::vector<std::string> stringSplitToToken(const std::string& expression) {
    std::vector<std::string> tokens;
    auto it = expression.begin();
    auto iterEndOfExpression = expression.end();
    while(it != iterEndOfExpression) {
        if (!checkSimpleToken(&(*it))) {
            if (!checkCompositeToken(it, iterEndOfExpression, tokens)) {
                throw std::runtime_error(INVALID_TOKEN);
            }
        }
        tokens.push_back({*it});
        it++;
    }
    return tokens;
}


bool checkValidBracket(std::vector<std::string>& tokens) {
    int counterBracket = 0;
    for (auto it : tokens) {
        if (it == OPEN_BRACKET_TOKEN) {
            counterBracket++;
        } else if (it == CLOSE_BRACKET_TOKEN) {
            counterBracket--;
        }
        if (counterBracket < 0) {
            return false;
        }
    }
    if (counterBracket) {
        return false;
    }
    return true;
}

size_t findTokenLowestPriority(std::vector<std::string>& tokens) {
    size_t lowestPriority = FIRST_PRIORITY;
    bool foundBracket = false;
    size_t resultPos = 0;
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i] == OPEN_BRACKET_TOKEN) {
            foundBracket = true;
            continue;
        }
        if (tokens[i] == CLOSE_BRACKET_TOKEN) {
            foundBracket = false;
            continue;
        }
        if (!foundBracket && (tokens[i] == MULTIPLY_TOKEN ||
                              tokens[i] == MINUS_TOKEN || 
                              tokens[i] == PLUS_TOKEN ||
                              tokens[i] == ASIN_TOKEN ||
                              tokens[i] == ACOS_TOKEN) && Priority[tokens[i]] >= lowestPriority) {
            resultPos = i;
            lowestPriority = Priority[tokens[i]];
        }
    }
    return resultPos;
}

calculator::ptrToICalc createCalcNode(std::string& token) {
    if (token == MINUS_TOKEN) {
        return std::make_unique<calculator::OperatorMinus>(calculator::OperatorMinus());
    }
    if (token == PLUS_TOKEN) {
        return std::make_unique<calculator::OperatorPlus>(calculator::OperatorPlus());
    }
    if (token == ASIN_TOKEN) {
        return std::make_unique<calculator::OperatorAsin>(calculator::OperatorAsin());
    }
    if (token == ACOS_TOKEN) {
        return std::make_unique<calculator::OperatorAcos>(calculator::OperatorAcos());
    }
    if (token == MULTIPLY_TOKEN) {
        return std::make_unique<calculator::OperatorMultiply>(calculator::OperatorMultiply());
    }
    return std::make_unique<calculator::Expression>(calculator::Expression(token));
}



calculator::ptrToICalc parseTokensToCalc(std::vector<std::string>& tokens) {
    size_t currPos = findTokenLowestPriority(tokens);
    if (!currPos && *tokens.begin() == OPEN_BRACKET_TOKEN) {
        tokens.erase(tokens.begin());
        tokens.erase(tokens.end());
        if (!checkValidBracket(tokens)) {
            throw std::runtime_error(INVALID_EXPRESSION);
        }
        currPos = findTokenLowestPriority(tokens);
    }

    if (!currPos) {
        std::string resultExpression = std::accumulate(tokens.begin() + 1, tokens.end(), *tokens.begin());
        auto result = createCalcNode(resultExpression);
        return result;
    }
    auto result = createCalcNode(tokens[currPos]);
    if (tokens[currPos] == ASIN_TOKEN || tokens[currPos] == ACOS_TOKEN) {
        std::vector<std::string> stepTokens{tokens.begin()+currPos + 1, tokens.end()};
        result->setValue(parseTokensToCalc(stepTokens));
    } else {
        std::vector<std::string> stepTokensLeft{tokens.begin(), tokens.begin() + currPos - 1};
        result->setLeft(parseTokensToCalc(stepTokensLeft));
        std::vector<std::string> stepTokensRight{tokens.begin() + currPos + 1, tokens.end()};
        result->setRight(parseTokensToCalc(stepTokensRight));
    }
    return result;
}





// bool intoBracketsNotNull(std::vector<std::string>& tokens) {
//     int counterExpressions = 0;
//     for (auto it : tokens) {
//         if (*it.c_str() == OPEN_BRACKET_TOKEN) {
//             counterExpressions++;
//         } else if (counterExpressions != 0 && 
//                    ZERO_NUMBER_TOKEN <= *it.c_str() && *it.c_str() <= NINE_NUMBER_TOKEN) {
//             counterExpressions--;
//         } else if (*it.c_str() == CLOSE_BRACKET_TOKEN) {

//         }
//     }
//     if (counterExpressions) {
//         return false;
//     }
//     return true;
// } // (1)



