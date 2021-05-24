#include "argument.h"

Argument::Argument()
{

}

Argument::Argument(std::unique_ptr<Token> value)
    :value(std::move(value)){}
Argument::Argument(std::unique_ptr<AddOperation> addOperation)
    :addOperation(std::move(addOperation)){}
Argument::Argument(std::unique_ptr<LogicalExpression> logicalExpression)
    :logicalExpression(std::move(logicalExpression)){}
