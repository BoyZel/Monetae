#ifndef VARDECLARATION_H
#define VARDECLARATION_H

#include <Token.h>
#include "addoperation.h"
#include "functioncall.h"
#include "logicalexpression.h"
#include "instruction.h"
class VarDeclaration: public Instruction
{
    std::unique_ptr<std::string> identifier;
    std::unique_ptr<AddOperation> addOperation;
    std::unique_ptr<Instruction> functionCall;
    std::unique_ptr<LogicalExpression> logicalExpression;
public:
    VarDeclaration(std::unique_ptr<std::string> ident, std::unique_ptr<AddOperation> addOperation);
    VarDeclaration(std::unique_ptr<std::string> ident, std::unique_ptr<Instruction> functionCall);
    VarDeclaration(std::unique_ptr<std::string> ident, std::unique_ptr<LogicalExpression> logicalExpression);
    VarDeclaration();
    void accept(Interpreter visitor);
};

#endif // VARDECLARATION_H
