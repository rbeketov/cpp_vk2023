#include "utils.h"
#include "pars_expression.h"
#include "exception.h"
#include <cmath>
static constexpr double ABS_ERROR = 1e-2;

TEST(BaseTestLogic, TestOperatorPlus) {
    const char inputBuffer[] = "5+5";
    auto expression = parsePassedExpressionToCalc(inputBuffer);
    double expected = 10;
    ASSERT_NEAR(expression->calculate(), expected, ABS_ERROR);
}

TEST(BaseTestLogic, TestOperatorMultiply) {
    const char inputBuffer[] = "5*5";
    auto expression = parsePassedExpressionToCalc(inputBuffer);
    double expected = 25;
    ASSERT_NEAR(expression->calculate(), expected, ABS_ERROR);
}

TEST(BaseTestLogic, TestOperatorMinus) {
    const char inputBuffer[] = "5-5";
    auto expression = parsePassedExpressionToCalc(inputBuffer);
    double expected = 0;
    ASSERT_NEAR(expression->calculate(), expected, ABS_ERROR);
}

TEST(BaseTestLogic, TestOperatorAsinPositiv) {
    const char inputBuffer[] = "asin(1)";
    auto expression = parsePassedExpressionToCalc(inputBuffer);
    double expected = M_PI / 2;
    ASSERT_NEAR(expression->calculate(), expected, ABS_ERROR);
}

TEST(BaseTestLogic, TestOperatorAsinNegativ) {
    const char inputBuffer[] = "asin(-1)";
    auto expression = parsePassedExpressionToCalc(inputBuffer);
    double expected = -1.57;
    ASSERT_NEAR(expression->calculate(), expected, ABS_ERROR);
}

TEST(BaseTestLogic, TestOperatorAcosPositiv) {
    const char inputBuffer[] = "acos(1)";
    auto expression = parsePassedExpressionToCalc(inputBuffer);
    double expected = 0;
    ASSERT_NEAR(expression->calculate(), expected, ABS_ERROR);
}

TEST(BaseTestLogic, TestOperatorAcosZero) {
    const char inputBuffer[] = "acos(0)";
    auto expression = parsePassedExpressionToCalc(inputBuffer);
    double expected = M_PI / 2;
    ASSERT_NEAR(expression->calculate(), expected, ABS_ERROR);
}


TEST(BaseTestLogic, TestCompositOperators1) {
    const char inputBuffer[] = "5-5+5";
    auto expression = parsePassedExpressionToCalc(inputBuffer);
    double expected = 5;
    ASSERT_NEAR(expression->calculate(), expected, ABS_ERROR);
}

TEST(BaseTestLogic, TestCompositOperators2) {
    const char inputBuffer[] = "5-5*5.5";
    auto expression = parsePassedExpressionToCalc(inputBuffer);
    double expected = -22.5;
    ASSERT_NEAR(expression->calculate(), expected, ABS_ERROR);
}

TEST(BaseTestLogic, TestCompositOperators3) {
    const char inputBuffer[] = "5.001-5*1";
    auto expression = parsePassedExpressionToCalc(inputBuffer);
    double expected = 0.001;
    ASSERT_NEAR(expression->calculate(), expected, ABS_ERROR);
}

TEST(BaseTestLogic, TestCompositOperators4) {
    const char inputBuffer[] = "5+5+5*100";
    auto expression = parsePassedExpressionToCalc(inputBuffer);
    double expected = 510;
    ASSERT_NEAR(expression->calculate(), expected, ABS_ERROR);
}

TEST(BaseTestLogic, TestCompositOperators5) {
    const char inputBuffer[] = "5*0.5";
    auto expression = parsePassedExpressionToCalc(inputBuffer);
    double expected = 2.5;
    ASSERT_NEAR(expression->calculate(), expected, ABS_ERROR);
}


TEST(BaseTestLogic, TestExpressionWithBuckets1) {
    const char inputBuffer[] = "5+(-5)*0.5";
    auto expression = parsePassedExpressionToCalc(inputBuffer);
    double expected = 2.5;
    ASSERT_NEAR(expression->calculate(), expected, ABS_ERROR);
}


TEST(BaseTestLogic, TestExpressionWithBuckets2) {
    const char inputBuffer[] = "(5+7)*10";
    auto expression = parsePassedExpressionToCalc(inputBuffer);
    double expected = 120;
    ASSERT_NEAR(expression->calculate(), expected, ABS_ERROR);
}



TEST(BaseTestLogic, TestExpressionWithBuckets3) {
    const char inputBuffer[] = "asin(5*0.5-2.5)";
    auto expression = parsePassedExpressionToCalc(inputBuffer);
    double expected = 0;
    ASSERT_NEAR(expression->calculate(), expected, ABS_ERROR);
}


TEST(BaseTestLogic, TestExpressionWithBuckets4) {
    const char inputBuffer[] = "acos(asin(0))";
    auto expression = parsePassedExpressionToCalc(inputBuffer);
    double expected = M_PI / 2;
    ASSERT_NEAR(expression->calculate(), expected, ABS_ERROR);
}

TEST(BaseTestLogic, TestExpressionWithBuckets5) {
    const char inputBuffer[] = "20*(-4)";
    auto expression = parsePassedExpressionToCalc(inputBuffer);
    double expected = -80;
    ASSERT_NEAR(expression->calculate(), expected, ABS_ERROR);
}



TEST(ErrorTest, EmptyBrackets) {
    const char inputBuffer[] = "()";
    EXPECT_THROW(parsePassedExpressionToCalc(inputBuffer), calculator::InvalidExpression);
}

TEST(ErrorTest, InvalidTokenDivision) {
    const char inputBuffer[] = "5+7/2";
    EXPECT_THROW(parsePassedExpressionToCalc(inputBuffer), calculator::InvalidToken);
}


TEST(ErrorTest, InvalidExpressionTwoMultiply) {
    const char inputBuffer[] = "5**2";
    EXPECT_THROW(parsePassedExpressionToCalc(inputBuffer), calculator::InvalidExpression);
}

TEST(ErrorTest, InvalidExpressionPlusMinusWithoutBrackets) {
    const char inputBuffer[] = "5+-2";
    EXPECT_THROW(parsePassedExpressionToCalc(inputBuffer), calculator::InvalidExpression);
}

TEST(ErrorTest, InvalidExpressionTwoDotsInRow) {
    const char inputBuffer[] = "5..2";
    EXPECT_THROW(parsePassedExpressionToCalc(inputBuffer), calculator::InvalidExpression);
}

TEST(ErrorTest, InvalidExpressionBadDouble) {
    const char inputBuffer[] = "5.5.5+7";
    EXPECT_THROW(parsePassedExpressionToCalc(inputBuffer), calculator::InvalidExpression);
}

TEST(ErrorTest, InvalidExpressionBadBracketsAfter) {
    const char inputBuffer[] = "asin(1)()";
    EXPECT_THROW(parsePassedExpressionToCalc(inputBuffer), calculator::InvalidExpression);
}

TEST(ErrorTest, InvalidExpressionBadBracketsBefor) {
    const char inputBuffer[] = "()asin(1)";
    EXPECT_THROW(parsePassedExpressionToCalc(inputBuffer), calculator::InvalidExpression);
}

TEST(ErrorTest, InvalidExpressionInvalidScopeAsinPositive) {
    const char inputBuffer[] = "asin(10)";
    auto result = parsePassedExpressionToCalc(inputBuffer);
    EXPECT_THROW(result->calculate(), calculator::InvalidMathFuncScope);
}

TEST(ErrorTest, InvalidExpressionInvalidScopeAsinNegative) {
    const char inputBuffer[] = "asin(-10)";
    auto result = parsePassedExpressionToCalc(inputBuffer);
    EXPECT_THROW(result->calculate(), calculator::InvalidMathFuncScope);
}


TEST(ErrorTest, InvalidExpressionInvalidScopeAcosPositive) {
    const char inputBuffer[] = "acos(10)";
    auto result = parsePassedExpressionToCalc(inputBuffer);
    EXPECT_THROW(result->calculate(), calculator::InvalidMathFuncScope);
}


TEST(ErrorTest, InvalidExpressionInvalidScopeAcosNegative) {
    const char inputBuffer[] = "acos(-10)";
    auto result = parsePassedExpressionToCalc(inputBuffer);
    EXPECT_THROW(result->calculate(), calculator::InvalidMathFuncScope);
}

TEST(ErrorTest, InvalidExpressionBadBracketsSequenceClose) {
    const char inputBuffer[] = "(5+7)+3)";
    EXPECT_THROW(parsePassedExpressionToCalc(inputBuffer), calculator::InvalidExpression);
}

TEST(ErrorTest, InvalidExpressionBadBracketsSequenceOpen) {
    const char inputBuffer[] = "((5+7)+3";
    EXPECT_THROW(parsePassedExpressionToCalc(inputBuffer), calculator::InvalidExpression);
}

TEST(ExtraLogic, FirstExpression) {
    const char inputBuffer[] = "5+(7*0.2)-asin(0+(5*0.5-2.5))+15*0.2";
    auto expression = parsePassedExpressionToCalc(inputBuffer);
    double expected = 9.4;
    ASSERT_NEAR(expression->calculate(), expected, ABS_ERROR);
}

TEST(ExtraLogic, SecondExpression) {
    const char inputBuffer[] = "15+1*1000-acos(-1)+17*(-2*19+6-8.24)";
    auto expression = parsePassedExpressionToCalc(inputBuffer);
    double expected = 327.78;
    ASSERT_NEAR(expression->calculate(), expected, ABS_ERROR);
}

TEST(ExtraLogic, ThirdExpression) {
    const char inputBuffer[] = "8+(-2)+(-3)+(-5*(-2))";
    auto expression = parsePassedExpressionToCalc(inputBuffer);
    double expected = 13;
    ASSERT_NEAR(expression->calculate(), expected, ABS_ERROR);
}
