#ifndef PROJDA2_GRAPH_H
#define PROJDA2_GRAPH_H

#include <sstream>
#include <fstream>
#include <cmath>
#include "VertexEdge.h"
#include "DataFiles.h"

using namespace std;

class Graph {
public:
    explicit Graph(bool hasDir);

    void readNodes(string nodes);
    void readEdges(string edges);
    void readFiles(string nodes, string edges);
    void readEdgesFile(string edges);

    Vertex *findVertex(const int id) const;

    bool addVertex(const int id);

    bool addEdge(const int source, const int target, const double distance);
    bool addBidirectionalEdge(const int origin, const int destination, const double distance);

    int getNumVertex() const;
    unordered_map<int, Vertex *> getVertexMap() const;

    // returns distance between nodes
    double HaversineDistance(Vertex *v1, Vertex *v2);

    bool dfs(const int source, const int dest);
    bool dfsVisit(Vertex *s, const int dest);


    // (vector of vertexes visited, total distance)
    pair<vector<Vertex *>, double> utilBacktrack(Vertex *currentNode, vector<Vertex *> &visited, double distance, pair<vector<Vertex *>, double> &res);
    // (vector of vertexes visited, total distance)
    pair<vector<Vertex *>, double> backtracking();

    // vector of connections
    vector<pair<Vertex *, Vertex *>> primMST();
    double preorderTraversal(Vertex* root, unordered_set<Vertex*>& visited, vector<pair<Vertex *, Vertex *>> &mstEdges);
    // (vector of MST connections, total distance)
    pair<vector<pair<Vertex *, Vertex *>>, double> triangularApprox();

    pair<vector<Vertex *>, double> approxByVertexes();



protected:
    bool hasDir;
    unordered_map<int, Vertex *> vertexMap;    // vertex map
};

#endif //PROJDA2_GRAPH_H
