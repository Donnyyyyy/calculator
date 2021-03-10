#ifndef CALCULATOR_OPERATIONS_H
#define CALCULATOR_OPERATIONS_H


#include "Parser.h"

class Sin : public UnaryOperation {
public:
    using UnaryOperation::UnaryOperation;

    int get_value() override;
};

class Cos : public UnaryOperation {
public:
    using UnaryOperation::UnaryOperation;

    int get_value() override;
};

class Tan : public UnaryOperation {
public:
    using UnaryOperation::UnaryOperation;

    int get_value() override;
};

class Not : public UnaryOperation {
public:
    using UnaryOperation::UnaryOperation;

    int get_value() override;
};

class Factorial : public UnaryOperation {
public:
    using UnaryOperation::UnaryOperation;

    int get_value() override;

private:
    static int factorial(int a);
};

class Plus : public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    int get_value() override;
};

class Minus : public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    int get_value() override;
};

class Divide : public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    int get_value() override;
};

class Multiply : public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    int get_value() override;
};

class And : public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    int get_value() override;
};

class Or : public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    int get_value() override;
};

class Xor : public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    int get_value() override;
};

class LeftShift : public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    int get_value() override;
};

class RightShift : public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    int get_value() override;
};

class Power : public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    int get_value() override;
};


#endif //CALCULATOR_OPERATIONS_H
