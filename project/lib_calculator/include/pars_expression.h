#pragma once

#include "calculator.h"
#include <vector>
#include <iterator>

using stringIter = std::string::const_iterator;

// main function
calculator::ptrToICalc parsePassedExpressionToCalc(const char* buffer);

//

size_t findTokenLowestPriority(std::vector<std::string>& tokens);
std::vector<std::string> stringSplitToToken(const std::string& expression);

calculator::ptrToUnary createCalcNodeUnary(std::string& token);
calculator::ptrToBinary createCalcNodeBinary(std::string& token);


calculator::ptrToICalc parseTokensToCalc(std::vector<std::string>& tokens);