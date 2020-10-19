//
// Created by Dominic Järmann on 18/10/2020.
//

#ifndef LIONV8_ABSTRACTSYNTAXTREE_H
#define LIONV8_ABSTRACTSYNTAXTREE_H

#include <string>
#include <vector>
#include "../tokenizer/token.h"
#include "../helpers/Logger.h"


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
    CallExpression,
    MemberExpression
};
enum class BinaryExpressionOperator {
    Addition,
    Subtraction,
    Multiplication,
    Division
};

struct Statement {
    static void execute() {
        Logger::log("Executing statement base");
    }
};

struct BlockStatement : Statement {
    std::vector<Statement *> *body;
};


struct StatementIdentifier {
    TokenType type;
    std::string name;
};

struct Declaration : Statement {
    DeclarationType Type;
    StatementIdentifier identifier;
};


struct ExpressionStatement : Statement {
    ExpressionType Type;
    void *value;
    Statement *expression;
};

struct BinaryExpression : Statement {
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
    DeclarationType type = DeclarationType::FunctionDeclarator;
    std::vector<StatementIdentifier> parameters;
    BlockStatement *body;
};


struct MemberExpression : ExpressionStatement {
    ExpressionType type = ExpressionType::MemberExpression;
    bool computed;
    StatementIdentifier *object;
    StatementIdentifier *property;
};

struct CallExpression : ExpressionStatement {
    ExpressionType type;
    MemberExpression callee;
    std::vector<ExpressionStatement> *arguments;


};


struct AbstractSyntaxTree {
    std::string type;
    BlockStatement *program;
};


#endif //LIONV8_ABSTRACTSYNTAXTREE_H
