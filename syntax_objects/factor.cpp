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

Factor::Factor(std::unique_ptr<Token> number, std::unique_ptr<std::string> identifier)
    :number(std::move(number)), identifier(std::move(identifier)){}

Factor::Factor(std::unique_ptr<std::string> identifier)
    :identifier(std::move(identifier)){}

Factor::Factor(std::unique_ptr<Token> number)
    :number(std::move(number)){}

Factor::Factor(std::unique_ptr<AddOperation> addOperation)
    :addOperation(std::move(addOperation)){}

Factor::Factor(std::unique_ptr<Instruction> funCall)
    :funCall(std::move(funCall)){}
