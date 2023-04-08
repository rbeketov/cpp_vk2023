#include <iostream>
#include "pars_expression.h"

const int kSizeOfPassedExpression = 2;
const std::string kErrorMessageSizeExp = "Invalid number of arguments passed";

int main(int argc, char* argv[]) {
    if (argc != kSizeOfPassedExpression) {
        std::cerr << kErrorMessageSizeExp << std::endl;
        return 1;
    }

    try {
        auto expression = parsePassedExpressionToCalc(argv[argc - 1]);
        std::cout << expression->calculate() << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}