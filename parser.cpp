#include "parser.h"
#include "syntax_objects/addoperation.h"
#include "syntax_objects/whileloop.h"
#include "syntax_objects/ifelse.h"
#include "syntax_objects/vardeclaration.h"
#include "syntax_objects/assignment.h"
#include "syntax_objects/return.h"
#include <iostream>
Parser::Parser()
{

}

Parser::Parser(std::unique_ptr<Lexer> lexer) : lexer(std::move(lexer)){}

void Parser::parseProgram()
{
    std::unique_ptr<Program> parsingProgram(new Program());
    nextToken();
    std::unique_ptr<FunctionDef> functionDef;
    std::unique_ptr<Instruction> varDefinition;
    while((functionDef = parseFunctionDef()) != nullptr || ((varDefinition = parseVarDefinition()) != nullptr)){
        if(functionDef !=nullptr)
            parsingProgram->addFunctionDef(std::move(functionDef));
        if(varDefinition != nullptr)
            parsingProgram->addVarDeclaration(std::move(varDefinition));

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
    forceTokenType(TokenTypes::NAME);
    auto ident = token;
    nextToken();
    forceTokenTypeAndGetNext(TokenTypes::LEFT_PARENTHESIS);
    auto params = parseParameters();
    forceTokenTypeAndGetNext(TokenTypes::RIGHT_PARENTHESIS);
    auto block = parseStatementBlock();
    return std::make_unique<FunctionDef>(std::make_unique<std::string>(ident.text), std::move(params), std::move(block));
}

std::unique_ptr<Parameters> Parser::parseParameters()
{
    std::unique_ptr<Parameters> parameters(new Parameters());
    if(token.type == TokenTypes::NAME){
        parameters->addParameter(std::make_unique<std::string>(std::move(token.text)));
        nextToken();
        while(token.type == TokenTypes::COMMA){
            nextToken();
            forceTokenType(TokenTypes::NAME);
            parameters->addParameter(std::make_unique<std::string>(std::move(token.text)));
            nextToken();
        }
    }
    return parameters;
}

std::unique_ptr<StatementBlock> Parser::parseStatementBlock()
{
    forceTokenTypeAndGetNext(TokenTypes::LEFT_BRACE);
    std::unique_ptr<StatementBlock> block(new StatementBlock());
    std::unique_ptr<Instruction>instruction(parseInstruction());
    while(instruction != nullptr){
        block->addInstruction(std::move(instruction));
        instruction = parseInstruction();
    }
    forceTokenTypeAndGetNext(TokenTypes::RIGHT_BRACE);
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
    auto returnStatement = parseReturn();
    if(returnStatement != nullptr)
        return returnStatement;
    if(token.type == TokenTypes::NAME){
        Token l_token = token;
        nextToken();
        auto assignment = parseAssignment(l_token);
        if(assignment != nullptr)
            return assignment;
        auto functionCall = parseFunctionCall(l_token);
        if(functionCall != nullptr)
            return functionCall;
        throw std::runtime_error("Unexpected token");
    }
    return nullptr;

}

std::unique_ptr<Instruction> Parser::parseWhileLoop()
{
    if(token.type!=TokenTypes::WHILE)
        return nullptr;
    nextToken();
    forceTokenTypeAndGetNext(TokenTypes::LEFT_PARENTHESIS);
    auto logicalExp = parseLogicalExpression();
    forceTokenTypeAndGetNext(TokenTypes::RIGHT_PARENTHESIS);
    auto block = parseStatementBlock();
    return std::make_unique<WhileLoop>(std::move(logicalExp), std::move(block));
}

std::unique_ptr<Instruction> Parser::parseIfElse()
{
    if(token.type!=TokenTypes::IF)
        return nullptr;
    nextToken();
    forceTokenTypeAndGetNext(TokenTypes::LEFT_PARENTHESIS);
    auto logicalExp = parseLogicalExpression();
    forceTokenTypeAndGetNext(TokenTypes::RIGHT_PARENTHESIS);
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
    forceTokenType(TokenTypes::NAME);
    auto name = std::make_unique<std::string>(token.text);
    nextToken();
    forceTokenTypeAndGetNext(TokenTypes::ASSIGN);
    auto addOperation = parseAddOperation();
    if(addOperation!=nullptr){
        forceTokenTypeAndGetNext(TokenTypes::SEMICOLON);
        return std::make_unique<VarDeclaration>(std::move(name), std::move(addOperation));
    }
    if(token.type == TokenTypes::NAME){
        auto l_token = token;
        nextToken();
        auto funCall = parseFunctionCall(l_token);
        if(funCall!=nullptr){
            forceTokenTypeAndGetNext(TokenTypes::SEMICOLON);
            return std::make_unique<VarDeclaration>(std::move(name), std::move(funCall));
        }
        throw std::runtime_error("Unexpected token");
    }
    auto logicalExp = parseLogicalExpression();
    if(logicalExp!=nullptr){
        forceTokenTypeAndGetNext(TokenTypes::SEMICOLON);
        return std::make_unique<VarDeclaration>(std::move(name), std::move(logicalExp));
    }
    throw std::runtime_error("Unexpected token");
}

std::unique_ptr<Instruction> Parser::parseAssignment(Token identifier)
{
    if(token.type!=TokenTypes::ASSIGN)
        return nullptr;
    auto name = std::make_unique<std::string>(identifier.text);
    nextToken();
    auto addOperation = parseAddOperation();
    if(addOperation!=nullptr){
        forceTokenTypeAndGetNext(TokenTypes::SEMICOLON);
        return std::make_unique<Assignment>(std::move(name), std::move(addOperation));
    }
    if(token.type == TokenTypes::NAME){
        auto l_token = token;
        nextToken();
        auto funCall = parseFunctionCall(l_token);
        if(funCall!=nullptr){
            forceTokenTypeAndGetNext(TokenTypes::SEMICOLON);
            return std::make_unique<Assignment>(std::move(name), std::move(funCall));
        }
        throw std::runtime_error("Unexpected token");
    }
    auto logicalExp = parseLogicalExpression();
    if(logicalExp!=nullptr){
        forceTokenTypeAndGetNext(TokenTypes::SEMICOLON);
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
        forceTokenTypeAndGetNext(TokenTypes::SEMICOLON);
        return std::make_unique<Return>(std::move(addOperation));
    }
    if(token.type == TokenTypes::NAME){
        auto l_token = token;
        nextToken();
        auto funCall = parseFunctionCall(l_token);
        if(funCall!=nullptr){
            forceTokenTypeAndGetNext(TokenTypes::SEMICOLON);
            return std::make_unique<Return>(std::move(funCall));
        }
        throw std::runtime_error("Unexpected token");
    }
    auto logicalExp = parseLogicalExpression();
    if(logicalExp==nullptr)
        throw std::runtime_error("Unexpected token");
    forceTokenTypeAndGetNext(TokenTypes::SEMICOLON);
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
std::unique_ptr<Instruction> Parser::parseFunctionCall(Token identifier)
{
    std::unique_ptr<FunctionCall> functionCall(new FunctionCall(std::make_unique<std::string>(identifier.text)));
    nextToken();
    if(token.type!=TokenTypes::LEFT_PARENTHESIS)
        return nullptr;
    nextToken();
    auto argument = parseArgument();
    if(argument != nullptr){
        functionCall->addArgument(std::move(argument));
        while(token.type == TokenTypes::COMMA){
            nextToken();
            auto argument = parseArgument();
            if(argument == nullptr)
                throw std::runtime_error("Unexpected token");
            functionCall->addArgument(std::move(argument));
        }
    }
    forceTokenTypeAndGetNext(TokenTypes::RIGHT_PARENTHESIS);
    return functionCall;
}

std::unique_ptr<LogicalExpression> Parser::parseLogicalExpression()
{
    auto expression = parseExpression();
    if(expression == nullptr)
        return nullptr;
    std::unique_ptr<LogicalExpression> logicalExpression(new LogicalExpression(std::move(expression)));
 //   logicalExpression->setNegation(l_negation);
    while(token.type == TokenTypes::AND || token.type == TokenTypes::OR){
        logicalExpression->addLogicalOp(std::make_unique<std::string>(token.text));
        nextToken();
        auto l_Expression = parseExpression();
        if(l_Expression == nullptr)
            throw std::runtime_error("Unexpected token");
        logicalExpression->addExpression(std::move(l_Expression));
    }
    return logicalExpression;
}

std::unique_ptr<Expression> Parser::parseExpression()
{
    auto pExp = parsePrimaryExpression();
    if(pExp != nullptr){
        forceTokenType(TokenTypes::COMPARE);
        std::unique_ptr<std::string> l_operator(new std::string(token.text));
        nextToken();
        auto pExp2 = parsePrimaryExpression();
        if(pExp2 == nullptr)
            throw std::runtime_error("Unexpected token");
        return std::unique_ptr<Expression>(new Expression(std::move(pExp), std::move(l_operator), std::move(pExp2)));
    }
    throw std::runtime_error("Unexpected token");
}

std::unique_ptr<PrimaryExpression> Parser::parsePrimaryExpression(){
    bool l_negation = false;
    if(token.type == TokenTypes::NEGATE){
        l_negation = true;
        nextToken();
    }
    if(token.type == TokenTypes::LEFT_PARENTHESIS){
        nextToken();
        auto logExp = parseLogicalExpression();
        if(logExp == nullptr)
            throw std::runtime_error("Unexpected token");
        forceTokenTypeAndGetNext(TokenTypes::RIGHT_PARENTHESIS);
        std::unique_ptr<PrimaryExpression> pExp(new PrimaryExpression(std::move(logExp)));
        pExp->setNegation(l_negation);
        return pExp;
    }
    auto addOperation = parseAddOperation();
    if(addOperation == nullptr)
        throw std::runtime_error("Unexpected token");
    std::unique_ptr<PrimaryExpression> pExp(new PrimaryExpression(std::move(addOperation)));
    pExp->setNegation(l_negation);
    return pExp;
}

std::unique_ptr<AddOperation> Parser::parseAddOperation()
{
    auto multiOp = parseMultiOperation();
    if(multiOp == nullptr)
        return nullptr;
    std::unique_ptr<AddOperation> addOp(new AddOperation(std::move(multiOp)));
    while(token.type == TokenTypes::ADD){
        addOp->addAddOperator(std::make_unique<std::string>(token.text));
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
        multiOp->addMultiOperator(std::make_unique<std::string>(token.text));
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
            auto factor = std::make_unique<Factor>(std::make_unique<Token>(l_number), std::make_unique<std::string>(l_token.text));
            factor->setMinus(minus);
        }
        return std::make_unique<Factor>(std::make_unique<Token>(l_number));
    }
    if(token.type == TokenTypes::NAME){
        Token l_token = token;
        auto call = parseFunctionCall(l_token);
        if(call != nullptr){
            auto factor = std::make_unique<Factor>(std::move(call));
            factor->setMinus(minus);
            return factor;
        }
        auto factor = std::make_unique<Factor>(std::make_unique<std::string>(l_token.text));
        factor->setMinus(minus);
        return factor;
    }
    if(token.type != TokenTypes::LEFT_PARENTHESIS){
        if(minus)
            throw std::runtime_error("Unexpected token");
        return nullptr;
    }
    auto addOp = parseAddOperation();
    if(addOp == nullptr)
        throw std::runtime_error("Unexpected token");
    std::unique_ptr<Factor> factor(new Factor(std::move(addOp)));
    factor->setMinus(minus);
    forceTokenTypeAndGetNext(TokenTypes::RIGHT_PARENTHESIS);
    return factor;
}

void Parser::forceTokenType(TokenTypes type)
{
    if(token.type != type)
        throw std::runtime_error("Unexpected token");
}

void Parser::forceTokenTypeAndGetNext(TokenTypes type)
{
    forceTokenType(type);
    nextToken();
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
            forceTokenType(TokenTypes::NUMBER);
            if(token.value != 0)
                ex.push_back(token.value);
            else
                ex.push_back(token.valueDouble);
            nextConfigToken();
        }
        exchanges.push_back(ex);
    }
}
