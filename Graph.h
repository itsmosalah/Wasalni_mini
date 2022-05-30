#pragma once
#include<iostream>
#include <map>
#include <vector>
#include <string>
#include"Validation.h"
#include "shortestPath.h"

using namespace std;

class Graph
{
public:
	string name;
    int type;
    int nodes;
	int numOfEdges;
    map < string, int > toInt;
    map < int, string > toString;
    vector < vector < pair < int, int > > > paths;
    map < pair < int, int >, int > queries;
    vector < edge > edges;

public:
	void algoOutputTest(int start, int dest, vector<pair<int, int>>(*algorithm)(int, int, int, int&, vector<edge>&));
	void insertGraph();
	void Path(bool test);
	void updateGraph();
	void addLocation();
	void deleteLocation();
	void roadFns(char operation);
	void deleteEdge(edge& e);
	void reset();
	void deleteEdgesRlocation(int location);
	int findEdge(edge &e);
	void displayGraph();
};

	


