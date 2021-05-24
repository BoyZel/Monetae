#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <Token.h>
#include "addoperation.h"
#include "functioncall.h"
#include "logicalexpression.h"
#include "instruction.h"
class Assignment: public Instruction
{
    std::unique_ptr<Token> identifier;
    std::unique_ptr<AddOperation> addOperation; //optional
    std::unique_ptr<Instruction> functionCall; //or this
    std::unique_ptr<LogicalExpression> logicalExpression; //or this
public:
    Assignment();
    Assignment(std::unique_ptr<Token> ident, std::unique_ptr<AddOperation> addOperation);
    Assignment(std::unique_ptr<Token> ident, std::unique_ptr<Instruction> functionCall);
    Assignment(std::unique_ptr<Token> ident, std::unique_ptr<LogicalExpression> logicalExpression);
};

#endif // ASSIGNMENT_H
