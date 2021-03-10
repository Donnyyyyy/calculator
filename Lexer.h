#ifndef CALCULATOR_LEXER_H
#define CALCULATOR_LEXER_H


#include <string>

enum Lexeme {
    NUMBER, START_BRACKET, END_BRACKET,
    PLUS, MINUS, DIVIDE, MULTIPLY,
    SIN, COS, TAN,
    AND, OR, XOR, LEFT_SHIFT, RIGHT_SHIFT, NOT,
    POW, FACTORIAL,
};


class Keyword {
public:
    std::string term;
    Lexeme lexeme;

    Keyword(std::string term, Lexeme lexeme);
};


class Token {
public:
    Lexeme lexeme;
    std::string value;

    Token(Lexeme lexeme, std::string value);
};

class Lexer {
public:
    std::vector<Keyword *> *keywords;
    std::string *valid_number_characters;

    explicit Lexer(std::vector<Keyword *> *keywords, std::string *valid_number_characters);

    std::vector<Token> *tokenize(std::string *expression);

protected:
    Token *get_next_token(std::string *expression) const;
};


#endif //CALCULATOR_LEXER_H
