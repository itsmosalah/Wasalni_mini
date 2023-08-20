#include "StartMenu.h"
#include "ConsoleOutput.h"


void Wasalni::runWasalni()
{
    initializeWasalni();
    

    string choice = getUserChoice();

    if (choice == CHOICE_ENTER_NEW_DATA)
    {
        handleEnteringNewData();
    }
    else if (choice == CHOICE_LOAD_SAVED_DATA)
    {
        handleLoadingSavedData();
    }
    
    showSavePrompt();
}

//function to check whether user wishes to save or not
void Wasalni::showSavePrompt() {

    if (currentGraph.name.empty())
        return;

    char choice;

    while (true) {
        cout << "Do you wish to save any change(s) made to \"" << currentGraph.name << "\" (y/n)\n";
        cin >> choice;
        if (choice == 'y') {

            FileHandling::writeAll(currentGraph);
            
            //cout << "for testing. right before saving to file: \n";
            //displaySavedGraphs();

            FileHandling::save_graphsname(savedGraphs);
            
            ConsoleOutput::success("Data of \"" + currentGraph.name + "\" have been saved successfully!\n\n");
        }
        if (choice == 'y' || choice == 'n')
            break;
        else {
            ConsoleOutput::error("Invalid input. Please try again...\n");
        }
    }
    
}

bool Wasalni::addIfValid(string graphName)
{
    if (graphExists(graphName)) return false; //duplicate
    savedGraphs.emplace(graphName);
    return true;
}

bool Wasalni::graphExists(const string& graphName) {
    for (auto& s : savedGraphs)
    {
        if (graphName == s) return true;
    }
    return false;
}

bool Wasalni::displaySavedGraphs() {
    bool output = false;
    int index = 1;
    for (auto& s : savedGraphs)
    {
        if (s.size() > 1)
            output = true;
        ConsoleOutput::info(to_string(index) + " - " + s + "\n");
        index++;
    }
    return output;
}

void Wasalni::initializeWasalni() {
    currentGraph = Graph();
    
    if (!graphsNamesFileLoaded) {
        FileHandling::load_graphsname(savedGraphs);
        graphsNamesFileLoaded = true;
    }
}

bool Wasalni::validChoice(string choice)
{
    return (choice == CHOICE_EXIT or
        choice == CHOICE_ENTER_NEW_DATA or
        choice == CHOICE_LOAD_SAVED_DATA);
}

void Wasalni::handleEnteringNewData()
{
    string input;
    //taking a name for the graph and validating it is not a duplicate
    do {
        cout << MESSAGE_ENTER_GRAPH_NAME;  cin >> input;

        if (input == "exit") {
            cout << endl;
            return;
        }

        if (addIfValid(input)) break;

        ConsoleOutput::error("Name \"" + input + "\" is already used. Try another!\n");
    } while (true);

    //now it is validated and added to the vector of strings of graph names that we have in runtime.

    currentGraph.name = input;
    currentGraph.insertGraph();
    currentGraph.updateGraph();
}

void Wasalni::handleLoadingSavedData()
{
    //load existing graphs names
    cout << "Here are the names of the saved graphs:\n";
    //if the display function returned false, this means nothing was stored and displayed
    if (!displaySavedGraphs()) {
        ConsoleOutput::error(" -- No graphs stored -- \n\n");
        return;
    }

    string graphName = getSavedGraphName();
    if (graphName == "0")
        return;

    //now we have an existing graph. all we need to do is load it into current graph

    currentGraph.name = graphName;
    FileHandling::loadData(currentGraph);

    ConsoleOutput::success("Data for \"" + graphName + "\" have been loaded successfully!\n");

    currentGraph.updateGraph();
}

string Wasalni::getUserChoice()
{
    string choice;
    do
    {
        cout << MESSAGE_ENTER_OR_LOAD_NEW_DATA; cin >> choice;

        if (validChoice(choice))
        {
            if (choice == CHOICE_EXIT)
                exit(0);
            
            break;
        }
        ConsoleOutput::error("Invalid input. Please try again.\n");

    } while (true);
    return choice;
}

string Wasalni::getSavedGraphName() {
    string input, graphName;
    int size = savedGraphs.size();
    do {
        ConsoleOutput::message("\nEnter the index of the graph you wish to load from the above list. Or enter \'0\' to return.\n");
        cin >> input;

        if (input == "0")
            break;

        try {
            int input_num = stoi(input) - 1, index = 0;
            for (auto it = savedGraphs.begin(); it != savedGraphs.end(); it++, index++) {
                if (index == input_num)
                {
                    graphName = *it;
                    break;
                }
            }
            if (graphName.empty())
                throw exception("Index out of bounds.");
        }
        catch (exception&) {
            ConsoleOutput::error("Invalid Input Please choose an index within the above list. From 1 to " + to_string(size) + "\n");
            continue;
        }
    } while (true);
    return graphName;
}