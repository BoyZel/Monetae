#ifndef WHILELOOP_H
#define WHILELOOP_H

#include "instruction.h"
#include "logicalexpression.h"
#include "statementblock.h"
class WhileLoop : public Instruction
{
    std::unique_ptr<LogicalExpression> logicalExpression;
    std::unique_ptr<StatementBlock> statementBlock;
public:
    WhileLoop(std::unique_ptr<LogicalExpression> expression, std::unique_ptr<StatementBlock> block);
    WhileLoop();
    void accept(Interpreter visitor);
};

#endif // WHILELOOP_H
