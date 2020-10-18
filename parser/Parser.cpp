//
// Created by Dominic Järmann on 18/10/2020.
//

#include "Parser.h"
#include "../helpers/Logger.h"
#include "AbstractSyntaxTree.h"

Parser::Parser(std::vector<TokenHolder> *tokens) {
    this->_tokens = tokens;
}

AbstractSyntaxTree *Parser::Parse() {
    AbstractSyntaxTree *tree = new AbstractSyntaxTree;
    Logger::log("Parsing Tokens to AST");
    return tree;
}
