#include "program.h"

Program::Program()
{

}

void Program::addVarDeclaration(std::unique_ptr<Instruction> next)
{
    varDeclarations.push_back(std::move(next));
}

void Program::addFunctionDef(std::unique_ptr<FunctionDef> next)
{
    functionDefs.push_back(std::move(next));
}

