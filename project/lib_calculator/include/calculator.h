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
  virtual void setValue(std::string& value) = 0;
  virtual void setLeft(ptrToICalc&& leftValue) = 0;
  virtual void setRight(ptrToICalc&& rightValue) = 0;
};

class UnaryOperator: public ICalculatable {
 public:
   virtual double calculate() override = 0;
   void setValue(ptrToICalc&& value) override;
 private:
   ptrToICalc value_;
};

class BinaryOperator: public ICalculatable {
 public:
   void setLeft(ptrToICalc&& leftValue) override;
   void setRight(ptrToICalc&& rightValue) override;
   virtual double calculate() override = 0;
 private:
   ptrToICalc leftValue_;
   ptrToICalc rightValue_;
};


class Expression: public ICalculatable {
 public:
   Expression();
   explicit Expression(std::string& value);
   void setValue(std::string& value) override;
   double calculate() override;
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
   using UnaryOperator::UnaryOperator;
   double calculate() override;
 private:
   ptrToICalc value_;
};

}  // namespace calculator