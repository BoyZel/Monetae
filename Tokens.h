#ifndef TOKENS_H
#define TOKENS_H
#include "TokenTypes.h"
#include <unordered_map>
#include <string>
#include <set>
#include <vector>
class Tokens{
public:
    std::unordered_map<std::string, TokenTypes>keywords = {
        {"if", TokenTypes::IF},
        {"else", TokenTypes::ELSE},
        {"while", TokenTypes::WHILE},
        {"return", TokenTypes::RETURN},
        {"var", TokenTypes::VAR},
        {"main", TokenTypes::MAIN},
        {"break", TokenTypes::BREAK},
        {"continue", TokenTypes::CONTINUE},
        {"function", TokenTypes::FUNCTION}
    };

    std::unordered_map<char, TokenTypes>single_operators = {
        {'(', TokenTypes::LEFT_PARENTHESIS},
        {')', TokenTypes::RIGHT_PARENTHESIS},
        {'{', TokenTypes::LEFT_BRACE},
        {'}', TokenTypes::RIGHT_BRACE},
        {'+', TokenTypes::ADD},
        {'-', TokenTypes::ADD},
        {'*', TokenTypes::MULTIPLY},
        {'/', TokenTypes::MULTIPLY},
        {'=', TokenTypes::ASSIGN},
        {'>', TokenTypes::COMPARE},
        {'<', TokenTypes::COMPARE},
        {',', TokenTypes::COMMA},
        {';', TokenTypes::SEMICOLON},
        {'!', TokenTypes::NEGATE},
        {'.', TokenTypes::DOT}
    };

    std::unordered_map<std::string, TokenTypes>double_operators = {
        {"==", TokenTypes::EQUAL},
        {"!=", TokenTypes::NOT_EQUAL},
        {">=", TokenTypes::COMPARE},
        {"<=", TokenTypes::COMPARE},
        {"&&", TokenTypes::AND},
        {"||", TokenTypes::OR}
    };
    std::set<char>dangerous = {
        '=', '!', '>', '<', '&', '|'
    };
    std::unordered_map<std::string, int> currencies;
    std::vector<std::vector<std::pair<int, int>>> exchanges;
};

#endif // TOKENS_H
