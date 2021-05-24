#include "factor.h"

bool Factor::getMinus() const
{
    return minus;
}

void Factor::setMinus(bool value)
{
    minus = value;
}

Factor::Factor()
{

}

Factor::Factor(std::unique_ptr<Token> number, std::unique_ptr<Token> identifier)
    :number(std::move(number)), identifier(std::move(identifier)){}

Factor::Factor(std::unique_ptr<Token> identifier)
    :identifier(std::move(identifier)){}

Factor::Factor(std::unique_ptr<AddOperation> addOperation)
    :addOperation(std::move(addOperation)){}
