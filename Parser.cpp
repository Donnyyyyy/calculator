#include "Parser.h"
#include "operations.h"


Parser::Parser(
        int base, std::unordered_map<Lexeme, int> *operation_priority,
        std::set<Lexeme> *prefix_unary_operations,
        std::set<Lexeme> *postfix_unary_operations,
        std::set<Lexeme> *binary_operations
) {
    this->base = base;
    this->operation_priority = operation_priority;
    this->prefix_unary_operations = prefix_unary_operations;
    this->postfix_unary_operations = postfix_unary_operations;
    this->binary_operations = binary_operations;
}

Node *Parser::parse(std::vector<Token> *tokens) {
    if (tokens->empty()) {
//        Пустое выражение
        throw std::runtime_error("Ошибка выражения: введено пустое выражение или пустые скобки");
    }

    if (Parser::is_surrounded_in_brackets(tokens)) {
//        Раскрываем скобки
        auto expression_without_brackets = new std::vector<Token>(tokens->begin() + 1, tokens->end() - 1);
        return this->parse(expression_without_brackets);
    }

    int last_operation_position = this->get_last_operation_position(tokens);

    if (last_operation_position == -1) {
//        Операторов нет, значит выражение содержит только число или является некорректным
        if (tokens->size() != 1 or tokens->at(0).lexeme != Lexeme::NUMBER) {
            throw std::runtime_error("Ошибка выражения: неверное расположение операторов");
        }
        return new Number(std::stoi(tokens->at(0).value, nullptr, this->base));
    }

    if (this->prefix_unary_operations->find(tokens->at(last_operation_position).lexeme) !=
        this->prefix_unary_operations->end()) {
//        Найденная операция - унарная и выражение идет после нее
        if (last_operation_position != 0) {
//            До найденного унарного оператора есть еще токены - ошибка
            throw std::runtime_error(
                    "Ошибка выражения: пропущен оператор перед \"" + tokens->at(last_operation_position).value + "\"");
        }

        auto expression_vector = new std::vector<Token>(tokens->begin() + 1, tokens->end());
        return this->build_unary_operation(&tokens->at(last_operation_position), expression_vector);
    }

    if (this->postfix_unary_operations->find(tokens->at(last_operation_position).lexeme) !=
        this->postfix_unary_operations->end()) {
//        Найденная операция - унарная и выражение идет до нее
        if (last_operation_position != tokens->size() - 1) {
//            После найденного унарного оператора есть еще токены - ошибка
            throw std::runtime_error(
                    "Ошибка выражения: пропущен оператор после \"" + tokens->at(last_operation_position).value + "\"");
        }

        auto expression_vector = new std::vector<Token>(tokens->begin(), tokens->end() - 1);
        return this->build_unary_operation(&tokens->at(last_operation_position), expression_vector);
    }

    if (this->binary_operations->find(tokens->at(last_operation_position).lexeme) !=
        this->binary_operations->end()) {
//        Найденная операция - бинарная
        if (last_operation_position == 0 or last_operation_position == tokens->size() - 1) {
//            Бинарная операция не может стоять в начале или в конце
            throw std::runtime_error(
                    "Ошибка выражения: бинарный оператор \"" + tokens->at(last_operation_position).value +
                    "\" требует два операнда");
        }

        auto left_expression_vector = new std::vector<Token>(tokens->begin(),
                                                             tokens->begin() + last_operation_position);

        auto right_expression_vector = new std::vector<Token>(tokens->begin() + last_operation_position + 1,
                                                              tokens->end());

        return this->build_binary_operation(&tokens->at(last_operation_position), left_expression_vector,
                                            right_expression_vector);
    }


    throw std::runtime_error("Невозможно распознать оператор \"" + tokens->at(last_operation_position).value + "\"");
}

int Parser::get_last_operation_position(std::vector<Token> *tokens) {
    int less_priority_operation_index = -1;
    int less_priority_operation_value;

    int bracket_level = 0;

    int current_token_index = 0;
    for (const auto &token : *tokens) {
//        Пропускаем выражениея в скобках, если скобки не находятся по краям
        if (token.lexeme == START_BRACKET) {
            bracket_level++;
        } else if (token.lexeme == END_BRACKET) {
            bracket_level--;
        }

        if (bracket_level > 0) {
            current_token_index++;
            continue;
        }

        int current_operation_priority = (*this->operation_priority)[token.lexeme];
        if (current_operation_priority != 0) {
            if (less_priority_operation_index == -1 or current_operation_priority >= less_priority_operation_value) {
                less_priority_operation_index = current_token_index;
                less_priority_operation_value = current_operation_priority;
            }
        }
        current_token_index++;
    }

    return less_priority_operation_index;
}

Node *Parser::build_unary_operation(Token *operation, std::vector<Token> *expression_tokens) {
    switch (operation->lexeme) {
        case SIN:
            return new Sin(this->parse(expression_tokens));
        case COS:
            return new Cos(this->parse(expression_tokens));
        case TAN:
            return new Tan(this->parse(expression_tokens));
        case NOT:
            return new Not(this->parse(expression_tokens));
        case FACTORIAL:
            return new Factorial(this->parse(expression_tokens));
        default:
            throw std::runtime_error("\"" + operation->value + "\" не является унарным оператором");
    }
}

Node *Parser::build_binary_operation(Token *operation, std::vector<Token> *left_expression_tokens,
                                     std::vector<Token> *right_expression_tokens) {
    auto left_expression_node = this->parse(left_expression_tokens);
    auto right_expression_node = this->parse(right_expression_tokens);

    switch (operation->lexeme) {
        case PLUS:
            return new Plus(left_expression_node, right_expression_node);
        case MINUS:
            return new Minus(left_expression_node, right_expression_node);
        case DIVIDE:
            return new Divide(left_expression_node, right_expression_node);
        case MULTIPLY:
            return new Multiply(left_expression_node, right_expression_node);
        case AND:
            return new And(left_expression_node, right_expression_node);
        case OR:
            return new Or(left_expression_node, right_expression_node);
        case XOR:
            return new Xor(left_expression_node, right_expression_node);
        case LEFT_SHIFT:
            return new LeftShift(left_expression_node, right_expression_node);
        case RIGHT_SHIFT:
            return new RightShift(left_expression_node, right_expression_node);
        case POW:
            return new Power(left_expression_node, right_expression_node);
        default:
            throw std::runtime_error("\"" + operation->value + "\" не является бинарным оператором");
    }
}

bool Parser::is_surrounded_in_brackets(std::vector<Token> *expression) {
    int bracket_level = 0;
    bool inside_start_bracket = false;

    int current_token_index = 0;
    for (const auto &token : *expression) {
        if (token.lexeme == START_BRACKET) {
            bracket_level++;
        } else if (token.lexeme == END_BRACKET) {
            bracket_level--;
        }
        if (bracket_level > 0 and current_token_index == 0) {
            inside_start_bracket = true;
        }
        if (bracket_level == 0 and current_token_index != expression->size() - 1) {
            inside_start_bracket = false;
        }
        current_token_index++;
    }
    return inside_start_bracket;
}

Number::Number(int value) {
    this->value = value;
}

int Number::get_value() {
    return this->value;
}

UnaryOperation::UnaryOperation(Node *expression) {
    this->expression = expression;
}

BinaryOperation::BinaryOperation(Node *left_expression, Node *right_expression) {
    this->left_expression = left_expression;
    this->right_expression = right_expression;
}
