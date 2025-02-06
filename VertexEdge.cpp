#include "VertexEdge.h"

/************************* Vertex  **************************/

/*!
 * Default constructor
 * @param id vertex id
 */
Vertex::Vertex(int id) : id(id) {}


/*!
 * Auxiliary function to add an outgoing edge to a vertex, with a given destination vertex and distance
 * @param d destination vertex
 * @param distance distance
 * @return new edge that is created
 */
Edge *Vertex::addEdge(Vertex *d, double distance) {
    auto newEdge = new Edge(this, d, distance);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}


/*!
 *
 * @return id
 */
int Vertex::getId() const {
    return this->id;
}


/*!
 *
 * @return vector with the adjacent edges
 */
vector<Edge *> Vertex::getAdj() const {
    return this->adj;
}


/*!
 *
 * @return this vertex's latitude
 */
double Vertex::getLatitude() const {
    return this->latitude;
}


/*!
 *
 * @return this vertex's longitude
 */
double Vertex::getLongitude() const {
    return this->longitude;
}


/*!
 *
 * @return true if the vertex is visited, false otherwise
 */
bool Vertex::isVisited() const {
    return this->visited;
}


/*!
 *
 * @return distance
 */
int Vertex::getDist() const {
    return this->dist;
}


/*!
 *
 * @return path
 */
Edge *Vertex::getPath() const {
    return this->path;
}


/*!
 *
 * @return vector with incoming edges
 */
vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}


/*!
 * Sets latitude for this vertex
 * @param lat latitude
 */
void Vertex::setLatitude(double lat) {
    this->latitude = lat;
}


/*!
 * Sets longitude for this vertex
 * @param lon longitude
 */
void Vertex::setLongitude(double lon) {
    this->longitude = lon;
}


/*!
 * Sets the vertex as visited
 * @param visited mew state of visited
 */
void Vertex::setVisited(bool visited) {
    this->visited = visited;
}


/*!
 * Sets distance
 * @param dist new distance
 */
void Vertex::setDist(double dist) {
    this->dist = dist;
}


/*!
 * Sets the path of a vertex
 * @param path new path
 */
void Vertex::setPath(Edge *path) {
    this->path = path;
}



/********************** Edge  ****************************/

/*!
 * Default constructor
 * @param orig origin's vertex
 * @param dest destination's vertex
 * @param network network
 */
Edge::Edge(Vertex *orig, Vertex *dest, double distance): orig(orig), dest(dest), distance(distance) {}


/*!
 *
 * @return destination
 */
Vertex * Edge::getDest() const {
    return this->dest;
}


/*!
 *
 * @return distance
 */
double Edge::getDistance() const {
    return this->distance;
}


/*!
 *
 * @return origin
 */
Vertex *Edge::getOrig() const {
    return this->orig;
}

