#include "return.h"

Return::Return()
{

}
Return::Return(std::unique_ptr<AddOperation> addOperation)
    :addOperation(std::move(addOperation)){}

Return::Return(std::unique_ptr<Instruction> functionCall)
    :functionCall(std::move(functionCall)){}

Return::Return(std::unique_ptr<LogicalExpression> logicalExpression)
    :logicalExpression(std::move(logicalExpression)){}
