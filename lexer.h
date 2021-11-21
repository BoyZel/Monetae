#ifndef LEXER_H
#define LEXER_H
#include "Token.h"
#include "reader.h"
#include "Tokens.h"
class Lexer
{
private:
    Tokens dictionary;
    std::unique_ptr<Reader> reader;
    int tokenPositionInLine;
    int tokenLine;
    int tokenAbsolutePosition;
public:
    static constexpr int maxLength = 200;
    Lexer(std::unique_ptr<Reader>);
    Token getNextToken();
    Token getNextTokenFromConfig();
    void ignoreWhitespacesAndComments();
    Token getString();
    Token getNumber();
    Token getName();
    Token getDoubleChar();
    Token getSingleOperator();
    void lockPosition();
    void setPosition(Token &token);
    bool readConfig(const std::string name);
};

#endif // LEXER_H
