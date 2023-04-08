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
  virtual ~UnaryOperator() {};
  virtual void setValue(ptrToICalc&& value);
 private:
   ptrToICalc value_;
};

class BinaryOperator: public ICalculatable {
 public:
  virtual ~BinaryOperator() {};
  virtual void setLeft(ptrToICalc&& leftValue);
  virtual void setRight(ptrToICalc&& rightValue);
 private:
  ptrToICalc leftValue_;
  ptrToICalc rightValue_;
};


class Expression: public ICalculatable {
 public:
  Expression();
  explicit Expression(std::string& value);
  double calculate() override;
 private:
  double value_;
};

class OperatorPlus: public BinaryOperator {
 public:
  using BinaryOperator::setLeft;
  using BinaryOperator::setRight;
  double calculate() override;
 private:
  ptrToICalc leftValue_;
  ptrToICalc rightValue_;
};

class OperatorMinus: public BinaryOperator {
 public:
  using BinaryOperator::setLeft;
  using BinaryOperator::setRight;
  double calculate() override;
 private:
  ptrToICalc leftValue_;
  ptrToICalc rightValue_;
};

class OperatorMultiply: public BinaryOperator {
 public:
  using BinaryOperator::setLeft;
  using BinaryOperator::setRight;
  double calculate() override;
 private:
  ptrToICalc leftValue_;
  ptrToICalc rightValue_;
};


class OperatorAsin: public UnaryOperator {
 public:
  using UnaryOperator::setValue;
  double calculate() override;
 private:
  ptrToICalc value_;
};


class OperatorAcos: public UnaryOperator {
 public:
  using UnaryOperator::setValue;
  double calculate() override;
 private:
  ptrToICalc value_;
};

}  // namespace calculator