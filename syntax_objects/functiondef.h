#ifndef FUNCTIONDEF_H
#define FUNCTIONDEF_H
#include "parameters.h"
#include "statementblock.h"

class FunctionDef
{
    std::unique_ptr<Token> identifier;
    std::unique_ptr<Parameters> parameters;
    std::unique_ptr<StatementBlock> statementBlock;
public:
    FunctionDef();
    FunctionDef(std::unique_ptr<Token> identifier, std::unique_ptr<Parameters> parameters, std::unique_ptr<StatementBlock> statementBlock);
};

#endif // FUNCTIONDEF_H
