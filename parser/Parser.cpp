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
    tree->program = new BlockStatement;
    tree->program = std::get<BlockStatement *>(this->generateBlockStatement(0, this->_tokens->at(0)));


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
        Logger::log("Error: Expected identifier but got " + Token::type_to_string(this->_tokens->at(index + 1).type));
        return std::make_tuple(nullptr, index);
    }

    declaration->identifier.name = this->_tokens->at(index + 1).value;
    declaration->identifier.type = TokenType::IDENTIFIER;


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

std::tuple<FunctionDeclaration *, int> Parser::generateFunctionDeclaration(int index, TokenHolder token) {
    FunctionDeclaration *functionDeclaration = new FunctionDeclaration;
    if (this->_tokens->at(index + 1).type != TokenType::IDENTIFIER) {
        Logger::log("Error in function declaration: expected identifier but got: " +
                    Token::type_to_string(this->_tokens->at(index + 1).type));
        return std::make_tuple(nullptr, index);
    }

    // identifier is guaranteed to be an identifier. Lets assign it.

    functionDeclaration->identifier.type = TokenType::IDENTIFIER;
    functionDeclaration->identifier.name = this->_tokens->at(index + 1).value;

    // check for params

    if (this->_tokens->at(index + 2).type == TokenType::PUNCTUATOR && this->_tokens->at(index + 2).value == "(" &&
        this->_tokens->at(index + 3).type == TokenType::PUNCTUATOR && this->_tokens->at(index + 3).value == ")") {
        Logger::log("No params specified");
    } else {
        // TODO: Handle params of function declaration
    }

    // the body of a function is basically a block statement, so pass this on.

    auto blockStatementTuple = this->generateBlockStatement(index + 4, this->_tokens->at(index + 4));

    index = std::get<int>(blockStatementTuple);
    functionDeclaration->body = std::get<BlockStatement *>(blockStatementTuple);


    return std::make_tuple(functionDeclaration, index);
}

std::tuple<BlockStatement *, int> Parser::generateBlockStatement(int index, TokenHolder token) {
    bool startedAtIndexZero = index == 0;
    int initialIndex = index;

    auto *blockStatement = new BlockStatement;
    blockStatement->body = new std::vector<Statement *>;

    for (int it = index; it < this->_tokens->size(); it++) {
        TokenHolder token = this->_tokens->at(it);
        switch (token.type) {
            case TokenType::KEYWORD: {
                if (token.value == "function") {
                    auto tuple = this->generateFunctionDeclaration(it, token);
                    it = std::get<int>(tuple);
                    blockStatement->body->push_back(std::get<FunctionDeclaration *>(tuple));
                } else {
                    auto tuple = this->generateVariableDeclaration(it, token);
                    it = std::get<int>(tuple);
                    blockStatement->body->push_back(std::get<VariableDeclaration *>(tuple));
                }

                break;
            }
            case TokenType::PUNCTUATOR: {
                if (!startedAtIndexZero) {
                    if (token.value == "{" && initialIndex != it) {
                        auto tuple = this->generateBlockStatement(it, this->_tokens->at(it));
                        it = std::get<int>(tuple);
                        blockStatement->body->push_back(std::get<BlockStatement *>(tuple));
                    }
                    if (token.value == "}") {
                        return std::make_tuple(blockStatement, it);
                    }
                }
                break;
            }
            default:
                Logger::log("Token type: " + Token::type_to_string(token.type) + " with value: " + token.value +
                            " is not handled yet");
        }
    }

    return std::make_tuple(blockStatement, index);


}

