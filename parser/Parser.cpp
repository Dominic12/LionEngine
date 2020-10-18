//
// Created by Dominic Järmann on 18/10/2020.
//

#include "Parser.h"
#include "../helpers/Logger.h"
#include "AbstractSyntaxTree.h"
#include <tuple>

Parser::Parser(std::vector<TokenHolder> *tokens) {
    this->_tokens = tokens;
}

AbstractSyntaxTree *Parser::Parse() {
    AbstractSyntaxTree *tree = new AbstractSyntaxTree;
    for (int it = 0; it < this->_tokens->size(); it++) {
        TokenHolder token = this->_tokens->at(it);
        switch (token.type) {
            case TokenType::KEYWORD:
                it = std::get<int>(this->generateVariableDeclaration(it, token)) + 1;
                break;
            default:
                Logger::log("Token Type: " + Token::token_to_string(token.type) + " is not handled yet");
        }
    }
    return tree;
}

std::tuple<VariableDeclaration *, int> Parser::generateVariableDeclaration(int index, TokenHolder token) {
    VariableDeclaration *declaration = new VariableDeclaration;

    if (token.value == "let") {
        declaration->Kind = VariableDeclarationKind::Let;
        Logger::log("Token type detected let");
    }

    if (token.value == "const") {
        declaration->Kind = VariableDeclarationKind::Const;
        Logger::log("Token type detected const");

    }

    if (token.value == "var") {
        declaration->Kind = VariableDeclarationKind::Var;
        Logger::log("Token type detected var");
    }

    if (this->_tokens->at(index + 1).type != TokenType::IDENTIFIER) {
        Logger::log("Error: Expected identifier but got " + Token::token_to_string(this->_tokens->at(index + 1).type));
        return std::make_tuple(nullptr, index);
    }

    declaration->identifier.Name = this->_tokens->at(index + 1).value;
    declaration->identifier.Type = TokenType::IDENTIFIER;


    if (this->_tokens->at(index + 2).type == TokenType::PUNCTUATOR) {
        // Only declare variable..
        return std::make_tuple(declaration, index + 3);
    }


    // check for correct syntax

    if (this->_tokens->at(index + 3).type != TokenType::PUNCTUATOR || this->_tokens->at(index + 3).value != "=") {
        Logger::log("Error: Expected assignment operator but got  " + this->_tokens->at(index + 3).value);
        return std::make_tuple(nullptr, index);
    }

    if (this->_tokens->at(index + 4).type != TokenType::NUMERIC &&
        this->_tokens->at(index + 4).type != TokenType::STRING) {
        Logger::log("Error: Expected number or string type");
        return std::make_tuple(nullptr, index);
    }

    // Declare and assign value is what is wanted.

    if (this->_tokens->at(index + 4).type == TokenType::NUMERIC) {
        declaration->Statement.value = (void *) _tokens->at(index + 4).value.c_str();
        declaration->Statement.Type = ExpressionType::NumericExpression;
    }
    if (this->_tokens->at(index + 4).type == TokenType::STRING) {
        declaration->Statement.value = (void *) _tokens->at(index + 4).value.c_str();
        declaration->Statement.Type = ExpressionType::LiteralExpression;
    }


    return std::make_tuple(declaration, index);
}

