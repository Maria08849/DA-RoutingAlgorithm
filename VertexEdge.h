#ifndef PROJDA2_VERTEXEDGE_H
#define PROJDA2_VERTEXEDGE_H


#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

using namespace std;

class Edge;

class Vertex {
public:
    Vertex(int id);

    int getId() const;
    vector<Edge *> getAdj() const;
    double getLatitude() const;
    double getLongitude() const;
    bool isVisited() const;
    int getDist() const;
    Edge *getPath() const;
    vector<Edge *> getIncoming() const;


    void setLatitude(double lat);
    void setLongitude(double lon);
    void setVisited(bool visited);
    void setDist(double dist);
    void setPath(Edge *path);
    Edge *addEdge(Vertex *dest, double distance);

protected:
    int id;         // identifier
    vector<Edge *> adj;  // outgoing edges

    double latitude = -1;
    double longitude = -1;

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    int dist = -1;
    Edge *path = nullptr;

    vector<Edge *> incoming; // incoming edges
};

/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double distance);

    Vertex *getDest() const;
    double getDistance() const;
    Vertex *getOrig() const;

protected:
    Vertex *dest = nullptr; // destination vertex
    double distance;

    // used for bidirectional edges
    Vertex *orig = nullptr;
};
#endif //PROJDA2_VERTEXEDGE_H
