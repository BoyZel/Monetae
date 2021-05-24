#include "ifelse.h"

IfElse::IfElse(std::unique_ptr<LogicalExpression> expression, std::unique_ptr<StatementBlock> block)
    : logicalExpression(std::move(expression)), ifStatementBlock(std::move(block)){}

IfElse::IfElse(std::unique_ptr<LogicalExpression> expression, std::unique_ptr<StatementBlock> block, std::unique_ptr<StatementBlock> elseBlock)
    : logicalExpression(std::move(expression)), ifStatementBlock(std::move(block)), elseStatementBlock(std::move(elseBlock)){}

IfElse::IfElse()
{

}
