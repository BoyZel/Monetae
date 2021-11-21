#ifndef IFELSE_H
#define IFELSE_H
#include "instruction.h"
#include "statementblock.h"
class IfElse: public Instruction
{
    std::unique_ptr<LogicalExpression> logicalExpression;
    std::unique_ptr<StatementBlock> ifStatementBlock;
    std::unique_ptr<StatementBlock> elseStatementBlock; //optional
public:
    IfElse();
    IfElse(std::unique_ptr<LogicalExpression> expression, std::unique_ptr<StatementBlock> block);
    IfElse(std::unique_ptr<LogicalExpression> expression, std::unique_ptr<StatementBlock> block, std::unique_ptr<StatementBlock> elseBlock);
    void accept(Interpreter visitor);
};

#endif // IFELSE_H
