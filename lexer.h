#ifndef LEXER_H
#define LEXER_H
#include "Token.h"
#include "reader.h"
#include "Tokens.h"
class Lexer
{
public:
    Tokens dictionary;
    std::shared_ptr<Reader> reader;
    int line=0;
    int position=0;
    Lexer(std::shared_ptr<Reader>, std::string configName );
    Token getNextToken();
    void ignoreWhitespaces();
    Token getString();
    Token getNumber();
    Token getName();
    Token getDoubleChar();
    Token getSingleOperator();
    bool readConfig(const std::string name);
};

#endif // LEXER_H
