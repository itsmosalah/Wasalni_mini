#include "Validation.h"
#include<iostream>
#include <map>
#include <vector>
#include <string>
#include"Colors.cpp"

using namespace std;

//Function that checks whether the entered value is 'exit' or 'back'.
//It takes one string as an argument, the user's input to check it.

bool Validation::CheckEB(string s) {
    if (s.size() == 4) {
        for (int i = 0; i < 4; i++) {
            s[i] = tolower(s[i]);
        }

        if (s == "exit" || s == "back") {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

/*
- Function that prompts the user to input a value and checks whether the entered
value is 'y' or 'n',in case of invalid input, it asks the user to re-enter the value.
- it takes one string as an argument, a reference to the choice variable in the graph file that will be filled and validated.
*/

void Validation::CheckYN(string &choice) {
    cin >> choice;
    while (choice.size() > 1 || tolower(choice[0]) != 'n' && tolower(choice[0]) != 'y') {
        Colors("Invalid Input, please enter 'y' or 'n':\n",4);
        cin >> choice;
    }
}

//Function that checks whether the entered value is a number and whether it applies to certain constraints or not (Certain inputs are required to be within a specific range of numbers).
//It takes two arguments, an integer that represents the current step, and a string representing a reference to the choice variable in the graph file that will be filled and validated.

void Validation::CheckNumbers(int i,string &choice) {
        cin >> choice;

        if (i == 1 && choice != "1" && choice != "2") {
            Colors("Invalid Input, please enter 1 for directed graph or 2 for undirected graph:\n",4);
            CheckNumbers(1,choice);
        }
        else {
            bool valid = true;
            for (int i = 0; i < choice.size(); i++) {
                if (isdigit(choice[i]) == 0) {
                    valid = false;
                    break;
                }
            }

            if (!valid) {
                switch (i)
                {
                case 2:
                    Colors( "Invalid input, please enter a number: (greater than or equal to zero).\n",4);
                    CheckNumbers(2,choice);
                    break;
                case 3:
                    Colors( "Invalid input, please enter a positive number: (Distance must have a positive value).\n",4);
                    CheckNumbers(3,choice);
                    break;
                case 4:
                    Colors("Invalid input.\n",4);
                    cout << "\nPlease enter:\n'1' to add a location\n'2' to delete a location\n'3' to add a road\n'4' to delete a road\n'5' to update a road\n'6' to find the shortest path between two locations\n'7' to run testing mode\n'8' to terminate the program.\n\n>> ";
                    CheckNumbers(4, choice);
                    break;
                }

            }
        }
    }

 /*
Function that displays messages to guide the user through the operation and allows them to confirm their choices or discard them.
It takes 5 arguments as follows:
- three strings, the first one isa reference to the choice variable in the graph file that will be filled and validated, the second one is the message to be displayed to the user depending on his input progress,
and the third one is a confirmation message that is dislayed after the user inputs a value, it asks the user if they want to proceed with their input or re-enter it.
- two integers, the first one 'i' is a number assigned for a specific code block to be excuted when it's called,
and the second one 'var' will hold the value of the user input after they confirm they wish to proceed with it.

*/

void Validation::userGuide(string& choice,string s, int i, int& var, string s2) {
    do {
        cout << s << endl;

        SetConsoleTextAttribute(h, 7);

        Validation::CheckNumbers(i,choice);

        var = stoi(choice);

        if (i == 3 && var == 0) {
            SetConsoleTextAttribute(h, 4);
            Validation::userGuide(choice,"Invalid input, please enter a positive number: (Distance must have a positive value).", 3, var, "Would you like to proceed with the length that you entered? y/n");
        }
        else {
            cout << s2 << endl;
            Validation::CheckYN(choice);
        }
    } while (tolower(choice[0] == 'n'));
}

//Function that sets a string to a certain format.
//e.g ( CaIrO --> Cairo )
//takes a single string as an argument, the string to be formatted.

string Validation::format(string s) {
    s[0] = toupper(s[0]);
    for (int i = 1; i < s.size(); i++) {
        if (s[i] == '-') {
            s[i + 1] = toupper(s[i + 1]);
            i++;
        }
        else {
            s[i] = tolower(s[i]);
        }
    }
    return s;
}