#include "Graph.h"
#include<iostream>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "Colors.cpp"

using namespace std;

string Location;
string Location1, Location2;
string choice;


void Graph::algoOutputTest(int start, int dest, vector<pair<int, int>>(*algorithm)(int, int, int, int&, vector<edge>&)) {

    int dis = -1; vector<pair<int, int>>path;
    path = algorithm(start, dest, nodes, dis, edges);

    if (dis == -1)
        cout << "There is no path\n";
    else {
        for (int i = 0; i < path.size(); i++) {
            cout << toString[path[i].first];

            if (i < path.size() - 1) {
                cout << " --> ";
            }
        }
        
        Colors("\nWith total distance: " + to_string(dis) + "\n", 11);
    }
}

/*Function that inserts a graph as follows :
- It prompts the user to input the type of the graph(directed / undirected).
- It prompts the user to add the desired number of locations(none if desired).
- It prompts the user to add the desired number of roads, as long as the number of locations in the graph allows the addition of such roads(none if desired).
- The user is allowed to change and modify his input through a chain of confirmations.
- The questions that change the course of the program are case-insensitive, giving more freedom to the user.
- Many input validation functions have been made to assure that the user can only enter valid input.
*/

void Graph::insertGraph() {

    int roads, dist, numOfLocations;
    edge e;

    Validation::userGuide(choice,"Enter '1' for directed graph or '2' for undirected graph:", 1, type);
    Validation::userGuide(choice,"How many locations would you like to add? (Or enter '0' to skip).", 2, numOfLocations);

    if (numOfLocations > 0) {
        Colors("\nNOTE: while entering the name of locations that consist of more than one word, please insert a '-' between them (e.g Ain-Elsokhna).\n\n",3);
    }

    for (int i = 1; i <= numOfLocations; i++) {
        if (i > 1) {
            cout << "Enter the name of location " << i << ": (Or enter 'back' to re-enter the previous location).\n";
            cin >> choice;

            if (Validation::CheckEB(choice)) { 
                i--;
                string locationToRename = toString[i];
                toString.erase(i);
                
                i--;
                continue;
            }

            Location = choice;
        }
        else {
            cout << "Enter the name of location " << i << ":\n";
            cin >> Location;
        }

        Location= Validation::format(Location);

        
        while (toInt.find(Location) != toInt.end()) {
            Colors("Location already exists.\n",4);
            cout<<"Enter the name of location " << i << ":\n";
            cin >> Location;
            Location = Validation::format(Location);
        }
        toInt[Location] = i;
        toString[i] = Location;
        nodes++;
    }

    if (nodes >= 2) {
        Validation::userGuide(choice,"How many roads would you like to add: (Or enter '0' to skip).", 2, roads);

        for (int i = 0; i < roads; i++) {
            cout << "\nRoad #" << i + 1 << ":\n";
            cout << "Enter the name of the first location: (Or enter 'exit' to exit this operation).\n";
            cin >> Location1;

            if (Validation::CheckEB(Location1)) {
                break;
            }

            Location1 = Validation::format(Location1);

            
            while(toInt.find(Location1) == toInt.end()){
                Colors("Invalid input, Location does not exist.\n",4);
                cout<<"Re-enter the name first location : \n";
                cin >> Location1;
                Location1 = Validation::format(Location1); //~edited by Mariam & Mo
            }
            e.from = toInt[Location1];
            cout << "Enter the name of the second location: (Or enter 'exit' to exit this operation).\n";
            cin >> Location2;

            if (Validation::CheckEB(Location2)) {
                break;
            }

            Location2 = Validation::format(Location2);

            while (toInt.find(Location2) == toInt.end()) {
                Colors("Invalid input, Location does not exist.\n",4);
                cout<<"Re-nter the name of the second location:\n";
                cin >> Location2;
                Location2 = Validation::format(Location2);//~edited by Mariam & Mo
            }
            e.to = toInt[Location2];

            Validation::userGuide(choice,"Enter the length of the road between them:", 3, dist, "Would you like to proceed with the length that you entered? y/n");

            e.distance = dist;
            edges.push_back(e);
            numOfEdges++;

            if (type == 2) {
                edge e2;
                e2.to = toInt[Location1];
                e2.from = toInt[Location2];
                e2.distance = dist;
                edges.push_back(e2);
                numOfEdges++;
            }
        }
    }
}

//Function that displays the shortest path between to locations (if a path exists).
//It takes one argument, a boolean representing whether the user called the function for test mode or not.
void Graph::Path(bool test) {
    
    int startNode, endNode, distance = -1;

    if (nodes >= 2) {
        if (numOfEdges >= 1) {

            if (test == 1) {
                Colors("Welcome to testing mode.\n\n", 6);
            }

            do {
                cout << "Enter the name of the location that you'd like to find the shortest path starting from : (Or enter 'exit' to exit this operation).\n";
                cin >> Location1;

                if (Validation::CheckEB(Location1)) {
                    return;
                }

                Location1 = Validation::format(Location1);

                while (toInt.find(Location1) == toInt.end()) {
                    Colors("Invalid input, Location does not exist.\n", 4);
                    cout << "Re-enter the name of the location that you'd to find the shortest path starting from: (Or enter 'exit' to exit this operation).\n";
                    cin >> Location1;

                    if (Validation::CheckEB(Location1)) {
                        return;
                    }

                    Location1 = Validation::format(Location1);
                }
                cout << "Enter the name of the location you'd like to go to: (Or enter 'exit' to exit this operation).\n";
                cin >> Location2;

                if (Validation::CheckEB(Location2)) {
                    return;
                }

                Location2 = Validation::format(Location2);

                while (toInt.find(Location2) == toInt.end() || Location1 == Location2) {

                    Location1 == Location2 ? Colors("the destination must be different from the start location.\n", 4) : Colors("Invalid input, Location does not exist.\n", 4);
                    cout << "Re-enter the name of the location you'd like to go to: (Or enter 'exit' to exit this operation).\n";
                    cin >> Location2;

                    if (Validation::CheckEB(Location2)) {
                        return;
                    }

                    Location2 = Validation::format(Location2);
                }

                startNode = toInt[Location1];
                endNode = toInt[Location2];

                if (test == 1) {
                    
                    Colors("\nDijkstra:\n", 3);
                    algoOutputTest(startNode, endNode, shortestPath::dijkstra);

                    
                    Colors("\nBellman-Ford:\n", 3);
                    algoOutputTest(startNode, endNode, shortestPath::bellmanFord);

                    
                    Colors("\nFloyd-Warshall:\n", 3);
                    algoOutputTest(startNode, endNode, shortestPath::floydWarshall);
                }
                else {
                    vector<int>answer = shortestPath::getPath(startNode, endNode, distance, nodes, edges, paths, queries);

                    if (distance != -1) {
                        cout << "\nThe shortest path:\n";
                        for (int i = 0; i < answer.size(); i++) {

                            if (i == answer.size() - 1) {
                                cout << toString[answer[i]];
                            }
                            else {
                                cout << toString[answer[i]] << " --> ";
                            }

                        }
                        cout << "\nAnd is of total distance: " << distance << endl;
                    }
                    else {
                        Colors("No path found.\n", 4);
                    }
                }
                cout << "\nWould you like to do another query? y/n\n";

                Validation::CheckYN(choice);

            } while (choice[0] == 'y');
        }
        else {
            Colors("No roads found in the graph, this operation cannot proceed.\n", 4);
        }
    }

    else {
        Colors("Number of locations is less than two, a road cannot possibly exist.\n", 4);
    }
}


//Function that prompts different operations on the graph depending on the input of the user.

void Graph::updateGraph() { 
    cout << "\nPlease enter:\n'1' to add a location\n'2' to delete a location\n'3' to add a road\n'4' to delete a road\n'5' to update a road\n'6' to display data\n'7' to find the shortest path between two locations\n'8' to run testing mode\n'9' to return to start menu.\n>> ";
    
    Validation::CheckNumbers(4, choice);
    cout << endl;
    
    int i = stoi(choice);
    
    switch (i) {
    case 1:
        addLocation();
        break;
    case 2:
        deleteLocation();
        break;
    case 3:
        roadFns('a');
        break;
    case 4:
        roadFns('d');
        break;
    case 5:
        roadFns('u');
        break;
    case 6:
        displayGraph();
        break;
    case 7:
        Path(0);
        break;
    case 8:
        Path(1);
        break;
    case 9:
        return; //~mo
       
    default:
        Colors("Invalid input.\n",4);
    }
    updateGraph();
}

//Function that adds a new location to the graph.

void Graph::addLocation() {
    Colors("\nNOTE: while entering the name of locations that consist of more than one word, please insert a '-' between them (e.g Ain-Elsokhna).\n\n", 3);
    do {

        RE_ENTER:
        cout << "Enter the name of the new location: (Or enter 'exit' to exit this operation).\n";
        cin >> Location;

       

        Location = Validation::format(Location);

        if (Validation::CheckEB(Location)) {
            return;
        }
        if (toInt.find(Location) != toInt.end()) {
            Colors("Location already exists.\n", 4);
            goto RE_ENTER; //~mo
        }


        
        nodes++;
        toInt[Location] = nodes;
        toString[nodes] = Location;
        Colors("Added successfully.\n", 2);
        cout<<"\nWould you like to add another location ? y/n\n";

        Validation::CheckYN(choice);

    } while (choice[0] == 'y');
}

//Function that deletes a location in the graph.

void Graph::deleteLocation() {
    int wanted_location;

    if (nodes >= 1) {
        do {
            cout << "Enter the name of the location that you would like to delete: (Or enter 'exit' to exit this operation).\n";
            cin >> Location;

            if (Validation::CheckEB(Location)) {
                break;
            }

            Location = Validation::format(Location);

            while (toInt.find(Location) == toInt.end()) {
                Colors("Invalid input, Location does not exist.\n", 4);
                cout << "Please re-enter the name of the the location you would like to delete: (Or enter 'exit' to exit this operation).\n";
                cin >> Location;

                if (Validation::CheckEB(Location)) { //~mo
                    return;
                }
                Location = Validation::format(Location);
            }

            wanted_location = toInt[Location]; //get integer of this string
            deleteEdgesRlocation(wanted_location); //delete attached edges to this integer
            toString.erase(wanted_location); // delete the string from the mapping


            toInt.erase(Location);//~mo
            
            nodes--;
            Colors("Deleted successfully.\n",2);
            reset(); 

            if (nodes == 0) {
                break;
            }

            cout << "\nWould you like to delete another location? y/n\n";

            Validation::CheckYN(choice);

        } while (choice[0] == 'y');
    }
    else {
        Colors("No Locations found in the graph , this operation cannot proceed.\n",4);
    }
}

//Function that applies different operations on an edge (operations include adding, deleting, and updating an edge).
//It takes one character as an argument, representing the operation that the user wishes to apply: ('a' stands for adding,'d' stands for deleting, and 'u' stands for updating).

void Graph::roadFns(char operation) {
    int dist;
    edge e;

    if (nodes >= 2) {
        if (numOfEdges > 0 || operation == 'a') {
            do {
                cout << "Enter the name of the two locations which the road connects:\nEnter the first location. (Or enter 'exit' to exit operation).\n";
                cin >> Location1;

                if (Validation::CheckEB(Location1)) {
                    break;
                }

                bool valid = true;

                Location1 = Validation::format(Location1);

                while (toInt.find(Location1) == toInt.end()) {
                    Colors("Invalid input, Location does not exist.\n", 4);
                    cout << "Re-enter the name of the first location: (Or enter 'exit' to exit this operation).\n";
                    cin >> Location1;

                    if (Validation::CheckEB(Location1)) {
                        valid = false;
                        break;
                    }

                    Location1 = Validation::format(Location1);
                }

                if (!valid) {
                    break;
                }

                cout << "Enter the name of the second location: (Or enter 'exit' to exit this operation).\n";
                cin >> Location2;

                if (Validation::CheckEB(Location2)) {
                    break;
                }

                valid = true;

                Location2 = Validation::format(Location2);
                if (Location2 == Location1) { //~mo
                    Colors("the destination must be different from the start location.\n", 4);
                    goto RE_ENTER;
                }


                while (toInt.find(Location2) == toInt.end()) {
                    Colors("Invalid input, Location does not exist.\n", 4);


                    RE_ENTER: //~mo
                    cout << "Re-enter the name of the second location: (Or enter 'exit' to exit this operation).\n";
                    
                 
                    cin >> Location2;

                    if (Validation::CheckEB(Location2)) {
                        valid = false;
                        break;
                    }
                    Location2 = Validation::format(Location2);

                    if (Location2 == Location1) {
                        Colors("the destination must be different from the start location.\n", 4);
                        goto RE_ENTER;
                    }

                }

              
                
                if (!valid) {
                    break;
                }

                int node1 = toInt[Location1];
                int node2 = toInt[Location2];
                e.from = node1;
                e.to = node2;

                //this message is to specify whether the length entered is the current length (delete/update operations) or Adding a new edge
                string message = (operation == 'a' ? "" : "current");
                Validation::userGuide(choice, "Enter the " + message + " length of the road between them : ", 3, dist, "Would you like to proceed with the length that you entered ? y / n");
                
                e.distance = dist;

                if (operation == 'a') {
                    edges.push_back(e);
                    numOfEdges++;

                    if (type == 2) {
                        edge e2;
                        e2.to = toInt[Location1];
                        e2.from = toInt[Location2];
                        e2.distance = dist;
                        edges.push_back(e2);
                        numOfEdges++;
                    }

                    reset();

                    Colors("Road added Successfully.\n", 2);

                    if (numOfEdges > 0) {
                        cout << "\nWould you like to add another road? y/n\n";
                    }
                    else {
                        break;
                    }
                }
                else if (operation == 'd') {
                    deleteEdge(e);

                    if (numOfEdges > 0) {
                        cout << "\nWould you like to delete another road? y/n\n";
                    }
                    else {
                        break;
                    }
                }
                else {
                    int index1 = findEdge(e);

                    if (index1 != -1) {
                        cout << "Enter the new length of the road:\n";
                        int newDistance;
                        cin >> newDistance;
                        edges[index1].distance = newDistance;

                        if (type == 2) { //for undirected ~mo
                            swap(e.from, e.to);
                            int index2 = findEdge(e);
                            edges[index2].distance = newDistance;
                        }
                   
                        Colors("Road updated successfully.\n", 2); //~mo
                        reset();
                    }
                    cout << "\nWould you like to update another road ? y/n\n";
                }

                Validation::CheckYN(choice);

            } while (choice[0] == 'y');
        }
        else {
            Colors("No Roads found in the graph, this operation cannot proceed.\n",4);
        }
    }
    else {
        Colors("Number of locations is less than two, a road cannot possibly exist.\n", 4);
    }
}

//Function that deletes an edge, it takes edge as an argument and matches it & deletes it and its corresponding one in case of undirected


void Graph::deleteEdge(edge& e) {
    

    int idx = findEdge(e);
    if (idx == -1) {
        return;
    }
    edges.erase(edges.begin() + idx);

    if (type == 2) {
        swap(e.from, e.to);
        idx = findEdge(e);
        edges.erase(edges.begin() + idx);
    }


    reset();
    Colors("Road(s) deleted successfully.\n", 2);
}
/*
Function that resets two containers:
-queries: which holds the shortest paths from previous queries done by the user.
-paths: which holds all of the sub paths that form the full short path between the two desired locations.
(e.g when the shortest path between 1 and 7 is 1 --> 3 --> 5 --> 7 then we implicitly know that the shortest path between 3 and 7 is 3 --> 5 --> 7,
these sub paths are stored for future references).

This function is called after adding, deleting, updating edges, and after deleting a location.
*/

void Graph::reset() {
    queries.clear();
    paths.clear();
}

//Function that deletes all the edges connected to a certain location, It's called when a location is deleted.
//It takes the deleted location as an argument, and deletes all the edges that are connected to it.

void Graph::deleteEdgesRlocation(int location) {
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].from == location || edges[i].to == location) {
            edges.erase(edges.begin() + i);
            i--;
        }
    }
}

//Function that checks if a certain edge exists in a graph.
//it takes edge as an argument


int Graph::findEdge(edge &e) {
   
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].from == e.from && edges[i].to == e.to && edges[i].distance == e.distance) {
            return i;
        }
    }
    Colors("Invalid input, road does not exist.\n", 4);
    return -1;
}

/*
describe locations and roads
//directed (-->) or undirected (<-->)
*/

void Graph::displayGraph() {
    Colors(name, 13);
    cout << " consists of ";
    Colors(to_string(nodes), 13);
    cout << " locations and ";
    Colors(to_string(edges.size()), 13);
    cout << " roads\n\n";
    string arrow = (type == 1 ? " --> " : " <--> ");

    for (int i = 0; i < edges.size(); i += type) {
        cout << toString[edges[i].from];
        Colors(arrow, 2);
        cout << toString[edges[i].to];
        Colors(" -- with distance of : " + to_string(edges[i].distance), 7);
        cout << endl;
    }
    cout << endl;
}