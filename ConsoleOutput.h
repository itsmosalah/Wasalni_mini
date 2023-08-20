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
    template <typename T>
    static void print(const T s, int color);
public:
    template <typename T>
    static void message(const T s);
    template <typename T>
    static void success(const T s);
    template <typename T>
    static void error(const T s);
    template <typename T>
    static void info(const T s);
    template <typename T>
    static void info_bright(const T s);
    template <typename T>
    static void warning(const T s);
};


#include<iostream>
#include <windows.h>
#include "ConsoleOutput.h"

using namespace std;
static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

template <typename T>
void ConsoleOutput::print(const T s, int color) {
    SetConsoleTextAttribute(h, color);
    cout << s;
    SetConsoleTextAttribute(h, 7);
}

template <typename T>
void ConsoleOutput::message(const T s) { print(s, WHITE); }
template <typename T>
void ConsoleOutput::success(const T s) { print(s, DARK_GREEN); }
template <typename T>
void ConsoleOutput::error(const T s) { print(s, RED); }
template <typename T>
void ConsoleOutput::info(const T s) { print(s, TEAL); }
template <typename T>
void ConsoleOutput::info_bright(const T s) { print(s, CYAN); }
template <typename T>
void ConsoleOutput::warning(const T s) { print(s, YELLOW); }
