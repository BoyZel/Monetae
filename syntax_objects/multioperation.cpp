#include "multioperation.h"

MultiOperation::MultiOperation()
{

}

MultiOperation::MultiOperation(std::unique_ptr<Factor> factor)
    :factor(std::move(factor)){}

void MultiOperation::addMultiOperator(std::unique_ptr<Token> next)
{
    multiOps.push_back(std::move(next));
}

void MultiOperation::addMultiOperation(std::unique_ptr<MultiOperation> next)
{
    multiOperations.push_back(std::move(next));
}
