#include "addoperation.h"

AddOperation::AddOperation()
{

}

AddOperation::AddOperation(std::unique_ptr<MultiOperation> multiOperation)
    :multiOperation(std::move(multiOperation)){}

void AddOperation::addAddOperator(std::unique_ptr<Token> next)
{
    additiveOps.push_back(std::move(next));
}

void AddOperation::addAddOperation(std::unique_ptr<AddOperation> next)
{
    addOperations.push_back(std::move(next));
}


