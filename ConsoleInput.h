#pragma once
#include <iostream>
#include "ConsoleOutput.h"
#include <string>
#include <vector>


class ConsoleInput {
	template<typename T>
	static void displayErrorMessage(const std::vector<T>& choices);
public:
	template<typename T>
	static T getUserInput(std::initializer_list<T> choices);
	template<typename T>
	static T getUserInput(std::vector<T> choices);
};

// Implementing templates

template <typename T>
void ConsoleInput::displayErrorMessage(const std::vector<T>& choices) {
	ConsoleOutput::error("Error: Invalid input.\n");
	ConsoleOutput::warning("Please enter one of the following choices:\n");

	for (auto choice : choices) {
		ConsoleOutput::info(choice);
		cout << " ";
	}
	ConsoleOutput::info("\n------------------\n> ");
}

template <typename T>
T ConsoleInput::getUserInput(std::vector<T> choices) {
	T input;

	bool valid = false;
	do {
		try {
			cin >> input;
			if (cin.fail()) {
				cin.clear(); cin.ignore();
				throw exception();
			}

			for (auto& choice : choices) {
				if (valid |= (input == choice))
					break;
			}
			if (!valid)
				throw exception();
		}
		catch (exception&) {
			displayErrorMessage(choices);
		}
	} while (!valid);

	return input;
}

template <typename T>
T ConsoleInput::getUserInput(std::initializer_list<T> choices) {
	return getUserInput(std::vector<T>(choices.begin(), choices.end()));
}