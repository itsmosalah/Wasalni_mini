#pragma once
#include"Graph.h"
#include"FileHandling.h"

class StartMenu {
	
	// constants
	const string MESSAGE_ENTER_OR_LOAD_NEW_DATA = "Do you wish to enter new data or load previously saved data?\n"
		"Enter \'1\' for entering new data, \'2\' for loading previously saved data, or \'0\' to terminate the program.\n";
	const string MESSAGE_ENTER_GRAPH_NAME
		= "Enter graph name, or enter \"exit\" to return to start menu:\n";

	const string CHOICE_EXIT = "0",
		CHOICE_ENTER_NEW_DATA = "1",
		CHOICE_LOAD_SAVED_DATA = "2";


	// instance fields

	bool graphsNamesFileLoaded = false;
	vector <string> savedGraphs;

	// functions

	bool graphExists(const string& graphName);
	bool addIfValid(string graphName);
	void initializeQuery();
	bool invalidChoice(string choice);
	void handleEnteringNewData();
	void handleLoadingSavedData();
	string getUserChoice();

public: 
	Graph currentGraph;
	void runWasalni();
	bool displaySavedGraphs();
	void savePrompt();

};
