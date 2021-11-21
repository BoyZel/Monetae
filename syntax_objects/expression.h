#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "primaryexpression.h"
class AddOperation;
class PrimaryExpression;
class Interpreter;
class Expression
{
    std::unique_ptr<PrimaryExpression> primaryExpression1;
    std::unique_ptr<std::string> compareOp;
    std::unique_ptr<PrimaryExpression> primaryExpression2;
public:
    Expression();
    Expression(std::unique_ptr<PrimaryExpression> primaryExpression1, std::unique_ptr<std::string> compareOp, std::unique_ptr<PrimaryExpression> primaryExpresion2);
    void accept(Interpreter visitor);
};

#endif // EXPRESSION_H
