#include "parameters.h"

Parameters::Parameters()
{

}

void Parameters::addParameter(std::unique_ptr<std::string> next)
{
    parameters.push_back(std::move(next));
}
