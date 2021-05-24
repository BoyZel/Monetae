#include "statementblock.h"

StatementBlock::StatementBlock()
{

}

void StatementBlock::addInstruction(std::unique_ptr<Instruction> next)
{
    instructions.push_back(std::move(next));
}
