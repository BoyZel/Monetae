#include "expression.h"

Expression::Expression(std::unique_ptr<AddOperation> addOperation1, std::unique_ptr<Token> compareOp, std::unique_ptr<AddOperation> addOperation2)
    :addOperation1(std::move(addOperation1)), compareOp(std::move(compareOp)), addOperation2(std::move(addOperation2)){}

Expression::Expression(std::unique_ptr<LogicalExpression> logicalExpression)
    :logicalExpression(std::move(logicalExpression)){}

Expression::Expression()
{

}
