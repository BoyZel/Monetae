#include "assignment.h"

Assignment::Assignment()
{

}

Assignment::Assignment(std::unique_ptr<std::string> ident, std::unique_ptr<AddOperation> addOperation)
    :identifier(std::move(ident)), addOperation(std::move(addOperation)){}

Assignment::Assignment(std::unique_ptr<std::string> ident, std::unique_ptr<Instruction> functionCall)
    :identifier(std::move(ident)), functionCall(std::move(functionCall)){}

Assignment::Assignment(std::unique_ptr<std::string> ident, std::unique_ptr<LogicalExpression> logicalExpression)
    :identifier(std::move(ident)), logicalExpression(std::move(logicalExpression)){}
