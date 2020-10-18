//
// Created by Dominic Järmann on 16/10/2020.
//

#pragma once

#ifndef LIONV8_TOKEN_H
#define LIONV8_TOKEN_H

#include <string>

enum TokenType {
    KEYWORD,
    IDENTIFIER,
    PUNCTUATOR,
    NUMERIC,
    STRING,
};

struct TokenPosition {
    int line;
    int position;
};
struct TokenHolder {
    TokenType type;
    std::string value;
    TokenPosition position;
};

class Token {
public:
    Token(std::string);

    bool is_digit();

    bool is_string();

    bool is_keyword();

    bool is_identifier();

    bool is_punctuator();

    bool contains_digit();



private:
    std::string value;

};

#endif //LIONV8_TOKEN_H
