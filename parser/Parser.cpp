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
    for (int it = 0; it < this->_tokens->size(); it++) {
        TokenHolder token = this->_tokens->at(it);
        switch (token.type) {
            case TokenType::KEYWORD:
                this->generateVariableDeclaration(it, token);
                break;
            default:
                Logger::log("Token Type");
        }
    }
    return tree;
}

VariableDeclaration Parser::generateVariableDeclaration(int index, TokenHolder token) {
    VariableDeclaration declaration;
    TokenHolder nextToken = this->_tokens->at(index + 1);
    if(nextToken.type != TokenType::IDENTIFIER){
        Logger::log("Error: Expected identifier but got " + Token::token_to_string(nextToken.type));
    }



    return declaration;
}

