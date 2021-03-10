#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H


#include "Lexer.h"
#include "Parser.h"

class Calculator {
public:
    explicit Calculator(int base);

    std::string *run_expression(std::string *expression);

    std::string *convert_from_custom_base(std::string *number, int from_base);

    std::string *generate_random_number(std::string *min, std::string *max);

protected:
    int base;
    Lexer *lexer;
    Parser *parser;
private:
    [[nodiscard]] std::string *get_valid_number_characters() const;

    std::string *to_valid_base_string(int value);

    static void prepare_expression(std::string *expression);
};


#endif //CALCULATOR_CALCULATOR_H
