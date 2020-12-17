#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include "TokenTypes.h"
struct Token{
public:
    std::string text;
    TokenTypes type;
    int line;
    int position;
    int beforeDot=0;
    int afterDot=0;
};

#endif // TOKEN_H
