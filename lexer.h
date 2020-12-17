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
    int line;
    int position;
    Lexer(std::shared_ptr<Reader>);
    Token getNextToken();
    void ignoreWhitespaces();
    Token getString();
    Token getNumber();
    Token getName();
    Token getDoubleChar();
    Token getSingleOperator();
};

#endif // LEXER_H
