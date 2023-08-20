#include <iostream>
#include<string>
#include <vector>
#include <fstream> 
#include <map>
#include "Graph.h" 
#include "FileHandling.h"
using namespace std;


//----------------------------------------------------READ FUNCTIONS------------------------------------------------------------//


void FileHandling::loadData(Graph &g) { 
	ifstream file;
	file.open("graphs/" + g.name + ".txt");
	ReadGraph(g, file);
	ReadMaps(g, file);
	ReadResults(g, file);
	file.close();
}


void FileHandling::ReadGraph(Graph& g, ifstream& file) {  

	edge e;
	file >> g.type;
	file >> g.nodes;
	file >> g.numOfEdges;

	while (true) {
		file >> e.to;
		if (e.to == -1) return; // -1 is a token that tells us that there are no more graph data in the file
		file >> e.from;
		file >> e.distance;
		g.edges.push_back(e);
	}

}

//--------------------------------------import the mapping data from the file to toInt and toString containers------------------------------//

void FileHandling::ReadMaps(Graph& g, ifstream& file) {
	string str; int in;
	while (true) {
		file >> str;
		if (str == "&&") return; // && is a token that tells us that there are no more graph data in the file
		file >> in;
		g.toInt[str] = in; g.toString[in] = str;
	}

}

//------------------------------Function to import the algo output data from file to the paths and queries containers------------------------//

void FileHandling::ReadResults(Graph &g, ifstream& file) {

	bool flag = true;
	while (flag) {      

		vector<pair<int, int>> temp;
		int in1; int in2;
		while (true) {

			file >> in1;
			if (in1 == -10) { //when the file reaches -10 that means that there is no more paths
				flag = false;
				break;
			}
			if (in1 == -150)  break; // -150 means that the path is completed
			file >> in2;
			temp.push_back(make_pair(in1, in2));

		}
		if (!flag)break;
		g.paths.push_back(temp);
	}
	//FOR QUERIES.
	while (!file.eof()) {    
		int p1, p2, value;
		file >> p1 >> p2 >> value;
		g.queries[make_pair(p1, p2)] = value;
	}
}


//----------------------------------------------ALL WRITE FUNCTIONS IN THE FIRST FILE--------------------------------------------------------//

void FileHandling::writeAll(Graph &g) {
	ofstream file;
	file.open("graphs/" + g.name + ".txt");
	WriteGraph(g, file);
	WriteMaps(g, file);
	WriteResults(g, file);
	file.close();
}

void FileHandling::WriteGraph(Graph &g, ofstream& file) {

	file << g.type << " ";
	file << g.nodes << endl;
	file << g.numOfEdges << endl;
	for (auto i : g.edges) {
		file << i.to << " ";
		file << i.from << " ";
		file << i.distance << endl;
	}
	file << -1 << endl << endl;
}

void FileHandling::WriteMaps(Graph &g, ofstream& file) {
	for (auto i : g.toInt) {
		file << i.first << " " << i.second << endl;
	}
	file << "&&" << endl << endl;
}

void FileHandling::WriteResults(Graph &g, ofstream& file) {
	for (auto i : g.paths) {

		for (auto j : i) {
			file << j.first << " " << j.second << " ";
		}
		file << -150 << endl;
	}
	file << -10 << endl << endl;
	if (!g.queries.empty())
	{
		auto it = g.queries.begin(); it++;
		for (; it != g.queries.end(); it++) {
			file << it->first.first << " " << it->first.second << ' ' << it->second << endl;
		}
	}



}





//----------------------------------------------Functions of graphs name file--------------------------------------------------------//

 void FileHandling::load_graphsname(unordered_set<string>& graphsname) {
	ifstream file;

	//this avoids exception when file does not exist prior to opening
	file.open("graphsname.txt", ios::app); //~Edited by Mariam
	string s;
	while (!file.eof()) {
		file >> s;
		if (!s.empty()) graphsname.insert(s);
	}

}

 void FileHandling::save_graphsname(unordered_set<string>& graphsname) {
	ofstream file;
	file.open("graphsname.txt");

	int index = 0;
	for (auto &name : graphsname) {
		file << name << (index < int(graphsname.size()) - 1 ? "\n" : "");
		index++;
	}
}


