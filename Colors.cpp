#include<iostream>
#include <windows.h>

using namespace std;
static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

//Funtion that changes the color of the console output.
//Used to highlight warnings, notes, and confirmations.

static void Colors(string s, int degree) {
    SetConsoleTextAttribute(h, degree);
    cout << s;
    SetConsoleTextAttribute(h, 7);
}