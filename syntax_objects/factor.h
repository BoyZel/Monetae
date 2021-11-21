#ifndef FACTOR_H
#define FACTOR_H
#include "addoperation.h"
#include "instruction.h"
#include "inode.h"
class Instruction;
class AddOperation;

class Factor
{
    bool minus;
    std::unique_ptr<Token> number;
    std::unique_ptr<std::string> identifier;
    std::unique_ptr<AddOperation> addOperation;
    std::unique_ptr<Instruction> funCall;
public:
    Factor();
    Factor(std::unique_ptr<Token> number,std::unique_ptr<std::string> identifier);
    Factor(std::unique_ptr<std::string> identifier);
    Factor(std::unique_ptr<Token> number);
    Factor(std::unique_ptr<AddOperation> addOperation);
    Factor(std::unique_ptr<Instruction> funCall);
    bool getMinus() const;
    void setMinus(bool value);
    void accept(Interpreter visitor);
};

#endif // FACTOR_H
