#ifndef ADDOPERATION_H
#define ADDOPERATION_H
#include <vector>
#include <memory>
#include <Token.h>
#include "multioperation.h"
class MultiOperation;

class AddOperation
{
    std::unique_ptr<MultiOperation> multiOperation;
    std::vector<std::unique_ptr<Token>> additiveOps;
    std::vector<std::unique_ptr<AddOperation>> addOperations;
public:
    AddOperation();
    AddOperation(std::unique_ptr<MultiOperation> multiOperation);
    void addAddOperator(std::unique_ptr<Token> next);
    void addAddOperation(std::unique_ptr<AddOperation> next);
};

#endif // ADDOPERATION_H
