#include "whileloop.h"

WhileLoop::WhileLoop(std::unique_ptr<LogicalExpression> expression, std::unique_ptr<StatementBlock> block)
    : logicalExpression(std::move(expression)), statementBlock(std::move(block)){}

WhileLoop::WhileLoop()
{

}
