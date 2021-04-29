#include "lexer.h"
#include <cctype>
#include <fstream>
#include <iostream>
Lexer::Lexer(std::shared_ptr<Reader> aReader) : reader(aReader)
{
    //readConfig(configName);
}

Token Lexer::getNextToken(){
    ignoreWhitespaces();
    Token token;
    token = getString();
    if(token.type != TokenTypes::WRONG)
        return token;
    token = getNumber();
    if(token.type != TokenTypes::WRONG)
        return token;
    token = getName();
    if(token.type != TokenTypes::WRONG)
        return token;
    token = getDoubleChar();
    if(token.type != TokenTypes::WRONG)
        return token;
    return getSingleOperator();
}

Token Lexer::getNextTokenFromConfig()
{
    ignoreWhitespaces();
    Token token;
    token = getNumber();
    if(token.type != TokenTypes::WRONG)
        return token;
    token = getName();
    if(token.type != TokenTypes::WRONG)
        return token;
    return getSingleOperator();
}

void Lexer::ignoreWhitespaces()
{
    bool isComment = 0;
    char tmp;
    while((tmp = reader->peekChar()) == ' ' || tmp == '/' || tmp == 10 || tmp == 13 || tmp == 9 || isComment){
        reader->getChar();
        if(tmp == '/'){
            if(!isComment){
                if(reader->peekChar() != '/'){
                    reader->unget();
                    break;
                }
                else
                    isComment = true;
            }
        }
        if(tmp == 10){
            reader->setNewLine();
            isComment = false;
            continue;
        }
    }
}

Token Lexer::getString()
{
    Token token;
    if(reader->peekChar() != '"'){
        token.type = TokenTypes::WRONG;
        return token;
    }
    char single;
    reader.get();
    token.line = reader->getLine();
    token.absolutePosition = reader->getAbsolutePosition();
    token.positionInLine = reader->getPositionInLine();
    token.type = TokenTypes::STRING;
    if(reader->peekChar() == '"')
        return token;
    while((single = reader->getChar()) != std::char_traits<char>::eof()){
        if(token.text.size()>maxLength){
            token.type = TokenTypes::ERROR_TOO_LONG;
            return token;
        }
        if(single == '"' && token.text.back() != '\\')
            return token;
        token.text.push_back(single);
        if(single == 10){
            reader->setNewLine();
        }
    }
    reader->unget();
    return token;
}

Token Lexer::getName()
{
    Token token;
    char single = reader->peekChar();
    if(! (isalpha(single) || single == '_')){
        token.type = TokenTypes::WRONG;
        return token;
    }
    token.line = reader->getLine();
    token.absolutePosition = reader->getAbsolutePosition();
    token.positionInLine = reader->getPositionInLine();
    while(isalpha(single = reader->getChar()) || single == '_'){
        if(token.text.size()>maxLength){
            token.type = TokenTypes::ERROR_TOO_LONG;
            return token;
        }
        token.text.push_back(single);
    }
    reader->unget();
    auto x = dictionary.keywords.find(token.text);
    if(x != dictionary.keywords.end())
        token.type = x->second;
    else
        token.type = TokenTypes::NAME;
    return token;
}

Token Lexer::getDoubleChar()
{
    Token token;
    if(!dictionary.dangerous.count(reader->peekChar())){
        token.type = TokenTypes::WRONG;
        return token;
    }
    token.line = reader->getLine();
    token.absolutePosition = reader->getAbsolutePosition();
    token.positionInLine = reader->getPositionInLine();
    token.text.push_back(reader->getChar());
    token.text.push_back(reader->getChar());
    auto x = dictionary.double_operators.find(token.text);
    if(x != dictionary.double_operators.end())
        token.type = x->second;
    else{
        auto y = dictionary.single_operators.find(token.text[0]);
        token.type = y->second;
        token.text.pop_back();
        reader->unget();
    }
    return token;
}

Token Lexer::getSingleOperator()
{
    Token token;
    token.line = reader->getLine();
    token.absolutePosition = reader->getAbsolutePosition();
    token.positionInLine = reader->getPositionInLine();
    token.text.push_back(reader->getChar());
    auto y = dictionary.single_operators.find(token.text[0]);
    if(y != dictionary.single_operators.end())
        token.type = y->second;
    else{
        if(token.text[0] == std::char_traits<char>::eof())
            token.type = TokenTypes::EOFTOKEN;
        else
            token.type = TokenTypes::OTHER;
    }
    return token;
}
/*
bool Lexer::readConfig(const std::string name)
{
    std::ifstream stream(name, std::ios::in | std::ios::binary);
    if(!stream)
        return false;
    int numOfCurrencies;
    stream>>numOfCurrencies;
    for(int i=0; i<numOfCurrencies; i++){
        std::string tmp;
        stream>>tmp;
        dictionary.currencies.emplace(tmp, i);
    }
    for(int i=0;i<numOfCurrencies;i++){
        std::vector<std::pair<int,int>> exchange;
        for(int j=0;j<numOfCurrencies;j++){
            int preDot = 0, afterDot = 0;
            stream>>preDot;
            if(stream.get() == '.')
                stream>>afterDot;
            exchange.emplace_back(preDot, afterDot);
        }
        dictionary.exchanges.push_back(exchange);
    }
    return true;
}
*/

Token Lexer::getNumber()
{
    Token token;
    if(!isdigit(reader->peekChar())){
        token.type = TokenTypes::WRONG;
        return token;
    }
    char single = reader->getChar();
    token.line = reader->getLine();
    token.absolutePosition = reader->getAbsolutePosition();
    token.positionInLine = reader->getPositionInLine();
    token.type = TokenTypes::NUMBER;
    token.value = single - '0';
    while(isdigit(single = reader->getChar())){
        token.value = token.value*10 + single - '0';
        if(token.value>200000000){
            token.type = TokenTypes::ERROR_TOO_LONG;
            return token;
        }
    }
    reader->unget();
    return token;
}
