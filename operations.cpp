#include "operations.h"

int Sin::get_value() {
    int expression_value = this->expression->get_value();
    return sin(expression_value);
}

int Cos::get_value() {
    int expression_value = this->expression->get_value();
    return cos(expression_value);
}

int Tan::get_value() {
    int expression_value = this->expression->get_value();
    return tan(expression_value);
}

int Not::get_value() {
    int expression_value = this->expression->get_value();
    return ~expression_value;
}

int Factorial::get_value() {
    int expression_value = this->expression->get_value();
    return Factorial::factorial(expression_value);
}

int Factorial::factorial(int a) {
    if (a < 0) {
        throw std::runtime_error("Невозможно получить факториал отрицательного числа");
    }

    if (a == 0 or a == 1) {
        return 1;
    }

    return a * Factorial::factorial(a - 1);
}

int Plus::get_value() {
    int left_expression_value = this->left_expression->get_value();
    int right_expression_value = this->right_expression->get_value();
    return left_expression_value + right_expression_value;
}

int Minus::get_value() {
    int left_expression_value = this->left_expression->get_value();
    int right_expression_value = this->right_expression->get_value();
    return left_expression_value - right_expression_value;
}

int Divide::get_value() {
    int left_expression_value = this->left_expression->get_value();
    int right_expression_value = this->right_expression->get_value();

    if (right_expression_value == 0) {
        throw std::runtime_error("Попытка деления на ноль");
    }

    return left_expression_value / right_expression_value;
}

int Multiply::get_value() {
    int left_expression_value = this->left_expression->get_value();
    int right_expression_value = this->right_expression->get_value();
    return left_expression_value * right_expression_value;
}

int And::get_value() {
    int left_expression_value = this->left_expression->get_value();
    int right_expression_value = this->right_expression->get_value();
    return left_expression_value & right_expression_value;
}

int Or::get_value() {
    int left_expression_value = this->left_expression->get_value();
    int right_expression_value = this->right_expression->get_value();
    return left_expression_value | right_expression_value;
}

int Xor::get_value() {
    int left_expression_value = this->left_expression->get_value();
    int right_expression_value = this->right_expression->get_value();
    return left_expression_value ^ right_expression_value;
}

int LeftShift::get_value() {
    int left_expression_value = this->left_expression->get_value();
    int right_expression_value = this->right_expression->get_value();
    return left_expression_value << right_expression_value;
}

int RightShift::get_value() {
    int left_expression_value = this->left_expression->get_value();
    int right_expression_value = this->right_expression->get_value();
    return left_expression_value >> right_expression_value;
}

int Power::get_value() {
    int left_expression_value = this->left_expression->get_value();
    int right_expression_value = this->right_expression->get_value();
    return pow(left_expression_value, right_expression_value);
}
