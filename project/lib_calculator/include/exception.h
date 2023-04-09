#pragma once // NOLINT

#include <stdexcept>
#include <string>

namespace calculator {

class CalculatorException: public std::runtime_error {
 public:
  explicit CalculatorException(const std::string& msg)
      : std::runtime_error(msg) {}
};

class InvalidMathFuncScope: public CalculatorException {
 public:
  explicit InvalidMathFuncScope(const std::string& mathFunc)
      : CalculatorException("The scope of the function " + mathFunc + " definition is violated") {}
};

class InvalidCalcNode: public CalculatorException {
 public:
    InvalidCalcNode()
      : CalculatorException("Node have nullptr. Calculate impossible") {}
};

class InvalidToken: public CalculatorException {
 public:
    explicit InvalidToken(const std::string& token)
      : CalculatorException("Invalid token \"" + token + "\"") {}
};

class InvalidExpression: public CalculatorException {
 public:
    InvalidExpression()
      : CalculatorException("Invalid expression") {}
};


}  // namespace calculator