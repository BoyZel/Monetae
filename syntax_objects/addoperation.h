#ifndef ADDOPERATION_H
#define ADDOPERATION_H
#include <vector>
#include <memory>
#include <Token.h>
#include "multioperation.h"
#include "inode.h"
class MultiOperation;
class AddOperation : public INode
{
    std::unique_ptr<MultiOperation> multiOperation;
    std::vector<std::unique_ptr<std::string>> additiveOps;
    std::vector<std::unique_ptr<AddOperation>> addOperations;
public:
    AddOperation();
    AddOperation(std::unique_ptr<MultiOperation> multiOperation);
    void addAddOperator(std::unique_ptr<std::string> next);
    void addAddOperation(std::unique_ptr<AddOperation> next);
    void accept(Interpreter visitor);
};

#endif // ADDOPERATION_H
