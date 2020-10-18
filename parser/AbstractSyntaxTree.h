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
enum class BinaryExpressionOperator {
    Addition,
    Subtraction,
    Multiplication,
    Division
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
    char *Value;
};

struct BinaryExpression : ExpressionStatement {
    ExpressionStatement *Left;
    ExpressionStatement *Right;
    BinaryExpressionOperator Operator;
};


struct VariableDeclaration : Declaration {
    DeclarationType Type = DeclarationType::VariableDeclarator;
    ExpressionStatement Statement;
    VariableDeclarationKind Kind;
};

struct FunctionDeclaration : Declaration {
    DeclarationType Type = DeclarationType::FunctionDeclarator;
    std::vector<StatementIdentifier> Parameters;
    std::vector<Statement> *Body;
};

struct CallExpression : ExpressionStatement {
    ExpressionType Type;
    struct Callee {
        bool Computed;
        StatementIdentifier *Object;
        StatementIdentifier *Property;
        std::vector<ExpressionStatement> *Arguments;
    };

};


struct BlockStatement : Statement {

};


struct AbstractSyntaxTree {
    std::string Type;
    std::vector<Statement> *Program;
};


#endif //LIONV8_ABSTRACTSYNTAXTREE_H
