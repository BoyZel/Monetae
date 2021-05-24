#ifndef PARAMETERS_H
#define PARAMETERS_H
#include <Token.h>
#include <vector>
#include <memory>
class Parameters
{
    std::vector<std::unique_ptr<Token>> parameters;
public:
    Parameters();
    void addParameter(std::unique_ptr<Token> next);
};

#endif // PARAMETERS_H
