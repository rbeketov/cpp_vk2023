#include <cmath>
#include <stdexcept>
#include "calculator.h"

const std::string NULLPTR_IN_NODE = "Node have nullptr. Calculate impossible";

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
        throw std::runtime_error(NULLPTR_IN_NODE);
    }
    return leftValue_->calculate() + rightValue_->calculate();
}
// OperatorMinus
double OperatorMinus::calculate() {
    if (!leftValue_.get() || !rightValue_.get()) {
        throw std::runtime_error(NULLPTR_IN_NODE);
    }
    return leftValue_->calculate() - rightValue_->calculate();
}
// OperatorMultiply
double OperatorMultiply::calculate() {
    if (!leftValue_.get() || !rightValue_.get()) {
        throw std::runtime_error(NULLPTR_IN_NODE);
    }
    return leftValue_->calculate() * rightValue_->calculate();
}
// OperatorAsin
double OperatorAsin::calculate() {
    if (!value_.get()) {
        throw std::runtime_error(NULLPTR_IN_NODE);
    }
    if (std::abs(value_->calculate()) > 1) {
        throw std::runtime_error("The scope of the function \"arcsin(x)\" definition is violated");
    }
    return asin(value_->calculate());
}
// OperatorAcos
double OperatorAcos::calculate() {
    if (!value_.get()) {
        throw std::runtime_error(NULLPTR_IN_NODE);
    }
    if (std::abs(value_->calculate()) > 1) {
        throw std::runtime_error("The scope of the function \"arccos(x)\" definition is violated");
    }
    return acos(value_->calculate());
}

}  // namespace calculator