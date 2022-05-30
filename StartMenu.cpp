#include "StartMenu.h"
#include "Colors.cpp"


void StartMenu::runWasalni()
{
    initializeQuery();
    

    string choice, graphName;

    //taking user input whether they choose to enter a new graph or load a saved one
    while (true)
    {
        cout << "Do you wish to enter new data or load previously saved data?\n"
            "Enter \'1\' for entering new data, \'2\' for loading previously saved data, or \'0\' to terminate the program.\n";

        cin >> choice;

        if (choice == "0")
        {
            exit(0);
        }
        else if (choice == "1" || choice == "2") break;

        Colors("Invalid input. Please try again.\n", 4);
            
    }

    if (choice == "1")
    {

        //taking a name for the graph and validating it is not a duplicate
        do {
            cout << "Enter graph name, or enter \"exit\" to return to start menu:\n";  cin >> graphName;

            if (graphName == "exit"){
                cout << endl;
                return;
            }
            //add if valid returns false when there is a duplicate
            if (addIfValid(graphName)) break;
            //cout << "Name \"" << graphName << "\" is already used. Try another!\n";

            Colors("Name \"" + graphName + "\" is already used. Try another!\n", 4);
        } while (true);

        //now it is validated and added to the vector of strings of graph names that we have in runtime.

        currentGraph.name = graphName;
        currentGraph.insertGraph();
        currentGraph.updateGraph();
    }

    else
    {

        //load existing graphs names
        cout << "Here are the names of the saved graphs:\n";

        //if the display function returned false, this means nothing was stored and displayed
        if (!displaySavedGraphs()){
            Colors(" -- No graphs stored -- \n\n", 4);
            return;
        }



        do {

            int index = 0, size = savedGraphs.size();
            string input;
            cout << "\nEnter the index of the graph you wish to load from the above list. Or enter \'0\' to return.\n";
            cin >> input;

            if (input == "0")
                return;

            for (char& c : input) {
                if (c < '0' || c >'9') goto InvalidInput;
                index = index * 10 + (c - '0');
            }
            if (index < 1 || index > size) {
                goto InvalidInput;
            }

            //in case input was valid
            graphName = savedGraphs[index - 1];
            break;

            InvalidInput:
                Colors("Invalid Input Please choose an index within the above list. From 1 to " + to_string(size) + "\n", 4);
        }
        while (true);

        //now we have an existing graph. all we need to do is load it into current graph
        
        currentGraph.name = graphName;
        FileHandling::loadData(currentGraph);

        //cout << "Data for \"" << graphName << "\" was loaded successfully!\n";
        
        Colors("Data for \"" + graphName + "\" have been loaded successfully!\n", 2);

        //then, user is navigated to graph options.
        currentGraph.updateGraph();
    }
    
    savePrompt();
}

//function to check whether user wishes to save or not
void StartMenu::savePrompt() {

    char choice;

    while (true) {
        cout << "Do you wish to save any change(s) made to \" " << currentGraph.name << " \" y/n\n";
        cin >> choice;
        if (choice == 'y') {

            FileHandling::writeAll(currentGraph);
            
            //cout << "for testing. right before saving to file: \n";
            //displaySavedGraphs();

            FileHandling::save_graphsname(savedGraphs);
            //cout << "Data of \"" << currentGraph.name << "\" have been saved successfully!\n\n";
            Colors("Data of \"" + currentGraph.name + "\" have been saved successfully!\n\n", 2);
        }
        if (choice == 'y' || choice == 'n')
            break;
        else {
            //cout << "Invalid input. Please try again...\n";
            Colors("Invalid input. Please try again...\n", 4);
        }
    }
    
}

bool StartMenu::addIfValid(string graphName)
{
    if (graphExists(graphName)) return false; //duplicate
    savedGraphs.push_back(graphName);
    return true;
}

bool StartMenu::graphExists(const string& graphName) {
    for (string& s : savedGraphs)
    {
        if (graphName == s) return true;
    }
    return false;
}

bool StartMenu::displaySavedGraphs() {
    bool output = false;
    int index = 1;
    for (string& s : savedGraphs)
    {
        output |= s.size() > 1;
        //cout << index++ << " - " << s << endl;
        Colors(to_string(index++) + " - " + s + "\n", 3);
    }
    return output;
}

void StartMenu::initializeQuery() {
    currentGraph = Graph();
    //loading the saved graphs to the vector of strings once
    if (!graphsNamesFileLoaded) {
        graphsNamesFileLoaded = true;
        FileHandling::load_graphsname(savedGraphs);
    }
}