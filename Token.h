#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include "TokenTypes.h"
#include <optional>
struct Token{
public:
    std::string text;
    std::optional<TokenTypes> type;
    int line;
    int positionInLine;
    int absolutePosition;
    int value=0;
    double valueDouble =0;
};

#endif // TOKEN_H
