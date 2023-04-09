#include <iostream>
#include <exception>
#include "pars_expression.h"
#include "exception.h"

const int SIZE_OF_PASSED_EXPRESSION = 2;
const std::string ERROR_MESSAGE_SIZE_EXP = "Invalid number of arguments passed";
const std::string ERROR_MESSAGE_INCORRECTLY_NUMB = "Number entered incorrectly";

int main(int argc, char* argv[]) {
    if (argc != SIZE_OF_PASSED_EXPRESSION) {
        std::cerr << ERROR_MESSAGE_SIZE_EXP << std::endl;
        return 1;
    }

    try {
        auto expression = parsePassedExpressionToCalc(argv[argc - 1]);
        std::cout << expression->calculate() << std::endl;
    } catch (calculator::CalculatorException &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (std::invalid_argument&) {
        std::cerr << ERROR_MESSAGE_INCORRECTLY_NUMB << std::endl;
        return 1;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}