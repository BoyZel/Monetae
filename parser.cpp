#include "parser.h"
#include "syntax_objects/addoperation.h"
#include "syntax_objects/whileloop.h"
#include "syntax_objects/ifelse.h"
#include "syntax_objects/vardeclaration.h"
#include "syntax_objects/assignment.h"
#include "syntax_objects/return.h"
#include <iostream> //do usuniecia
Parser::Parser()
{

}

Parser::Parser(std::unique_ptr<Lexer> lexer) : lexer(std::move(lexer)){}

void Parser::parseProgram()
{
    std::unique_ptr<Program> parsingProgram(new Program());
    nextToken();
    while(token.type != TokenTypes::EOFTOKEN){
        auto functionDef = parseFunctionDef();
            if(functionDef !=nullptr){
                parsingProgram->addFunctionDef(std::move(functionDef));
                continue;
            }
        auto definition = parseVarDefinition();
        if(definition == nullptr)
            return;
        parsingProgram->addVarDeclaration(std::move(definition));
    }
}

void Parser::nextToken()
{
    token = lexer->getNextToken();
}

std::unique_ptr<FunctionDef> Parser::parseFunctionDef()
{
    if(token.type != TokenTypes::FUNCTION)
        return nullptr;
    nextToken();
    if(token.type != TokenTypes::NAME)
        throw std::runtime_error("Unexpected token");
    auto ident = token;
    nextToken();
    if(token.type != TokenTypes::LEFT_PARENTHESIS)
        throw std::runtime_error("Unexpected token");
    nextToken();
    auto params = parseParameters();
    if(token.type != TokenTypes::RIGHT_PARENTHESIS)
        throw std::runtime_error("Unexpected token");
    nextToken();
    auto block = parseStatementBlock();
    return std::make_unique<FunctionDef>(std::make_unique<Token>(ident), std::move(params), std::move(block));
}

std::unique_ptr<Parameters> Parser::parseParameters()
{
    std::unique_ptr<Parameters> parameters(new Parameters());
    while(token.type == TokenTypes::NAME){
        parameters->addParameter(std::make_unique<Token>(std::move(token)));
        nextToken();
        if(token.type!=TokenTypes::COMMA)
            return parameters;
        nextToken();
    }
    return parameters;
}

std::unique_ptr<StatementBlock> Parser::parseStatementBlock()
{
    if(token.type != TokenTypes::LEFT_BRACE)
        throw std::runtime_error("Unexpected token");
    std::unique_ptr<StatementBlock> block(new StatementBlock());
    nextToken();
    std::unique_ptr<Instruction>instruction(parseInstruction());
    while(instruction != nullptr){
        block->addInstruction(std::move(instruction));
        instruction = parseInstruction();
    }
    if(token.type != TokenTypes::RIGHT_BRACE)
        throw std::runtime_error("Unexpected token");
    nextToken();
    return block;

}

std::unique_ptr<Instruction> Parser::parseInstruction()
{
    auto whileLoop = parseWhileLoop();
    if(whileLoop != nullptr)
        return whileLoop;
    auto ifElse = parseIfElse();
    if(ifElse != nullptr)
        return ifElse;
    auto varDef = parseVarDefinition();
    if(varDef != nullptr)
        return varDef;
    auto assignment = parseAssignment();
    if(assignment != nullptr)
        return assignment;
    auto returnStatement = parseReturn();
    if(returnStatement != nullptr)
        return returnStatement;
    auto functionCall = parseFunctionCall();
    if(functionCall != nullptr)
        return functionCall;
    return nullptr;

}

std::unique_ptr<Instruction> Parser::parseWhileLoop()
{
    if(token.type!=TokenTypes::WHILE)
        return nullptr;
    nextToken();
    if(token.type!=TokenTypes::LEFT_PARENTHESIS)
        throw std::runtime_error("Unexpected token");
    nextToken();
    auto logicalExp = parseLogicalExpression();
    if(token.type!=TokenTypes::RIGHT_PARENTHESIS)
        throw std::runtime_error("Unexpected token");
    nextToken();
    auto block = parseStatementBlock();
    return std::make_unique<WhileLoop>(std::move(logicalExp), std::move(block));
}

std::unique_ptr<Instruction> Parser::parseIfElse()
{
    if(token.type!=TokenTypes::IF)
        return nullptr;
    nextToken();
    if(token.type!=TokenTypes::LEFT_PARENTHESIS)
        throw std::runtime_error("Unexpected token");
    nextToken();
    auto logicalExp = parseLogicalExpression();
    if(token.type!=TokenTypes::RIGHT_PARENTHESIS)
        throw std::runtime_error("Unexpected token");
    nextToken();
    auto ifStatement = parseStatementBlock();
    if(token.type==TokenTypes::ELSE){
        nextToken();
        auto block = parseStatementBlock();
        return std::make_unique<IfElse>(std::move(logicalExp), std::move(ifStatement), std::move(block));
    }
    return std::make_unique<IfElse>(std::move(logicalExp), std::move(ifStatement));
}

std::unique_ptr<Instruction> Parser::parseVarDefinition()
{
    if(token.type!=TokenTypes::VAR)
        return nullptr;
    nextToken();
    if(token.type!=TokenTypes::NAME)
        throw std::runtime_error("Unexpected token");
    auto name = std::make_unique<Token>(token);
    nextToken();
    if(token.type!=TokenTypes::ASSIGN)
        throw std::runtime_error("Unexpected token");
    nextToken();
    auto addOperation = parseAddOperation();
    if(addOperation!=nullptr){
        if(token.type != TokenTypes::SEMICOLON)
            throw std::runtime_error("Unexpected token");
        nextToken();
        return std::make_unique<VarDeclaration>(std::move(name), std::move(addOperation));
    }
    auto funCall = parseFunctionCall();
    if(funCall!=nullptr){
        if(token.type != TokenTypes::SEMICOLON)
            throw std::runtime_error("Unexpected token");
        nextToken();
        return std::make_unique<VarDeclaration>(std::move(name), std::move(funCall));
    }
    auto logicalExp = parseLogicalExpression();
    if(logicalExp!=nullptr){
        if(token.type != TokenTypes::SEMICOLON)
            throw std::runtime_error("Unexpected token");
        nextToken();
        return std::make_unique<VarDeclaration>(std::move(name), std::move(logicalExp));
    }
    throw std::runtime_error("Unexpected token");
}

std::unique_ptr<Instruction> Parser::parseAssignment()
{
    if(token.type!=TokenTypes::NAME)
        return nullptr;
    auto name = std::make_unique<Token>(token);
    nextToken();//problem
    if(token.type!=TokenTypes::ASSIGN)
        return nullptr;
    nextToken();
    auto addOperation = parseAddOperation();
    if(addOperation!=nullptr){
        if(token.type != TokenTypes::SEMICOLON)
            throw std::runtime_error("Unexpected token");
        nextToken();
        return std::make_unique<Assignment>(std::move(name), std::move(addOperation));
    }
    auto funCall = parseFunctionCall();
    if(funCall!=nullptr){
        if(token.type != TokenTypes::SEMICOLON)
            throw std::runtime_error("Unexpected token");
        nextToken();
        return std::make_unique<Assignment>(std::move(name), std::move(funCall));
    }
    auto logicalExp = parseLogicalExpression();
    if(logicalExp!=nullptr){
        if(token.type != TokenTypes::SEMICOLON)
            throw std::runtime_error("Unexpected token");
        nextToken();
        return std::make_unique<Assignment>(std::move(name), std::move(logicalExp));
    }
    throw std::runtime_error("Unexpected token");
}

std::unique_ptr<Instruction> Parser::parseReturn()
{
    if(token.type!=TokenTypes::RETURN)
        return nullptr;
    nextToken();
    auto addOperation = parseAddOperation();
    if(addOperation!=nullptr){
        if(token.type != TokenTypes::SEMICOLON)
            throw std::runtime_error("Unexpected token");
        nextToken();
        return std::make_unique<Return>(std::move(addOperation));
    }
    auto funCall = parseFunctionCall();
    if(funCall!=nullptr){
        if(token.type != TokenTypes::SEMICOLON)
            throw std::runtime_error("Unexpected token");
        nextToken();
        return std::make_unique<Return>(std::move(funCall));
    }
    auto logicalExp = parseLogicalExpression();
    if(logicalExp==nullptr)
        throw std::runtime_error("Unexpected token");
    if(token.type != TokenTypes::SEMICOLON)
        throw std::runtime_error("Unexpected token");
    nextToken();
    return std::make_unique<Return>(std::move(logicalExp));
}

std::unique_ptr<Argument> Parser::parseArgument()
{
    if(token.type == TokenTypes::NAME || token.type == TokenTypes::STRING || token.type == TokenTypes::NUMBER){
        return std::make_unique<Argument>(std::make_unique<Token>(token));
    }
    auto addOperation = parseAddOperation();
    if(addOperation!=nullptr)
        return std::make_unique<Argument>(std::move(addOperation));
    auto logicalExp = parseLogicalExpression();
    if(logicalExp!=nullptr)
        return std::make_unique<Argument>(std::move(logicalExp));
    return nullptr;

}
std::unique_ptr<Instruction> Parser::parseFunctionCall()
{
    if(token.type!=TokenTypes::NAME)
        return nullptr;
    std::unique_ptr<FunctionCall> functionCall(new FunctionCall(std::make_unique<Token>(token)));
    nextToken();
    if(token.type!=TokenTypes::LEFT_PARENTHESIS)
        return nullptr;
    nextToken();
    auto argument = parseArgument();
    if(argument == nullptr){
        if(token.type!=TokenTypes::RIGHT_PARENTHESIS)
            throw std::runtime_error("Unexpected token");
        nextToken();
        return functionCall;
    }
    while(token.type == TokenTypes::COMMA){
        nextToken();
        auto argument = parseArgument();
        if(argument == nullptr)
            throw std::runtime_error("Unexpected token");
        functionCall->addArgument(std::move(argument));
    }
    if(token.type!=TokenTypes::RIGHT_PARENTHESIS)
        throw std::runtime_error("Unexpected token");
    nextToken();
    return functionCall;
}

std::unique_ptr<LogicalExpression> Parser::parseLogicalExpression()
{
    bool l_negation = false;
    if(token.type == TokenTypes::NEGATE){
        l_negation = true;
        nextToken();
    }
    auto expression = parseExpression();
    if(expression == nullptr)
        return nullptr;
    std::unique_ptr<LogicalExpression> logicalExpression(new LogicalExpression(std::move(expression)));
    logicalExpression->setNegation(l_negation);
    while(token.type == TokenTypes::AND || token.type == TokenTypes::OR){
        logicalExpression->addLogicalOp(std::make_unique<Token>(token));
        nextToken();
        auto l_logicalExpression = parseLogicalExpression();
        if(logicalExpression == nullptr)
            throw std::runtime_error("Unexpected token");
        logicalExpression->addLogicalExpression(std::move(l_logicalExpression));
    }
    return logicalExpression;
}

std::unique_ptr<Expression> Parser::parseExpression()
{
    auto l_add_operation1 = parseAddOperation();
    if(l_add_operation1 != nullptr){
        if(token.type != TokenTypes::COMPARE)
            throw std::runtime_error("Unexpected token");
        std::unique_ptr<Token> l_operator(new Token(token));
        nextToken();
        auto l_add_operation2 = parseAddOperation();
        if(l_add_operation2 == nullptr)
            throw std::runtime_error("Unexpected token");
        return std::unique_ptr<Expression>(new Expression(std::move(l_add_operation1), std::move(l_operator), std::move(l_add_operation2)));
    }
    auto logExp = parseLogicalExpression();
    if(logExp == nullptr)
        return nullptr;
    return std::unique_ptr<Expression>(new Expression(std::move(logExp)));
}

std::unique_ptr<AddOperation> Parser::parseAddOperation()
{
    auto multiOp = parseMultiOperation();
    if(multiOp == nullptr)
        return nullptr;
    std::unique_ptr<AddOperation> addOp(new AddOperation(std::move(multiOp)));
    while(token.type == TokenTypes::ADD){
        addOp->addAddOperator(std::make_unique<Token>(token));
        nextToken();
        auto addOper = parseAddOperation();
        if(addOper == nullptr)
            throw std::runtime_error("Unexpected token");
        addOp->addAddOperation(std::move(addOper));
    }
    return addOp;
}

std::unique_ptr<MultiOperation> Parser::parseMultiOperation()
{
    auto factor = parseFactor();
    if(factor == nullptr)
        return nullptr;
    std::unique_ptr<MultiOperation> multiOp(new MultiOperation(std::move(factor)));
    while(token.type == TokenTypes::MULTIPLY){
        multiOp->addMultiOperator(std::make_unique<Token>(token));
        nextToken();
        auto multiOper = parseMultiOperation();
        if(multiOper == nullptr)
            throw std::runtime_error("Unexpected token");
        multiOp->addMultiOperation(std::move(multiOper));
        nextToken();
    }
    return multiOp;
}

std::unique_ptr<Factor> Parser::parseFactor()
{
    bool minus = false;
    if(token.type == TokenTypes::ADD){
        if(token.text == "-"){
            minus = true;
        }
    }
    Token l_number = token;
    if(l_number.type == TokenTypes::NUMBER){
        nextToken();
        if(token.type == TokenTypes::NAME){
            Token l_token = token;
            nextToken();
            auto factor = std::make_unique<Factor>(std::make_unique<Token>(l_number), std::make_unique<Token>(l_token));
            factor->setMinus(minus);
        }
        return std::make_unique<Factor>(std::make_unique<Token>(l_number));
    }
    if(token.type == TokenTypes::NAME){
        Token l_token = token;
        nextToken();
        auto factor = std::make_unique<Factor>(std::make_unique<Token>(l_token));
        factor->setMinus(minus);
        return factor;
    }
    if(token.type != TokenTypes::LEFT_PARENTHESIS)
        return nullptr;
    auto addOp = parseAddOperation();
    if(addOp == nullptr)
        throw std::runtime_error("Unexpected token");
    std::unique_ptr<Factor> factor(new Factor(std::move(addOp)));
    factor->setMinus(minus);
    if(token.type != TokenTypes::RIGHT_PARENTHESIS)
        throw std::runtime_error("Unexpected token");
    nextToken();
    return factor;
}

void Parser::nextConfigToken(){
    token = lexer->getNextTokenFromConfig();
}

void Parser::parseConfig(){
    int index = 0;
    while(token.type == TokenTypes::NAME){
        currencies.emplace(token.text, index);
        index++;
        nextConfigToken();
    }
    for(int i=0;i<index;i++){
        std::vector<double> ex;
        for(int j=0;j<index;j++){
            if(token.type != TokenTypes::NUMBER)
                throw std::runtime_error("Unexpected token");
            if(token.value != 0)
                ex.push_back(token.value);
            else
                ex.push_back(token.valueDouble);
            nextConfigToken();
        }
        exchanges.push_back(ex);
    }
}
