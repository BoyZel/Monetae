#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "logicalexpression.h"

class Interpreter;
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
    void accept(Interpreter visitor);
};

#endif // INSTRUCTION_H
