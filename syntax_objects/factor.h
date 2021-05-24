#ifndef FACTOR_H
#define FACTOR_H
#include "addoperation.h"

class AddOperation;

class Factor
{
    bool minus;
    std::unique_ptr<Token> number;
    std::unique_ptr<Token> identifier;
    std::unique_ptr<AddOperation> addOperation;
public:
    Factor();
    Factor(std::unique_ptr<Token> number,std::unique_ptr<Token> identifier);
    Factor(std::unique_ptr<Token> identifier);
    Factor(std::unique_ptr<AddOperation> addOperation);
    bool getMinus() const;
    void setMinus(bool value);
};

#endif // FACTOR_H
