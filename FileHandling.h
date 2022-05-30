#pragma once
#include <iostream>
#include<string>
#include <vector>
#include <fstream> 
#include <map>
#include "Graph.h" // ~mo

using namespace std;



class FileHandling {
public:

	//----------------------------------------------------READ FUNCTIONS-------------------------------------------------------------------------//

	static void loadData(Graph &g);

	static void ReadGraph(Graph& g, ifstream& file);

	static void ReadMaps(Graph &g, ifstream& file);

	//---------------------------------------------Function to import the algo output data from file to the paths and queries containers---------//
	static void ReadResults(Graph &g, ifstream& file);

	//----------------------------------------------ALL WRITE FUNCTIONS IN THE FIRST FILE--------------------------------------------------------//

	static void writeAll(Graph &g);

	static void WriteGraph(Graph &g, ofstream& file);

	static void WriteMaps(Graph &g, ofstream& file);

	static void WriteResults(Graph &g, ofstream& file);

	//----------------------------------------------Functions of graphs name file--------------------------------------------------------//

	static void load_graphsname(vector<string>& graphsname);

	static void save_graphsname(vector<string>& graphsname);


};


