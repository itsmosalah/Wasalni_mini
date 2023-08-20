#include "StartMenu.h"
#include "ConsoleOutput.h"
#include "ConsoleInput.h"

void Wasalni::runWasalni()
{
    initializeWasalni();
    

    ConsoleOutput::message(MESSAGE_ENTER_OR_LOAD_NEW_DATA);
    int choice = ConsoleInput::getUserInput<int>({0, 1, 2});
    
    if (choice == CHOICE_ENTER_NEW_DATA)
    {
        handleEnteringNewData();
    }
    else if (choice == CHOICE_LOAD_SAVED_DATA)
    {
        handleLoadingSavedData();
    }
    else if (choice == 0) {
        exit(0);
    }
    
    showSavePrompt();
}

//function to check whether user wishes to save or not
void Wasalni::showSavePrompt() {
    if (currentGraph.name.empty())
        return;

    ConsoleOutput::message("Do you wish to save any change(s) made to \"" + currentGraph.name + "\" (y/n)\n");
    char choice = ConsoleInput::getUserInput<char>({'y', 'n', 'Y', 'N'});
    choice = tolower(choice);

    if (choice == 'y') {
        FileHandling::writeAll(currentGraph);
        FileHandling::save_graphsname(savedGraphs);
        ConsoleOutput::success("Data of \"" + currentGraph.name + "\" have been saved successfully!\n\n");
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

void Wasalni::handleEnteringNewData()
{
    string input;
    //taking a name for the graph and validating it is not a duplicate
    do {
        ConsoleOutput::message(MESSAGE_ENTER_GRAPH_NAME);
        input = ConsoleInput::getUserInput<string>({ "exit", "**Graph Name**" });
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
    if (graphName == EXIT)
        return;

    //now we have an existing graph. all we need to do is load it into current graph

    currentGraph.name = graphName;
    FileHandling::loadData(currentGraph);

    ConsoleOutput::success("Data for \"" + graphName + "\" have been loaded successfully!\n");

    currentGraph.updateGraph();
}


string Wasalni::getSavedGraphName() {
    int input, size = savedGraphs.size();
    vector<int> inputs(size + 1); for (int i = 0; i <= size; i++) inputs[i] = i;
    
    ConsoleOutput::message("\nEnter the index of the graph you wish to load from the above list. Or enter \'0\' to return.\n");

    input = ConsoleInput::getUserInput(inputs);

    if (input == 0) return EXIT;

    auto it = savedGraphs.begin();
    for (int index = 0; index < input - 1; it++, index++);

    return *it;
}