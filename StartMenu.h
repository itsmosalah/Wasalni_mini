#pragma once
#include"Graph.h"
#include"FileHandling.h"

class StartMenu {
	
	bool graphsNamesFileLoaded = false;
	vector <string> savedGraphs;

	bool graphExists(const string& graphName);
	bool addIfValid(string graphName);
	void initializeQuery();

public: 
	Graph currentGraph;
	void runWasalni();
	bool displaySavedGraphs();
	void savePrompt();

};