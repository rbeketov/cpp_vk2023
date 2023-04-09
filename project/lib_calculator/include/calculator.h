#pragma once

#include <memory>
#include <string>

namespace calculator {

class ICalculatable;
class UnaryOperator;
class BinaryOperator;

using ptrToICalc = std::unique_ptr<ICalculatable>;
using ptrToBinary = std::unique_ptr<BinaryOperator>;
using ptrToUnary = std::unique_ptr<UnaryOperator>;

class ICalculatable {
 public:
  virtual ~ICalculatable() {};
  virtual double calculate() = 0;
};

class UnaryOperator: public ICalculatable {
 public:
   void setValue(ptrToICalc&& value);
 protected:
   ptrToICalc value_;
};

class BinaryOperator: public ICalculatable {
 public:
  void setLeft(ptrToICalc&& leftValue);
  void setRight(ptrToICalc&& rightValue);
 protected:
  ptrToICalc leftValue_;
  ptrToICalc rightValue_;
};


class Expression: public ICalculatable {
 public:
  explicit Expression(std::string& value);
  double calculate() override;
 private:
  double value_;
};

class OperatorPlus: public BinaryOperator {
 public:
  double calculate() override;
};

class OperatorMinus: public BinaryOperator {
 public:
  double calculate() override;
};

class OperatorMultiply: public BinaryOperator {
 public:
  double calculate() override;
};

class OperatorAsin: public UnaryOperator {
 public:
  double calculate() override;
};

class OperatorAcos: public UnaryOperator {
 public:
  double calculate() override;
};

}  // namespace calculator