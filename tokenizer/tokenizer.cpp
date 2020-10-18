//
// Created by Dominic Järmann on 16/10/2020.
//

#include <iostream>
#include <vector>
#include "tokenizer.h"
#include "../helpers/Logger.h"

#define DBG false

Tokenizer::Tokenizer(std::string tokens) {
    this->tokenizeStr = tokens;
}


std::vector<TokenHolder> *Tokenizer::Tokenitze() {

    auto *tokenHolders = new std::vector<TokenHolder>();

    while (!this->isEOF()) {
        auto next = this->next();
        if (next.value == "") {
            continue;
        }
        tokenHolders->push_back(next);
    }

#if dbg
    for (auto const &value: *tokenHolders) {
        switch (value.type) {
            case TokenType::STRING:
                Logger::log("STRING");
                Logger::log(value.value);

                break;
            case TokenType::PUNCTUATOR:
                Logger::log("PUNCTUATOR");
                Logger::log(value.value);

                break;
            case TokenType::KEYWORD:
                Logger::log("KEYWORD");
                Logger::log(value.value);

                break;
            case TokenType::IDENTIFIER:
                Logger::log("IDENTIFIER");
                Logger::log(value.value);

                break;
            case TokenType::NUMERIC:
                Logger::log("IDENTIFIER");
                Logger::log(value.value);

                break;
        }
    }
#endif
    return tokenHolders;
}

TokenHolder Tokenizer::next() {
    TokenHolder tokenHolder;

    auto block = this->readUntilDelimiter();
    Token token(block);
    if (token.is_digit()) {
        tokenHolder.type = TokenType::NUMERIC;
        tokenHolder.value = block;
        return tokenHolder;
    }

    if (token.is_keyword()) {
        tokenHolder.type = TokenType::KEYWORD;
        tokenHolder.value = block;
        return tokenHolder;
    }

    if (token.is_identifier()) {
        tokenHolder.type = TokenType::IDENTIFIER;
        tokenHolder.value = block;
        return tokenHolder;
    }

    if (token.is_punctuator()) {
        tokenHolder.type = TokenType::PUNCTUATOR;
        tokenHolder.value = block;
        return tokenHolder;
    }


    if (token.is_string()) {
        tokenHolder.type = TokenType::STRING;
        tokenHolder.value = block;
        return tokenHolder;
    }

    tokenHolder.position.position = position;
    tokenHolder.position.line = line;

    Logger::log("Couldn't read block: " + block);
    Logger::log("Len(block): " + std::to_string(block.length()));

}


bool Tokenizer::isEOF() {
    return this->readChars == this->tokenizeStr.length() - 1;
}

std::string Tokenizer::readUntilDelimiter() {
    std::string content;

    int tmpRead = this->readChars;
    for (int it = this->readChars; it < this->tokenizeStr.length(); it++) {

        // Update position

        if (tokenizeStr[it] == '\n') {
            this->line++;
            this->position = 0;
        } else {
            this->position++;
        }


        if (tokenizeStr[it] == ';' || tokenizeStr[it] == ' ' || tokenizeStr[it] == '\n' ||
            tokenizeStr[it] == '.' || tokenizeStr[it] == '(' || tokenizeStr[it] == ')' || tokenizeStr[it] == '{' ||
            tokenizeStr[it] == '}' ||
            tokenizeStr[it] == ',') {
            if (tokenizeStr[it] != ' ' && tokenizeStr[it] != '\n' && content.length() == 0) {
                content += tokenizeStr[it];
                tmpRead = it + 1;
                break;
            }
            if (tokenizeStr[it] == ' ') {
                tmpRead = it + 1;
                break;
            }
            if (tokenizeStr[it] == '\n' && content.length() == 0) {
                continue;
            }

            if (tokenizeStr[it] == '\n' && content.length() > 0) {
                tmpRead = it + 1;
                break;
            }

            tmpRead = it;
            break;

        } else {
            content += tokenizeStr[it];
            tmpRead = it + 1;
        }


    }

    this->readChars = tmpRead;


    return content;
}
