//
// Created by Dominic Järmann on 18/10/2020.
//

#ifndef LIONV8_ABSTRACTSYNTAXTREE_H
#define LIONV8_ABSTRACTSYNTAXTREE_H

#include <string>
#include <vector>
#include "../tokenizer/token.h"


enum class DeclarationType {
    VariableDeclarator,
    FunctionDeclarator,
};

enum class VariableDeclarationKind {
    Let,
    Const,
    Var,
};


enum class ExpressionType {
    LiteralExpression,
    NumericExpression,
    ObjectExpression,
    CallExpression
};

struct Statement {

};

struct StatementIdentifier {
    TokenType Type;
    std::string Name;
};

struct Declaration : Statement {
    DeclarationType Type;
    StatementIdentifier identifier;
};


struct ExpressionStatement : Statement {
    ExpressionType Type;
    char *value;
};


struct VariableDeclaration : Declaration {
    DeclarationType Type = DeclarationType::VariableDeclarator;
    ExpressionStatement Statement;
    VariableDeclarationKind Kind;
};

struct FunctionDeclaration : Declaration {
    DeclarationType Type = DeclarationType::FunctionDeclarator;
    std::vector<StatementIdentifier> parameters;
    std::vector<Statement> *body;
};


struct BlockStatement : Statement {

};


struct AbstractSyntaxTree {
    std::string type;
    std::vector<Statement> *program;
};


#endif //LIONV8_ABSTRACTSYNTAXTREE_H
