#include "functiondef.h"

FunctionDef::FunctionDef()
{

}

FunctionDef::FunctionDef(std::unique_ptr<std::string> identifier, std::unique_ptr<Parameters> parameters, std::unique_ptr<StatementBlock> statementBlock)
    :identifier(std::move(identifier)), parameters(std::move(parameters)), statementBlock(std::move(statementBlock)){}
