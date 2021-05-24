#ifndef LOGICALEXPRESSION_H
#define LOGICALEXPRESSION_H

#include <Token.h>
#include "expression.h"

class Expression;

class LogicalExpression
{
    bool negation;
    std::unique_ptr<Expression> expression;
    std::vector<std::unique_ptr<Token>> logicalOps;
    std::vector<std::unique_ptr<LogicalExpression>> logicalExpressions;
public:
    LogicalExpression();
    LogicalExpression(std::unique_ptr<Expression> expression);
    void addLogicalOp(std::unique_ptr<Token> next);
    void addLogicalExpression(std::unique_ptr<LogicalExpression> next);
    void setNegation(bool value);
};

#endif // LOGICALEXPRESSION_H
