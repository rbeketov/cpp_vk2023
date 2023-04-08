#pragma once

#include <memory>
#include <string>

namespace calculator {

class ICalculatable;

using ptrToICalc = std::unique_ptr<ICalculatable>;

class ICalculatable {
 public:
  virtual ~ICalculatable() {};
  virtual double calculate() = 0;
   // setters
  virtual void setValue(ptrToICalc&& value) = 0;
  virtual void setLeft(ptrToICalc&& leftValue) = 0;
  virtual void setRight(ptrToICalc&& rightValue) = 0;

};

class UnaryOperator: public ICalculatable {
 public:
  void setValue(ptrToICalc&& value) override;
  // virtual double calculate() = 0;
  void setLeft(ptrToICalc&& leftValue) override  {leftValue.get(); throw;}
  void setRight(ptrToICalc&& rightValue) override {rightValue.get(); throw;}

 private:
   ptrToICalc value_;
};

class BinaryOperator: public ICalculatable {
 public:
  void setLeft(ptrToICalc&& leftValue) override;
  void setRight(ptrToICalc&& rightValue) override;
  // virtual double calculate() = 0;

  void setValue(ptrToICalc&& value) override {value.get(); throw;}

 private:
  ptrToICalc leftValue_;
  ptrToICalc rightValue_;
};


class Expression: public ICalculatable {
 public:
  Expression();
  explicit Expression(std::string& value);
  double calculate() override;
  

  void setValue(ptrToICalc&& value) override { value.get();  throw;}
  void setLeft(ptrToICalc&& leftValue) override  {leftValue.get(); throw;}
  void setRight(ptrToICalc&& rightValue) override { rightValue.get(); throw;}

 private:
  double value_;
};

class OperatorPlus: public BinaryOperator {
 public:
  double calculate() override;
 private:
  ptrToICalc leftValue_;
  ptrToICalc rightValue_;
};

class OperatorMinus: public BinaryOperator {
 public:
  double calculate() override;
 private:
  ptrToICalc leftValue_;
  ptrToICalc rightValue_;
};

class OperatorMultiply: public BinaryOperator {
 public:
  double calculate() override;
 private:
  ptrToICalc leftValue_;
  ptrToICalc rightValue_;
};


class OperatorAsin: public UnaryOperator {
 public:
   double calculate() override;
 private:
   ptrToICalc value_;
};


class OperatorAcos: public UnaryOperator {
 public:
   double calculate() override;
 private:
   ptrToICalc value_;
};

}  // namespace calculator