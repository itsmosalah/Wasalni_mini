#pragma once
#include <iostream>
class ConsoleOutput {
    const static int 
        DARK_GREEN = 2,
        TEAL = 3,
        RED = 4,
        YELLOW = 6,
        WHITE = 7,
        CYAN = 11;
    static void print(const std::string s, int color);
public:

    static void message(const std::string s);
    static void success(const std::string s);
    static void error(const std::string s);
    static void info(const std::string s);
    static void info_bright(const std::string s);
    static void warning(const std::string s);
};