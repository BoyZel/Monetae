#include "functioncall.h"

FunctionCall::FunctionCall()
{

}

FunctionCall::FunctionCall(std::unique_ptr<std::string> ident)
    :identifier(std::move(ident)){}

void FunctionCall::addArgument(std::unique_ptr<Argument> next)
{
    arguments.push_back(std::move(next));
}
