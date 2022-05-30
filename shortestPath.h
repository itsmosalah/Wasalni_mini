#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <queue>
#include <cmath>
#include "edge.h"

using namespace std;

#ifndef UNTITLED2_SHORTESTPATH_H
#define UNTITLED2_SHORTESTPATH_H



class shortestPath {
public:


    static vector<int> retrieveQuery (int start, int dest, vector<pair<int,int>>&path, int & distance);

    static vector<pair<int,int>> dijkstra(int start,
                                          int dest,
                                          int nodes,
                                          int &distance,
                                          vector<edge>&edges
    );

    static vector<pair<int,int>> bellmanFord(int start,
                                             int dest,
                                             int nodes,
                                             int &distance,
                                             vector<edge>&edges);

    static vector<pair<int,int>> floydWarshall(int start,
                                               int dest,
                                               int nodes,
                                               int &distance,
                                               vector<edge>&edges);

    static vector<int> getPath(
            int start, int dest, int &distance, int nodes,
            vector<edge>&edges,
            vector < vector < pair < int , int > > > &paths,
            map < pair < int , int > , int > &queries
            );

};


#endif //UNTITLED2_SHORTESTPATH_H

