#ifndef CALCULATOR_CLI_H
#define CALCULATOR_CLI_H


class Cli {
public:
    static void start();

protected:
    static void about();

    static void run_expression();

    static void generate_number();

    static void convert_number();

private:
//    https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
    constexpr static const char blue[8] = {0x1b, '[', '1', ';', '3', '4', 'm', 0};
    constexpr static const char green[8] = {0x1b, '[', '1', ';', '3', '2', 'm', 0};
    constexpr static const char magenta[8] = {0x1b, '[', '1', ';', '3', '5', 'm', 0};
    constexpr static const char yellow[8] = {0x1b, '[', '1', ';', '3', '3', 'm', 0};
    constexpr static const char normal[8] = {0x1b, '[', '0', ';', '3', '9', 'm', 0};
};


#endif //CALCULATOR_CLI_H
