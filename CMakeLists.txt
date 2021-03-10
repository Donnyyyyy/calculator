
project(calculator)

set(CMAKE_CXX_STANDARD 20)

add_executable(calculator main.cpp Lexer.cpp Lexer.h Calculator.cpp Calculator.h Parser.cpp Parser.h operations.cpp operations.h Cli.cpp Cli.h)