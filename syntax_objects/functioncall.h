#ifndef FUNCTIONCALL_H
#define FUNCTIONCALL_H
#include <Token.h>
#include "argument.h"
#include "instruction.h"
class FunctionCall: public Instruction
{
    std::unique_ptr<Token> identifier;
    std::vector<std::unique_ptr<Argument>> arguments;
public:
    FunctionCall();
    FunctionCall(std::unique_ptr<Token> ident);
    void addArgument(std::unique_ptr<Argument> next);
};

#endif // FUNCTIONCALL_H
