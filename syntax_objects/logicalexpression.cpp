#include "logicalexpression.h"

void LogicalExpression::setNegation(bool value)
{
    negation = value;
}

LogicalExpression::LogicalExpression()
{
    
}

LogicalExpression::LogicalExpression(std::unique_ptr<Expression> expression)
    :expression(std::move(expression)){}

void LogicalExpression::addLogicalOp(std::unique_ptr<Token> next)
{
    logicalOps.push_back(std::move(next));
}

void LogicalExpression::addLogicalExpression(std::unique_ptr<LogicalExpression> next)
{
    logicalExpressions.push_back(std::move(next));
}
