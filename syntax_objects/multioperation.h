#ifndef MULTIOPERATION_H
#define MULTIOPERATION_H

#include "factor.h"
class Factor;

class MultiOperation
{
    std::unique_ptr<Factor> factor;
    std::vector<std::unique_ptr<Token>> multiOps;
    std::vector<std::unique_ptr<MultiOperation>> multiOperations;
public:
    MultiOperation();
    MultiOperation(std::unique_ptr<Factor> factor);
    void addMultiOperator(std::unique_ptr<Token> next);
    void addMultiOperation(std::unique_ptr<MultiOperation> next);
};

#endif // MULTIOPERATION_H
