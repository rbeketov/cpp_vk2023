#include <cmath>
#include "exception.h"
#include "calculator.h"

const std::string ASIN_TOKEN = "asin";
const std::string ACOS_TOKEN = "acos"; 

namespace calculator {

// BinaryOperator
void BinaryOperator::setLeft(ptrToICalc&& leftValue) {
    leftValue_ = std::move(leftValue);
}
void BinaryOperator::setRight(ptrToICalc&& rightValue) {
    rightValue_ = std::move(rightValue);
}

// UnaryOperator
void UnaryOperator::setValue(ptrToICalc&& value) {
    value_ = std::move(value);
}

// Expression
Expression::Expression(std::string& value) : value_(std::stod(value)) {}
double Expression::calculate() {
    return value_;
}

// OperatorPlus
double OperatorPlus::calculate() {
    if (!leftValue_.get() || !rightValue_.get()) {
        throw InvalidCalcNode();
    }
    return leftValue_->calculate() + rightValue_->calculate();
}
// OperatorMinus
double OperatorMinus::calculate() {
    if (!leftValue_.get() || !rightValue_.get()) {
        throw InvalidCalcNode();
    }
    return leftValue_->calculate() - rightValue_->calculate();
}
// OperatorMultiply
double OperatorMultiply::calculate() {
    if (!leftValue_.get() || !rightValue_.get()) {
        throw InvalidCalcNode();
    }
    return leftValue_->calculate() * rightValue_->calculate();
}
// OperatorAsin
double OperatorAsin::calculate() {
    if (!value_.get()) {
        throw InvalidCalcNode();
    }
    if (std::abs(value_->calculate()) > 1) {
        throw InvalidMathFuncScope(ASIN_TOKEN);
    }
    return asin(value_->calculate());
}
// OperatorAcos
double OperatorAcos::calculate() {
    if (!value_.get()) {
        throw InvalidCalcNode();
    }
    if (std::abs(value_->calculate()) > 1) {
        throw InvalidMathFuncScope(ACOS_TOKEN);
    }
    return acos(value_->calculate());
}

}  // namespace calculator