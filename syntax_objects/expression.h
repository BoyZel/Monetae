#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "addoperation.h"
#include "logicalexpression.h"

class LogicalExpression;
class Expression
{
    std::unique_ptr<AddOperation> addOperation1;
    std::unique_ptr<Token> compareOp;
    std::unique_ptr<AddOperation> addOperation2;
    std::unique_ptr<LogicalExpression> logicalExpression; //or this
public:
    Expression();
    Expression(std::unique_ptr<AddOperation> addOperation1, std::unique_ptr<Token> compareOp, std::unique_ptr<AddOperation> addOperation2);
    Expression(std::unique_ptr<LogicalExpression> logicalExpression);
};

#endif // EXPRESSION_H
