//
// Created by Dominic Järmann on 18/10/2020.
//

#ifndef LIONV8_PARSER_H
#define LIONV8_PARSER_H

#include "../tokenizer/token.h"
#include "AbstractSyntaxTree.h"
#include <vector>

class Parser {
public:
    Parser(std::vector<TokenHolder> *);
    AbstractSyntaxTree* Parse();
private:
    std::vector<TokenHolder> * _tokens;
};


#endif //LIONV8_PARSER_H
