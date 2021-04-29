#ifndef LEXER_H
#define LEXER_H
#include "Token.h"
#include "reader.h"
#include "Tokens.h"
class Lexer
{
private:
    Tokens dictionary;
    std::shared_ptr<Reader> reader;
public:
    static constexpr int maxLength = 200;
    Lexer(std::shared_ptr<Reader>);
    Token getNextToken();
    Token getNextTokenFromConfig();
    void ignoreWhitespaces();
    Token getString();
    Token getNumber();
    Token getName();
    Token getDoubleChar();
    Token getSingleOperator();
    bool readConfig(const std::string name);
};

#endif // LEXER_H
