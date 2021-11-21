#include "logicalexpression.h"

LogicalExpression::LogicalExpression()
{
    
}

LogicalExpression::LogicalExpression(std::unique_ptr<Expression> expression)
    :expression(std::move(expression)){}

void LogicalExpression::addLogicalOp(std::unique_ptr<std::string> next)
{
    logicalOps.push_back(std::move(next));
}

void LogicalExpression::addExpression(std::unique_ptr<Expression> next)
{
    expressions.push_back(std::move(next));
}
