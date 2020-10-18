//
// Created by Dominic Järmann on 16/10/2020.
//

#pragma once

#include <string>
#include "token.h"

#ifndef LIONV8_TOKENIZER_H
#define LIONV8_TOKENIZER_H

class Tokenizer {
public:
    Tokenizer(std::string);
    std::vector<TokenHolder> *Tokenitze();
private:
    std::string tokenizeStr;
    uint line = 0;
    uint position = 0;
    uint readChars = 0;

    TokenHolder next();
    bool isEOF();
    std::string readUntilDelimiter();
};


#endif //LIONV8_TOKENIZER_H
