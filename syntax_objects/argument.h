#ifndef ARGUMENT_H
#define ARGUMENT_H

#include "addoperation.h"
#include "logicalexpression.h"
#include <Token.h>
class AddOperation;
class LogicalExpression;
class Interpreter;
class Argument
{
    std::unique_ptr<Token> value;
    std::unique_ptr<AddOperation> addOperation;
    std::unique_ptr<LogicalExpression> logicalExpression;
public:
    Argument();
    Argument(std::unique_ptr<Token> value);
    Argument(std::unique_ptr<AddOperation> addOperation);
    Argument(std::unique_ptr<LogicalExpression> logicalExpression);
    void accept(Interpreter visitor);
};

#endif // ARGUMENT_H
