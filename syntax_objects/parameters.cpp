#include "parameters.h"

Parameters::Parameters()
{

}

void Parameters::addParameter(std::unique_ptr<Token> next)
{
    parameters.push_back(std::move(next));
}
