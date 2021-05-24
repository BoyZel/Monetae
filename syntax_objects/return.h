#ifndef RETURN_H
#define RETURN_H

#include "addoperation.h"
#include "functioncall.h"
#include "logicalexpression.h"
#include "instruction.h"

class Return: public Instruction
{
    std::unique_ptr<AddOperation> addOperation;
    std::unique_ptr<Instruction> functionCall;
    std::unique_ptr<LogicalExpression> logicalExpression;
public:
    Return();
    Return(std::unique_ptr<AddOperation> addOperation);
    Return(std::unique_ptr<Instruction> functionCall);
    Return(std::unique_ptr<LogicalExpression> logicalExpression);
};

#endif // RETURN_H
