#ifndef STATEMENTBLOCK_H
#define STATEMENTBLOCK_H
#include "instruction.h"

class StatementBlock
{
    std::vector<std::unique_ptr<Instruction>> instructions;
public:
    StatementBlock();
    void addInstruction(std::unique_ptr<Instruction> next);
};

#endif // STATEMENTBLOCK_H
