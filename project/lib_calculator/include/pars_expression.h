#pragma once

#include "calculator.h"
#include <vector>
#include <iterator>

using stringIter = std::string::const_iterator;


calculator::ptrToICalc parsePassedExpressionToCalc(const char* buffer);

bool checkValidBracket(std::vector<std::string>& tokens);
bool intoBracketsNotNull(std::vector<std::string>& tokens);

size_t findTokenLowestPriority(std::vector<std::string>& tokens);
std::vector<std::string> stringSplitToToken(const std::string& expression);

calculator::ptrToUnary createCalcNodeUnary(std::string& token);
calculator::ptrToBinary createCalcNodeBinary(std::string& token);


calculator::ptrToICalc parseTokensToCalc(std::vector<std::string>& tokens);