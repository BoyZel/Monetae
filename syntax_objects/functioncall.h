#ifndef FUNCTIONCALL_H
#define FUNCTIONCALL_H
#include <Token.h>
#include "argument.h"
#include "instruction.h"
class Argument;
class Interpreter;
class FunctionCall: public Instruction
{
    std::unique_ptr<std::string> identifier;
    std::vector<std::unique_ptr<Argument>> arguments;
public:
    FunctionCall();
    FunctionCall(std::unique_ptr<std::string> ident);
    void addArgument(std::unique_ptr<Argument> next);
    void accept(Interpreter visitor);
};

#endif // FUNCTIONCALL_H
