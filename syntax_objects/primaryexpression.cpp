#include "primaryexpression.h"

PrimaryExpression::PrimaryExpression()
{

}

PrimaryExpression::PrimaryExpression(std::unique_ptr<LogicalExpression> logicalExpression)
    :logicalExpression(std::move(logicalExpression)){}

PrimaryExpression::PrimaryExpression(std::unique_ptr<AddOperation> addOperation)
    :addOperation(std::move(addOperation)){}

void PrimaryExpression::setNegation(bool value){
    negation = value;
}
