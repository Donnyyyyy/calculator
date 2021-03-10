#include <iostream>
#include "Cli.h"
#include "Calculator.h"

void Cli::start() {
    Cli::about();
    std::cout << "Выберите один из режимов работы:" << std::endl
              << blue << "\t (1)" << normal << " вычислить значение выражения" << std::endl
              << magenta << "\t (2)" << normal << " сгенерировать случайное число" << std::endl
              << green << "\t (3)" << normal << " сконвертировать из одной системы счисления в другую" << std::endl;

    std::cout << yellow << "Введите номер режима работы: " << normal;
    std::string selected_mode;
    std::cin >> selected_mode;

    if (selected_mode == "1") {
        Cli::run_expression();
    } else if (selected_mode == "2") {
        Cli::generate_number();
    } else if (selected_mode == "3") {
        Cli::convert_number();
    } else {
        std::cout << "Введен неверный режим работы.";
        return;
    }
}

void Cli::about() {
    std::cout << "###################################################################" << std::endl
              << "#" << blue << " ЦЕЛОЧИСЛЕННЫЙ КАЛЬКУЛЯТОР С ПОДДЕРЖКОЙ МАТЕМАТИЧЕСКИХ ВЫРАЖЕНИЙ " << normal << "#"
              << std::endl
              << "###################################################################" << std::endl << std::endl;
}

void Cli::run_expression() {
    std::cout << std::endl << blue << "--- Вычисление значение целочисленного выражения с поддержкой скобок ---"
              << normal << std::endl
              << "Поддерживаемые операции:" << std::endl

              << "\tАрифметические: "
              << blue << "+" << normal << ", "
              << blue << "-" << normal << ", "
              << blue << "/" << normal << ", "
              << blue << "*" << normal << ";" << std::endl

              << "\tТригонометрические: "
              << blue << "sin" << normal << ", "
              << blue << "cos" << normal << ", "
              << blue << "tan" << normal << ";" << std::endl

              << "\tБинарные: "
              << blue << "&" << normal << ", "
              << blue << "|" << normal << ", "
              << blue << "^" << normal << ", "
              << blue << "<<" << normal << ", "
              << blue << ">>" << normal << ", "
              << blue << "~" << normal << ";" << std::endl

              << "\tПрочие: "
              << blue << "pow" << normal << ", "
              << blue << "!" << normal << "." << std::endl << std::endl;

    std::cout << yellow << "Введите основание системы счисления, в которой будет выражение (2-31): " << normal;
    int selected_base;
    std::cin >> selected_base;

    if (selected_base < 2 or selected_base > 31) {
        std::cout << "Введена неподдерживаемая система счисления.";
        return;
    }

    std::cout << yellow << "Введите выражение в системе счисления с основанием " << selected_base << ": " << normal;
    std::cin.ignore(1, '\n');
    auto *expression = new std::string;
    std::getline(std::cin, *expression);

    auto calculator = new Calculator(selected_base);
    std::string *result = calculator->run_expression(expression);

    std::cout << "Полученный результат: " << blue << *expression << " = " << *result << normal << std::endl;
}

void Cli::generate_number() {
    std::cout << magenta << "--- Генерация псевдослучайного целого числа в произвольной системе счисления ---" << normal
              << std::endl;

    std::cout << yellow << "Введите основание системы счисления, в которой будет сгенерировано число (2-31): "
              << normal;
    int target_base;
    std::cin >> target_base;

    if (target_base < 2 or target_base > 31) {
        std::cout << "Введена неподдерживаемая система счисления.";
        return;
    }

    std::cout << yellow << "Введите минимальное значение случайного числа (в выбранной системе счисления): "
              << normal;
    auto *min = new std::string;
    std::cin >> *min;

    std::cout << yellow << "Введите максимальное значение случайного числа (в выбранной системе счисления): "
              << normal;
    auto *max = new std::string;
    std::cin >> *max;

    auto calculator = new Calculator(target_base);
    std::string *result = calculator->generate_random_number(min, max);

    std::cout << "Полученный результат: " << magenta << *result << normal << std::endl;

}

void Cli::convert_number() {
    std::cout << green << "--- Конвертация произвольного числа из одной системы счисления в другую ---" << normal
              << std::endl;

    std::cout << yellow << "Введите основание системы счисления, из которой будет производиться конвертация (2-31): "
              << normal;
    int from_base;
    std::cin >> from_base;

    if (from_base < 2 or from_base > 31) {
        std::cout << "Введена неподдерживаемая система счисления.";
        return;
    }

    std::cout << yellow << "Число в выбранной системе счисления: " << normal;
    std::string number;
    std::cin >> number;

    std::cout << yellow << "Введите основание системы счисления, в которую будет сконвертированно число (2-31): "
              << normal;
    int to_base;
    std::cin >> to_base;

    if (to_base < 2 or to_base > 31) {
        std::cout << "Введена неподдерживаемая система счисления.";
        return;
    }

    auto calculator = new Calculator(to_base);
    std::string *result = calculator->convert_from_custom_base(&number, from_base);

    std::cout << "Полученный результат: " << green << *result << normal << std::endl;
}
