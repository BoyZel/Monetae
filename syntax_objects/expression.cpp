#include "expression.h"

Expression::Expression(std::unique_ptr<PrimaryExpression> primaryExpression1, std::unique_ptr<std::string> compareOp, std::unique_ptr<PrimaryExpression> primaryExpresion2)
    :primaryExpression1(std::move(primaryExpression1)), compareOp(std::move(compareOp)), primaryExpression2(std::move(primaryExpresion2)){}


Expression::Expression()
{

}
