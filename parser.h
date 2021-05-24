#ifndef PARSER_H
#define PARSER_H

#include "syntax_objects/program.h"
#include "lexer.h"
class Parser
{
    Token token;
    std::unique_ptr<Lexer> lexer;
    std::unique_ptr<Program> program;
public:
    Parser();
    Parser(std::unique_ptr<Lexer> lexer);

    void parseProgram();
    void nextToken();
    std::unique_ptr<FunctionDef> parseFunctionDef();
    std::unique_ptr<Parameters> parseParameters();
    std::unique_ptr<StatementBlock> parseStatementBlock();
    std::unique_ptr<Instruction> parseInstruction();
    std::unique_ptr<Instruction> parseWhileLoop();
    std::unique_ptr<Instruction> parseIfElse();
    std::unique_ptr<Instruction> parseVarDefinition();
    std::unique_ptr<Instruction> parseAssignment();
    std::unique_ptr<Instruction> parseReturn();
    std::unique_ptr<Argument> parseArgument();
    std::unique_ptr<Instruction> parseFunctionCall();
    std::unique_ptr<LogicalExpression> parseLogicalExpression();
    std::unique_ptr<Expression> parseExpression();
    std::unique_ptr<AddOperation> parseAddOperation();
    std::unique_ptr<MultiOperation> parseMultiOperation();
    std::unique_ptr<Factor> parseFactor();
};

#endif // PARSER_H
