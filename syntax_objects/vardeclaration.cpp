#include "vardeclaration.h"

VarDeclaration::VarDeclaration(std::unique_ptr<Token> ident, std::unique_ptr<AddOperation> addOperation)
    :identifier(std::move(ident)), addOperation(std::move(addOperation)){}

VarDeclaration::VarDeclaration(std::unique_ptr<Token> ident, std::unique_ptr<Instruction> functionCall)
    :identifier(std::move(ident)), functionCall(std::move(functionCall)){}

VarDeclaration::VarDeclaration(std::unique_ptr<Token> ident, std::unique_ptr<LogicalExpression> logicalExpression)
    :identifier(std::move(ident)), logicalExpression(std::move(logicalExpression)){}

VarDeclaration::VarDeclaration()
{

}
