#ifndef PROGRAM_H
#define PROGRAM_H
#include "vardeclaration.h"
#include "functiondef.h"

class Program
{
    std::vector<std::unique_ptr<Instruction>> varDeclarations;
    std::vector<std::unique_ptr<FunctionDef>> functionDefs;
public:
    Program();
    void addVarDeclaration(std::unique_ptr<Instruction> next);
    void addFunctionDef(std::unique_ptr<FunctionDef> next);
};

#endif // PROGRAM_H
