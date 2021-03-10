#ifndef CALCULATOR_PARSER_H
#define CALCULATOR_PARSER_H


#include <vector>
#include <set>
#include <unordered_map>
#include "Lexer.h"


class Node {
public:
    virtual int get_value() = 0;
};

class Number : public Node {
public:
    int value;

    explicit Number(int value);

    int get_value() override;
};


class UnaryOperation : public Node {
public:
    explicit UnaryOperation(Node *expression);

protected:
    Node *expression;
};


class BinaryOperation : public Node {
public:
    Node *left_expression;
    Node *right_expression;

    BinaryOperation(Node *left_expression, Node *right_expression);
};


class Parser {
public:
    Parser(
            int base, std::unordered_map<Lexeme, int> *operation_priority,
            std::set<Lexeme> *prefix_unary_operations,
            std::set<Lexeme> *postfix_unary_operations,
            std::set<Lexeme> *binary_operations
    );

    Node *parse(std::vector<Token> *tokens);

protected:
    int base;
    std::unordered_map<Lexeme, int> *operation_priority;
    std::set<Lexeme> *prefix_unary_operations;
    std::set<Lexeme> *postfix_unary_operations;
    std::set<Lexeme> *binary_operations;

    static bool is_surrounded_in_brackets(std::vector<Token> *expression);

    int get_last_operation_position(std::vector<Token> *tokens);

    Node *build_unary_operation(Token *operation, std::vector<Token> *expression_tokens);

    Node *build_binary_operation(Token *operation, std::vector<Token> *left_expression_tokens,
                                 std::vector<Token> *right_expression_tokens);
};


#endif //CALCULATOR_PARSER_H
