#include "lexer.h"
#include <cctype>
#include <fstream>
#include <iostream>
Lexer::Lexer(std::shared_ptr<Reader> aReader, std::string configName) : reader(aReader)
{
    readConfig(configName);
}

Token Lexer::getNextToken(){
    ignoreWhitespaces();
    char single = reader->peekChar();
    if(single == '"')
        return getString();
    if(isdigit(single))
        return getNumber();
    if(isalpha(single) || single == '_')
        return getName();
    if(dictionary.dangerous.count(single))
        return getDoubleChar();
    return getSingleOperator();
}

void Lexer::ignoreWhitespaces()
{
    bool isComment = 0;
    char tmp;
    while((tmp = reader->getChar()) == ' ' || tmp == '/' || tmp == 10 || tmp == 13 || tmp ==9 || isComment){
        if(tmp == '/'){
            if(!isComment){
                if(reader->peekChar() != '/')
                    break;
                else
                    isComment = true;
            }
        }
        if(tmp == 10){
            line++;
            position = 0;
            isComment = false;
            continue;
        }
        position++;
    }
    reader->unget();
}

Token Lexer::getString()
{
    Token token;
    char single;
    reader.get();
    token.line = line;
    token.position = position;
    token.type = TokenTypes::STRING;
    if(reader->peekChar() == '"')
        return token;
    while((single = reader->getChar()) != std::char_traits<char>::eof()){
        if(token.text.size()>10000){
            token.type = TokenTypes::ERROR_TOO_LONG;
            return token;
        }
        if(single == '"' && token.text.back() != '\\')
            return token;
        token.text.push_back(single);
        position++;
        if(single == 10){
            line++;
            position=0;
        }
    }
    reader->unget();
    return token;
}

Token Lexer::getName()
{
    Token token;
    char single;
    token.line = line;
    token.position = position;
    while(isalpha(single = reader->getChar()) || single == '_'){
        if(token.text.size()>10000){
            token.type = TokenTypes::ERROR_TOO_LONG;
            return token;
        }
        token.text.push_back(single);
        position++;
    }
    reader->unget();
    auto x = dictionary.keywords.find(token.text);
    if(x != dictionary.keywords.end())
        token.type = x->second;
    else{
    auto y = dictionary.currencies.find(token.text);
        if(y != dictionary.currencies.end())
            token.type = TokenTypes::CURRENCY;
        else{
            token.type = TokenTypes::NAME;
        }
    }
    return token;
}

Token Lexer::getDoubleChar()
{
    Token token;
    token.line = line;
    token.position = position;
    token.text.push_back(reader->getChar());
    token.text.push_back(reader->getChar());
    position+=2;
    auto x = dictionary.double_operators.find(token.text);
    if(x != dictionary.double_operators.end())
        token.type = x->second;
    else{
        auto y = dictionary.single_operators.find(token.text[0]);
        token.type = y->second;
        token.text.pop_back();
        reader->unget();
        position--;
    }
    return token;
}

Token Lexer::getSingleOperator()
{
    Token token;
    token.line = line;
    token.position = position;
    token.text.push_back(reader->getChar());
    position++;
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

Token Lexer::getNumber()
{
    char single = reader->getChar();
    Token token;
    token.line = line;
    token.position = position;
    position++;
    token.type = TokenTypes::NUMBER;
    if(single == '0'){
        char next = reader->peekChar();
        if(next != '.')
            return token;
        else{
            reader->getChar();
            while(isdigit(single = reader->getChar())){
                token.afterDot = token.afterDot*10 + single - '0';
                position++;
                if(token.afterDot>200000000){
                    token.type = TokenTypes::ERROR_TOO_LONG;
                    return token;
                }
            }
            reader->unget();
            return token;
        }
    }
    token.beforeDot = single - '0';
    while(isdigit(single = reader->getChar())){
        token.beforeDot = token.beforeDot*10 + single - '0';
        position++;
        if(token.beforeDot>200000000){
            token.type = TokenTypes::ERROR_TOO_LONG;
            return token;
        }
    }
    if(single != '.'){
        reader->unget();
        return token;
    }
    while(isdigit(single = reader->getChar())){
        token.afterDot = token.afterDot*10 + single - '0';
        position++;
        if(token.afterDot>200000000){
            token.type = TokenTypes::ERROR_TOO_LONG;
            return token;
        }
    }
    return token;
}
