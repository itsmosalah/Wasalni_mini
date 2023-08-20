#include<iostream>
#include <windows.h>
#include "ConsoleOutput.h"

using namespace std;
static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void ConsoleOutput::print(const string s, int color) {
    SetConsoleTextAttribute(h, color);
    cout << s;
    SetConsoleTextAttribute(h, 7);
}

void ConsoleOutput::message(const std::string s) { print(s, WHITE); }
void ConsoleOutput::success(const std::string s) { print(s, DARK_GREEN); }
void ConsoleOutput::error(const std::string s) { print(s, RED); }
void ConsoleOutput::info(const std::string s) { print(s, TEAL); }
void ConsoleOutput::info_bright(const std::string s) { print(s, CYAN); }
void ConsoleOutput::warning(const std::string s) { print(s, YELLOW); }
