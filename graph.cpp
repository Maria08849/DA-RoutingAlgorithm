#include "graph.h"

/*!
 * Default constructor
 * @param hasDir true if it's a directed graph, false otherwise
 */
Graph::Graph(bool hasDir) : hasDir(hasDir) {}


/*!
 * Reads nodes' file and sets vertexes for this graph
 * Used when both nodes and edges' file are provided
 * O(n)
 * @param nodes path to nodes file
 */
void Graph::readNodes(string nodes) {
    string path = nodes;
    string line;
    string id, lat, lon;
    ifstream file(path);

    if (file.is_open()) {
        getline(file, line);
        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, id, ',');
            getline(ss, lat, ',');
            getline(ss, lon, ',');
            if (!addVertex(stoi(id))) continue;
            Vertex *v = findVertex(stoi(id));
            v->setLatitude(stod(lat));
            v->setLongitude(stod(lon));
        }
        file.close();
    }
    else {
        cout << "Error opening nodes file." << endl;
        exit(1);
    }
}


/*!
 * Reads edges' file and sets edges for this graph
 * Used when both nodes and edges' files are provided
 * O(n)
 * @param edges path to edges file
 */
void Graph::readEdges(string edges) {
    string path = edges;
    string line;
    string orig, dest, dist;
    ifstream file(path);

    if (file.is_open()) {
        getline(file, line);
        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, orig, ',');
            getline(ss, dest, ',');
            getline(ss, dist, ',');
            if (hasDir) {
                if (!addEdge(stoi(orig), stoi(dest), stod(dist))) continue;
            } else {
                if (!addBidirectionalEdge(stoi(orig), stoi(dest), stod(dist))) continue;
            }
        }
        file.close();
    }
    else {
        cout << "Error opening edges file." << endl;
        exit(1);
    }
}


/*!
 * Reads edges and nodes' files and sets vertexes and edges for this graph,
 * Used when both nodes and edges' file are provided
 * O(n)
 * @param nodes path to nodes file
 * @param edges path to edges file
 */
void Graph::readFiles(string nodes, string edges) {
    readNodes(nodes);
    readEdges(edges);
}


/*!
 * Reads edges' file and sets vertexes and edges for this graph,
 * Used when only the edges' file is provided
 * O(n)
 * @param edges path to edges file
 */
void Graph::readEdgesFile(string edges) {
    string path = edges;
    string line;
    string orig, dest, dist;
    ifstream file(path);

    if (file.is_open()) {
        getline(file, line);
        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, orig, ',');
            getline(ss, dest, ',');
            getline(ss, dist, ',');
            addVertex(stoi(orig));
            addVertex(stoi(dest));
            if (hasDir) {
                if (!addEdge(stoi(orig), stoi(dest), stod(dist))) continue;
            } else {
                if (!addBidirectionalEdge(stoi(orig), stoi(dest), stod(dist))) continue;
            }
        }
        file.close();
    }
    else {
        cout << "Error opening edges file." << endl;
        exit(1);
    }
}



/*!
 * Finds and returns vertex with id equal to the parameter
 * O(1)
 * @param id vertex's id
 * @return pointer to vertex with id equal to the parameter if it exists, else nullptr
 */
Vertex *Graph::findVertex(const int id) const {
    if (vertexMap.find(id) == vertexMap.end()) return nullptr;
    return vertexMap.find(id)->second;
}


/*!
 * Number of vertexes in the graph
 * @return number of vertexes
 */
int Graph::getNumVertex() const {
    return vertexMap.size();
}


/*!
 * Vertex map in the graph
 * @return vertex map
 */
unordered_map<int, Vertex *> Graph::getVertexMap() const {
    return vertexMap;
}


/*!
 * Adds a vertex with a given id to a graph
 * O(1)
 * @param id id we want to add
 * @return true if successful, and false if a vertex with that content already exists
 */
bool Graph::addVertex(const int id) {
    if (findVertex(id) != nullptr)
        return false;
    vertexMap.insert(make_pair(id, new Vertex(id)));
    return true;
}


/*!
 * Adds an edge to a graph, given the contents of the source and destination vertices and the distance
 * O(V)
 * @param source starting vertex's id
 * @param target destination vertex's id
 * @param distance distance
 * @return true if successful, and false if the source or destination vertex does not exist
 */
bool Graph::addEdge(const int source, const int target, const double distance) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(target);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, distance);
    return true;
}


/*!
 * Adds a bidirectional edge
 * O(V)
 * @param origin starting vertex's id
 * @param dest destination vertex's id
 * @param distance distance
 * @return true if creates the edge, false otherwise
 */
bool Graph::addBidirectionalEdge(const int origin, const int dest, const double distance) {
    auto s1 = findVertex(origin);
    auto s2 = findVertex(dest);
    if (s1 == nullptr || s2 == nullptr) {
        return false;
    }
    s1->addEdge(s2, distance);
    s2->addEdge(s1, distance);
    return true;
}


/*!
 * Haversine distance
 * O(1)
 * @param v1 first vertex
 * @param v2 second vertex
 * @return distance between vertexes
 */
double Graph::HaversineDistance(Vertex *v1, Vertex *v2) {
    double lat1, lat2, lon1, lon2;
    lat1 = v1->getLatitude();
    lat2 = v2->getLatitude();
    lon1 = v1->getLongitude();
    lon2 = v2->getLongitude();

    // distance between latitudes and longitudes
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formula
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}


/*!
 * Depth-First Search
 * O(V + E)
 * @param source starting vertex's id
 * @param dest destination vertex's id
 * @return true if the vertexes are connected, false otherwise
 */
bool Graph::dfs(const int source, const int dest) {
    auto s = findVertex(source);
    auto d = findVertex(dest);

    if (s == nullptr || d == nullptr) {
        return false;
    }

    for (auto& v : vertexMap) {
        v.second->setVisited(false);
    }

    return dfsVisit(s, dest);
}


/*!
 * Depth-First Search
 * O(V + E)
 * @param s starting vertex's id
 * @param dest destination vertex's id
 * @return true if the stations vertexes are connected, false otherwise
 */
bool Graph::dfsVisit(Vertex *s, const int dest) {
    s->setVisited(true);
    if (!s->getAdj().empty()) {
        for (auto& e : s->getAdj()) {
            auto neighbor = e->getDest();
            if (e->getDest()->getId() == dest) return true;
            if (!neighbor->isVisited()) {
                if (dfsVisit(neighbor, dest)) return true;
            }
        }
    }
    return false;
}


/*!
 * Finds the best tour in a graph
 * O(2^V)
 * @param currentNode current node
 * @param visited list of visited nodes
 * @param totalDistance total distance visited
 * @param res best result found
 * @return pair of the best tour and the distance
 */
pair<vector<Vertex *>, double> Graph::utilBacktrack(Vertex *currentNode, vector<Vertex *> &visited, double totalDistance, pair<vector<Vertex *>, double> &res) {
    visited.push_back(currentNode);  // Add the current node to visited list

    if (visited.size() == getNumVertex()) {
        // Check if there is an edge from the current node to the starting node (labeled zero)
        Edge* returnEdge = currentNode->getIncoming().front();
        if (returnEdge->getOrig()->getId() == 0) {
            totalDistance += returnEdge->getDistance();
            res.first = visited;
            res.second = totalDistance;
        }
        visited.pop_back();  // Remove the current node from visited list
        return res;
    }

    // Initialize the best result to infinity
    pair<vector<Vertex *>, double> bestRes;
    bestRes.second = INT16_MAX;

    // Iterate over the neighbors of the current node
    for (Edge *edge : currentNode->getAdj()) {
        Vertex *nextNode = edge->getDest();
        if (find(visited.begin(), visited.end(), nextNode) == visited.end()) {
            double edgeDistance = edge->getDistance();
            totalDistance += edgeDistance;

            pair<vector<Vertex *>, double> tempRes = utilBacktrack(nextNode, visited, totalDistance, res);

            // Update the result if a valid tour with smaller total distance is found
            if (!tempRes.first.empty() && tempRes.second < bestRes.second) {
                bestRes = tempRes;
            }

            totalDistance -= edgeDistance;
        }
    }

    visited.pop_back();  // Remove the current node from visited list
    return bestRes;
}


/*!
 * Backtracking algorithm
 * O(2^V)
 * @return pair with a list of nodes of the best tour and the total distance
 */
pair<vector<Vertex *>, double> Graph::backtracking() {
    vector<Vertex *> visited;
    double totalDistance = 0.0;
    pair<vector<Vertex *>, double> res;

    // Start the TSP algorithm from the node labeled zero
    Vertex *startingNode = findVertex(0);
    return utilBacktrack(startingNode, visited, totalDistance, res);
}


/*!
 * Prim's algorithm
 * O((V + E) log V)
 * @return minimum-cost spanning tree
 */
vector<pair<Vertex *, Vertex *>> Graph::primMST() {
    // Create a map to store the MST edges
    vector<pair<Vertex *, Vertex *>> mstEdges;

    // Create a priority queue to store the edges based on their weights
    auto cmp = [](const Edge *e1, const Edge *e2) {
        return e1->getDistance() > e2->getDistance(); // Min-heap based on edge weight
    };
    priority_queue<Edge *, vector<Edge *>, decltype(cmp)> pq(cmp);

    // Create a set to keep track of visited vertices
    unordered_set<Vertex *> visited;

    // Choose any vertex as the starting vertex
    Vertex *startVertex = findVertex(0);
    visited.insert(startVertex);

    // Initialize the priority queue with the edges if the starting vertex
    for (Edge *edge : startVertex->getAdj()) {
        pq.push(edge);
    }

    // Perform Prim's algorithm until all vertices are visited
    while (!pq.empty()) {
        Edge *curr = pq.top();
        pq.pop();

        Vertex *src = curr->getOrig();
        Vertex *dest = curr->getDest();

        // Skip the edge if the destination vertex is already visited
        if (visited.find(dest) != visited.end()) {
            continue;
        }

        // Add the edge to the MST
        mstEdges.push_back({src, dest});

        // Mark both vertices as visited
        visited.insert(src);
        visited.insert(dest);

        // Add the adjacent edges of the newly visited vertex to the priority queue
        for (Edge *edge : dest->getAdj()) {
            if (visited.find(edge->getDest()) == visited.end()) {
                pq.push(edge);
            }
        }
    }

    return mstEdges;
}


/*!
 * Preorder traversal of an MST
 * O(E), where E is the number of edges in the MST
 * @param root subtree's vertex to traverse
 * @param visited visited vertexes
 * @param mstEdges vector with the edges of the minimum-cost spanning tree
 * @return total distance of the preorder traversal
 */
double Graph::preorderTraversal(Vertex *root, unordered_set<Vertex *> &visited, vector<pair<Vertex *, Vertex *>> &mstEdges) {
    double totalDistance = 0.0;
    visited.insert(root);

    for (auto &vp : mstEdges) {
        if (visited.find(vp.second) != visited.end()) continue;
        bool edgeExists = false;
        for (Edge *edge : vp.first->getAdj()) {
            if (edge->getDest() == vp.second) {
                edgeExists = true;
                totalDistance += edge->getDistance();
                break;
            }
        }
        if (!edgeExists) totalDistance += HaversineDistance(vp.first, vp.second);

        totalDistance += preorderTraversal(vp.second, visited, mstEdges);
    }

    return totalDistance;
}


/*!
 * Triangular approximation algorithm
 * O((V + E) log V)
 * @return pair of the minimum-cost spanning tree and the total distance of the traversal
 */
pair<vector<pair<Vertex *, Vertex *>>, double> Graph::triangularApprox() {
    // Create the minimum spanning tree (MST)
    vector<pair<Vertex *, Vertex *>> mstEdges = primMST();
    double totalDistance = 0.0;

    // Check if the MST is empty
    if (mstEdges.empty()) {
        return make_pair(mstEdges, totalDistance);
    }

    // Get the root vertex of the MST (first key in the first element)
    Vertex *root = mstEdges[0].first;

    // Perform a preorder traversal of the MST and calculate the total distance
    unordered_set<Vertex *> visited;
    totalDistance = preorderTraversal(root, visited, mstEdges);
    return make_pair(mstEdges, totalDistance);
}


/*!
 * Approximates the Traveling salesman problem
 * Iteratively selects the nearest unvisited vertex to the current vertex, until all vertexes have been visited
 * O(V^2)
 * @return pair of visited vertices and the total distance
 */
pair<vector<Vertex *>, double> Graph::approxByVertexes() {
    vector<Vertex *> visited;
    double totalDistance = 0.0;

    // Start the tour from the vertex with id = 0
    Vertex *startVertex = findVertex(0);
    visited.push_back(startVertex);

    // Create a set to keep track of unvisited vertices
    unordered_set<Vertex *> unvisited;
    for (auto &v : vertexMap) {
        if (v.second != startVertex) {
            unvisited.insert(v.second);
        }
    }

    while (!unvisited.empty()) {
        Vertex *currVertex = visited.back();
        Vertex *nextVertex = nullptr;
        double minDistance = INT16_MAX;

        // Find the nearest unvisited vertex based on the triangular inequality
        for (Vertex *v : unvisited) {
            double distance = HaversineDistance(currVertex, v);
            if (distance < minDistance) {
                minDistance = distance;
                nextVertex = v;
            }
        }

        // Add the nearest vertex to the tour
        visited.push_back(nextVertex);
        totalDistance += minDistance;

        // Remove the visited vertex from the unvisited set
        unvisited.erase(nextVertex);
    }

    // Add the distance from the last vertex back to the start vertex (id = 0)
    totalDistance += HaversineDistance(visited.back(), startVertex);

    // Return the result
    return make_pair(visited, totalDistance);
}
