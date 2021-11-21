#ifndef PRIMARYEXPRESSION_H
#define PRIMARYEXPRESSION_H
#include "logicalexpression.h"
#include "addoperation.h"

class LogicalExpression;
class AddOperation;
class Interpreter;

class PrimaryExpression
{
    bool negation;
    std::unique_ptr<LogicalExpression> logicalExpression;
    std::unique_ptr<AddOperation> addOperation;
public:
    PrimaryExpression();
    PrimaryExpression(std::unique_ptr<LogicalExpression> logicalExpression);
    PrimaryExpression(std::unique_ptr<AddOperation> addOperation);
    void setNegation(bool value);
    void accept(Interpreter visitor);
};

#endif // PRIMARYEXPRESSION_H
