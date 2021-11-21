#ifndef MULTIOPERATION_H
#define MULTIOPERATION_H

#include "factor.h"
class Factor;
class Interpreter;
class MultiOperation
{
    std::unique_ptr<Factor> factor;
    std::vector<std::unique_ptr<std::string>> multiOps;
    std::vector<std::unique_ptr<MultiOperation>> multiOperations;
public:
    MultiOperation();
    MultiOperation(std::unique_ptr<Factor> factor);
    void addMultiOperator(std::unique_ptr<std::string> next);
    void addMultiOperation(std::unique_ptr<MultiOperation> next);
    void accept(Interpreter visitor);
};

#endif // MULTIOPERATION_H
