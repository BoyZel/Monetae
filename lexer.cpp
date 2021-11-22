#include "lexer.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <tgmath.h>
Lexer::Lexer(std::unique_ptr<Reader> aReader) : reader(std::move(aReader))
{
    //readConfig(configName);
}

Token Lexer::getNextToken(){
    ignoreWhitespacesAndComments();
    lockPosition();
    Token token;
    token = getString();
    if(token.type.has_value())
        return token;
    token = getNumber();
    if(token.type.has_value())
        return token;
    token = getName();
    if(token.type.has_value())
        return token;
    token = getDoubleChar();
    if(token.type.has_value())
        return token;
    return getSingleOperator();
}

Token Lexer::getNextTokenFromConfig()
{
    ignoreWhitespacesAndComments();
    Token token;
    token = getNumber();
    if(token.type.has_value())
        return token;
    token = getName();
    if(token.type.has_value())
        return token;
    return getSingleOperator();
}

void Lexer::ignoreWhitespacesAndComments()
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
            isComment = false;
            continue;
        }
    }
}

Token Lexer::getString()
{
    Token token;
    if(reader->peekChar() != '"')
        return token;
    char single;
    reader.get();
    setPosition(token);
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
    }
    reader->unget();
    return token;
}

Token Lexer::getName()
{
    Token token;
    char single = reader->peekChar();
    if(! (isalpha(single) || single == '_'))
        return token;
    setPosition(token);
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
    if(!dictionary.dangerous.count(reader->peekChar()))
        return token;
    setPosition(token);
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
    setPosition(token);
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

void Lexer::lockPosition()
{
    tokenLine = reader->getLine();
    tokenAbsolutePosition = reader->tellg();
    tokenPositionInLine = reader->getPositionInLine();
}

void Lexer::setPosition(Token &token)
{
    token.line = tokenLine;
    token.absolutePosition = tokenAbsolutePosition;
    token.positionInLine = tokenPositionInLine;
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
    if(!isdigit(reader->peekChar()))
        return token;
    char single = reader->getChar();
    setPosition(token);
    token.value = single - '0';
    if(token.value == 0 && reader->peekChar()!='.'){
        token.type = TokenTypes::NUMBER;
        if(isdigit(reader->peekChar()))
            token.type.reset();
        return token;
    }
    while(isdigit(single = reader->getChar())){
        token.value = token.value*10 + single - '0';
        if(token.value>200000000){
            token.type = TokenTypes::ERROR_TOO_LONG;
            return token;
        }
    }
    if(single == '.'){
        int count=10;
        if(!isdigit(reader->peekChar())){
            return token;
        }
        token.valueDouble = token.value;
        token.value = 0;
        while(isdigit(single = reader->getChar())){
            token.valueDouble += (double)(single - '0')/count;
            count = count*10;
        }
    }
    if(single == 'e' || single == 'E'){
        if(!isdigit(reader->peekChar()))
            return token;
        int exp = reader->getChar() - '0';
        if(exp == 0){
            token.type = TokenTypes::NUMBER;
            if(isdigit(reader->peekChar())) //zakres
                token.type.reset();
            return token;
        }
        while(isdigit(single = reader->getChar())){
            exp = exp*10 + single - '0';
        }
        if(token.value == 0){
            token.valueDouble = std::pow(token.valueDouble, exp);
        }
        else{
            token.value = token.value^exp;
        }
    }
    reader->unget();
    token.type = TokenTypes::NUMBER;
    return token;
}
