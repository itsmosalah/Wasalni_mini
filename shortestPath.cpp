#include "shortestPath.h"
#include <set>
const int N=1e3+3;

using namespace std;





//This function retrieves queries that have already been processed before
vector<int> shortestPath::retrieveQuery(int start, int dest, vector<pair<int,int>>&path, int & distance){

        vector<int> ans;
        int startDis = 0, destDis = 0;
        bool startFound = false, destFound = false;

        for (auto i : path){
            if (i.first == start)
                startFound = true, startDis = i.second;

            if (startFound)
                ans.push_back(i.first);

            if (i.first == dest)
                destFound = true, destDis = i.second;

            if (startFound && destFound)
                break;
        }

        //distance equals absolute difference between accumulative distances between start to destination
        distance = abs(destDis-startDis);

        return ans;
    }



//Calculating shortest path using Dijkstra, Floyed-Warshall and Bellmanford Algorithms
//each of the 3 functions returns a vector of pair. where each pair has first representing node
//and second represenets accumulative distance

//Written by Mohamed Salah
vector<pair<int,int>> shortestPath::dijkstra(int start,
                                          int dest,
                                          int nodes,
                                          int &distance,
                                          vector<edge>&edges
    )
    {
        //if start is same as destination, distance = 0
        if (start == dest){
            distance = 0; return {{start,0}};
        }

        //all distances are initially 2e9 (infinity), all parents to nodes are initially -1
        vector<int> d(N, 2e9);
        vector<int> par(N, -1);

        //adjacency list of edges
        //vector<vector<edge>>g(nodes+1);
        vector<vector<edge>>g(N);

        //priority queue, sorts edges in increasing order according to distance, check edge class definition
        priority_queue<edge>q;

        //creating adjacency list out of edges. to each node its outgoing edges
        for(auto e : edges)
            g[e.from].push_back(e);


        //pushing the start node
        q.push({-1,start,0});

        //initializing first node to have 0 distance and no parent
        d[start] = 0; par[start] = -1;

        //dijkstra algorithm
        while (!q.empty()){
            int curNode = q.top().to, curDis = q.top().distance;
            q.pop();

            if (d[curNode] < curDis) continue;

            if (curNode == dest) break;

            for(auto e : g[curNode]){
                int newDis = e.distance + curDis;

                if (d[e.to] > newDis){
                    d[e.to] = newDis;
                    par[e.to] = curNode;
                    q.push({e.from,e.to,newDis});
                }
            }
        }

        //if parent of destination node = -1, it means it was never reached
        if (par[dest] == -1){
            //-1 distance is a flag for no reach, returning empty vector
            distance = -1; return {};
        }
        distance = d[dest];

        vector<pair<int,int>>path;
        int node = dest;
        while(node != -1){
            //path now contains the node and the accumulative distance to it
            path.emplace_back(node,d[node]);
            node = par[node];
        }

        //reversed to be in correct order
        reverse(path.begin(), path.end());

        return path;
    }


//written by Mariam
vector<pair<int,int>> shortestPath::bellmanFord(int start,
                                         int dest,
                                         int nodes,
                                         int &distance,
                                         vector<edge>&edges)
{
    //if start is same as destination, distance = 0
    if (start == dest){
        distance = 0; return {{start,0}};
    }

    int INF = 2e9;
    vector<int> d(N, INF);
    vector<int> par(N, -1);
    d[start] = 0;



    for(int i = 1 ; i <= nodes - 1 ; i++)
    {
        for(auto & edge : edges)
        {
            int u = edge.from;
            int v = edge.to;
            int w = edge.distance;

            if(d[v] > d[u] + w)
            {
                d[v] = d[u] + w;
                par[v] = u;
            }
        }
    }


    /*
     This step for checking if there is a negative cycle, but as we don't have
     negative edges, it's not important

    for(int i = 0 ; i < edges.size() ; i++)
    {
        int u = edges[i].from;
        int v = edges[i].to;
        int w = edges[i].distance;

        if(d[v] > d[u] + w)
        {
            d[v] = -INF;
            par[v] = u;
            distance = -1;
            return {};
        }
    }
    */

    int node = dest;

    if (par[dest] == -1)
    {
        distance = -1;
        return {};
    }

    vector<pair<int,int>>path;

    while(node != -1)
    {
        path.emplace_back(node , d[node]);
        node = par[node];
    }

    // to be in correct order

    reverse(path.begin() , path.end());

    distance = d[dest];

    return path;
}


//written by Mariam
vector<pair<int,int>> shortestPath::floydWarshall(int start,
                                            int dest,
                                            int nodes,
                                            int &distance,
                                            vector<edge>&edges)
{
    int INF = 1e9;
    
    set<long long>Set;
    
    for (auto &e : edges)
    {
        Set.insert(e.from);
        Set.insert(e.to);
    }
    

    long long dp[103][103];

    long long costOfSToD = 0;

    for(int i=1;i<=100;i++)
    {
        for(int j=1;j<=100;j++)
        {
            if(i==j)
            {
                dp[i][j]=0;
                continue;
            }
            dp[i][j]=INF;
        }
    }

    int par[103][103];

    for(int i = 1 ; i <= 100 ; i++)
    {
        for(int j = 1 ; j <= 100 ; j++)
        {
            par[i][j] = j;
        }
    }


    for(auto & e:edges)
    {
        int u = e.from;
        int v = e.to;
        int w = e.distance;

        //to consider minimum when there are multiple edges
        dp[u][v] = min(1LL*w, dp[u][v]);

        if(u == start && v == dest)
        {
            costOfSToD = dp[u][v];
        }
    }

    
   
    for (auto k : Set)
    {
        for (auto i : Set)
        {
            for (auto j : Set)
            {
                if (dp[i][k] + dp[k][j] < dp[i][j])
                {
                    dp[i][j] = dp[i][k] + dp[k][j];

                    par[i][j] = par[i][k];
                }
            }
        }
    }

   

    if(par[start][dest] == dest && nodes > 2 && costOfSToD != dp[start][dest] || dp[start][dest] == INF)
    {
        distance = -1;
        return {};
    }

    vector<pair<int,int>>path;


    int node = start;

    while (node != dest)
    {
        path.emplace_back(node,dp[start][node]);
        node = par[node][dest];
    }

    path.emplace_back(dest,dp[start][node]);

    distance = int(dp[start][dest]);

    return path;
}



//Written by Mohamed Salah
vector<int> shortestPath::getPath(
        int start, int dest, int &distance, int nodes,
        vector<edge>&edges,
        vector < vector < pair < int , int > > > &paths,
        map < pair < int , int > , int > &queries
        )
{



    vector<int> ans;
    //in case query already exists
    if (queries.find({start,dest}) != queries.end())
        ans = retrieveQuery(start, dest, paths[queries[{start, dest}]], distance);


    else {
        //we get path from selected algorithm by comparing complexities
        vector<pair<int,int>> path;
        if(nodes < 100)
        {
            path = floydWarshall(start, dest, nodes, distance, edges);
        }
        else if( (nodes + int(edges.size())) * log2(nodes) < nodes * int(edges.size()))
        {
            path = dijkstra(start, dest, nodes, distance, edges);
        }
        else
        {
            path = bellmanFord(start, dest, nodes, distance, edges);
        }

        for (auto&x:path)
            ans.push_back(x.first);

        paths.push_back(path);
        int curPathIndex = int(paths.size())-1;

        //we assign path and all sub-paths to the query index
        for (int i = 0; i < ans.size(); i++)
            for (int j = i+1; j < ans.size(); ++j)
                queries[{ans[i], ans[j]}] = curPathIndex;

    }

    return ans;
}



