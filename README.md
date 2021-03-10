# Калькулятор

- [Компиляция и запуск](#компиляция-и-запуск)
- [Примеры работы](#примеры-работы)
- [Схема работы](#схема-работы)

## Компиляция и запуск

Компиляция:

```shell
cmake .
cmake --build .
```

Запуск:

```shell
./calculator
```

## Примеры работы

Вычисление значения выражения:

![](./artifacts/run_expression_example.png)

Генерация псевдослучайного числа в заданном промежутке:

![](./artifacts/generate_number_example.png)

Конвертация из одной системы счисления в другую:

![](./artifacts/convert_number_example.png)

## Схема работы

![](artifacts/general_scheme.jpg)

## Caution

This project has 0% test coverage and intended for showcase only. It has memory leaks at least :D