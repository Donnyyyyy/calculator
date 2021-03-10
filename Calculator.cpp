#include <vector>
#include <set>
#include <unordered_map>
#include <random>
#include "Calculator.h"

Calculator::Calculator(int base) {
    this->base = base;

//    Описание лексемм, которые являются ключевыми словами/символами
    auto keywords = new std::vector<Keyword *>();
    keywords->push_back(new Keyword(std::string("("), Lexeme::START_BRACKET));
    keywords->push_back(new Keyword(std::string(")"), Lexeme::END_BRACKET));

    keywords->push_back(new Keyword(std::string("+"), Lexeme::PLUS));
    keywords->push_back(new Keyword(std::string("-"), Lexeme::MINUS));
    keywords->push_back(new Keyword(std::string("/"), Lexeme::DIVIDE));
    keywords->push_back(new Keyword(std::string("*"), Lexeme::MULTIPLY));

    keywords->push_back(new Keyword(std::string("sin"), Lexeme::SIN));
    keywords->push_back(new Keyword(std::string("cos"), Lexeme::COS));
    keywords->push_back(new Keyword(std::string("tan"), Lexeme::TAN));

    keywords->push_back(new Keyword(std::string("&"), Lexeme::AND));
    keywords->push_back(new Keyword(std::string("|"), Lexeme::OR));
    keywords->push_back(new Keyword(std::string("^"), Lexeme::XOR));
    keywords->push_back(new Keyword(std::string("<<"), Lexeme::LEFT_SHIFT));
    keywords->push_back(new Keyword(std::string(">>"), Lexeme::RIGHT_SHIFT));
    keywords->push_back(new Keyword(std::string("~"), Lexeme::NOT));

    keywords->push_back(new Keyword(std::string("pow"), Lexeme::POW));
    keywords->push_back(new Keyword(std::string("!"), Lexeme::FACTORIAL));

//    Описание приоритета операций
    auto operation_priority = new std::unordered_map<Lexeme, int>{
//        Унарные операторы
            {Lexeme::SIN,         1},
            {Lexeme::COS,         1},
            {Lexeme::TAN,         1},
            {Lexeme::NOT,         1},
            {Lexeme::FACTORIAL,   1},
//        Бинарные операторы
            {Lexeme::PLUS,        3},
            {Lexeme::MINUS,       3},
            {Lexeme::DIVIDE,      2},
            {Lexeme::MULTIPLY,    2},
            {Lexeme::AND,         2},
            {Lexeme::OR,          3},
            {Lexeme::XOR,         3},
            {Lexeme::LEFT_SHIFT,  2},
            {Lexeme::RIGHT_SHIFT, 2},
            {Lexeme::POW,         2},
    };

//    Описание унарных операций, которые пишутся перед выражением
    auto prefix_unary_operations = new std::set<Lexeme>();
    prefix_unary_operations->insert(Lexeme::SIN);
    prefix_unary_operations->insert(Lexeme::COS);
    prefix_unary_operations->insert(Lexeme::TAN);
    prefix_unary_operations->insert(Lexeme::NOT);

//    Описание унарных операций, которые пишутся после выражения
    auto postfix_unary_operations = new std::set<Lexeme>();
    postfix_unary_operations->insert(Lexeme::FACTORIAL);


//    Описание бинарных операций
    auto binary_operations = new std::set<Lexeme>();
    binary_operations->insert(Lexeme::PLUS);
    binary_operations->insert(Lexeme::MINUS);
    binary_operations->insert(Lexeme::DIVIDE);
    binary_operations->insert(Lexeme::MULTIPLY);
    binary_operations->insert(Lexeme::AND);
    binary_operations->insert(Lexeme::OR);
    binary_operations->insert(Lexeme::XOR);
    binary_operations->insert(Lexeme::LEFT_SHIFT);
    binary_operations->insert(Lexeme::RIGHT_SHIFT);
    binary_operations->insert(Lexeme::POW);

    this->lexer = new Lexer(keywords, this->get_valid_number_characters());
    this->parser = new Parser(this->base, operation_priority, prefix_unary_operations, postfix_unary_operations,
                              binary_operations);
}

std::string *Calculator::get_valid_number_characters() const {
    auto *number_alphabet = new std::string();

    int characters_left = this->base;

    while (characters_left > 0) {
        char next_char;
        if (number_alphabet->length() < 10) {
//        Если еще остались цифры
            next_char = (char) ('0' + number_alphabet->length());
        } else {
//            Когда цифры кончились, используем буквы
            next_char = (char) ('a' + number_alphabet->length() - 10);
        }
        number_alphabet->push_back(next_char);
        characters_left--;
    }

    return number_alphabet;
}

std::string *Calculator::run_expression(std::string *expression) {
    auto expression_copy = new std::string(*expression);
    Calculator::prepare_expression(expression_copy);
    std::vector<Token> *tokens = this->lexer->tokenize(expression_copy);
    Node *root_node = this->parser->parse(tokens);

    int value = root_node->get_value();
    return this->to_valid_base_string(value);
}

std::string *Calculator::to_valid_base_string(int value) {
    if (value == 0) {
        return new std::string("0");
    }

    auto converted = new std::string();
    auto alphabet = this->get_valid_number_characters();
    bool is_negative = value < 0;

    if (is_negative) {
        value *= -1;
    }

    while (value != 0) {
        char next_digit = alphabet->at(value % this->base);
        converted->insert(0, &next_digit, 1);
        value /= this->base;
    }

    if (is_negative) {
        converted->insert(0, 1, '-');
    }

    return converted;
}

void Calculator::prepare_expression(std::string *expression) {
//    Удаляем все пробельные символы
    expression->erase(remove_if(expression->begin(), expression->end(), isspace), expression->end());
//    Приводим строку к нижнему регистру
    std::transform(expression->begin(), expression->end(), expression->begin(),
                   [](unsigned char c) { return std::tolower(c); });
}

std::string *Calculator::convert_from_custom_base(std::string *number, int from_base) {
    Calculator::prepare_expression(number);
    int value = std::stoi(*number, nullptr, from_base);
    return this->to_valid_base_string(value);
}

std::string *Calculator::generate_random_number(std::string *min_number, std::string *max_number) {
    int min = std::stoi(*min_number, nullptr, this->base);
    int max = std::stoi(*max_number, nullptr, this->base);

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<int> distribution(min, max);

    int value = distribution(generator);
    return this->to_valid_base_string(value);
}
