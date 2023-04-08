#include <cmath>
#include "calculator.h"



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
void Expression::setValue(std::string& value) {
    value_ = std::stod(value);
}
double Expression::calculate() {
    return value_;
}

// OperatorPlus
double OperatorPlus::calculate() {
    return leftValue_->calculate() + rightValue_->calculate();
}
// OperatorMinus
double OperatorMinus::calculate() {
    return leftValue_->calculate() - rightValue_->calculate();
}
// OperatorMultiply
double OperatorMultiply::calculate() {
    return leftValue_->calculate() * rightValue_->calculate();
}
// OperatorAsin
double OperatorAsin::calculate() {
    return asin(value_->calculate());
}
//// OperatorAcos
double OperatorAcos::calculate() {
    return acos(value_->calculate());
}

}  // namespace calculator