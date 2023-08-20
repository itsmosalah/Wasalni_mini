#include "StartMenu.h"
#include "Colors.cpp"


void StartMenu::runWasalni()
{
    initializeQuery();
    

    string choice = getUserChoice();

    if (choice == CHOICE_ENTER_NEW_DATA)
    {
        handleEnteringNewData();
    }
    else if (choice == CHOICE_LOAD_SAVED_DATA)
    {
        handleLoadingSavedData();
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
        if (s.size() > 1)
            output = true;
        Colors(to_string(index) + " - " + s + "\n", 3);
        index++;
    }
    return output;
}

void StartMenu::initializeQuery() {
    currentGraph = Graph();
    
    if (!graphsNamesFileLoaded) {
        FileHandling::load_graphsname(savedGraphs);
        graphsNamesFileLoaded = true;
    }
}

bool StartMenu::invalidChoice(string choice)
{
    return (choice == CHOICE_EXIT or
        choice == CHOICE_ENTER_NEW_DATA or
        choice == CHOICE_LOAD_SAVED_DATA);
}

void StartMenu::handleEnteringNewData()
{
    string graphName;
    //taking a name for the graph and validating it is not a duplicate
    do {
        cout << MESSAGE_ENTER_GRAPH_NAME;  cin >> graphName;

        if (graphName == "exit") {
            cout << endl;
            return;
        }

        if (addIfValid(graphName)) break;

        Colors("Name \"" + graphName + "\" is already used. Try another!\n", 4);
    } while (true);

    //now it is validated and added to the vector of strings of graph names that we have in runtime.

    currentGraph.name = graphName;
    currentGraph.insertGraph();
    currentGraph.updateGraph();
}

void StartMenu::handleLoadingSavedData()
{
    //load existing graphs names
    cout << "Here are the names of the saved graphs:\n";

    //if the display function returned false, this means nothing was stored and displayed
    if (!displaySavedGraphs()) {
        Colors(" -- No graphs stored -- \n\n", 4);
        return;
    }


    string input, graphName;
    do {

        int index = 0, size = savedGraphs.size();

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
    } while (true);

    //now we have an existing graph. all we need to do is load it into current graph

    currentGraph.name = graphName;
    FileHandling::loadData(currentGraph);

    //cout << "Data for \"" << graphName << "\" was loaded successfully!\n";

    Colors("Data for \"" + graphName + "\" have been loaded successfully!\n", 2);

    //then, user is navigated to graph options.
    currentGraph.updateGraph();
}

string StartMenu::getUserChoice()
{
    string choice;
    do
    {
        cout << MESSAGE_ENTER_OR_LOAD_NEW_DATA; cin >> choice;

        if (invalidChoice(choice))
            Colors("Invalid input. Please try again.\n", 4);

        if (choice == CHOICE_EXIT)
            exit(0);

    } while (invalidChoice(choice));
    return choice;
}
