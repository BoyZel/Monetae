#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "logicalexpression.h"
class Instruction
{
    enum class InstructionType{
        WhileLoop,
        IfElse,
        VarDefinition,
        Assignment,
        Return,
        FunctionCall
    };
    InstructionType instructionType;

public:
    Instruction();
};

#endif // INSTRUCTION_H
