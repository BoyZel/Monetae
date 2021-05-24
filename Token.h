#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include "TokenTypes.h"
struct Token{
public:
    std::string text;
    TokenTypes type;
    int line;
    int positionInLine;
    int absolutePosition;
    int value=0;
    double valueDouble =0;
};

#endif // TOKEN_H
