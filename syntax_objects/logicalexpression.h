#ifndef LOGICALEXPRESSION_H
#define LOGICALEXPRESSION_H
#include <memory>
#include <vector>
#include <Token.h>
#include "expression.h"

class Expression;
class Interpreter;


class LogicalExpression
{
    std::unique_ptr<Expression> expression;
    std::vector<std::unique_ptr<std::string>> logicalOps;
    std::vector<std::unique_ptr<Expression>> expressions;
public:
    LogicalExpression();
    LogicalExpression(std::unique_ptr<Expression> expression);
    void addLogicalOp(std::unique_ptr<std::string> next);
    void addExpression(std::unique_ptr<Expression> next);
    void accept(Interpreter visitor);
};

#endif // LOGICALEXPRESSION_H
