#ifndef PARAMETERS_H
#define PARAMETERS_H
#include <Token.h>
#include <vector>
#include <memory>
#include "interpreter.h"

class Parameters
{
    std::vector<std::unique_ptr<std::string>> parameters;
public:
    Parameters();
    void addParameter(std::unique_ptr<std::string> next);
    void accept(Interpreter visitor);
};

#endif // PARAMETERS_H
