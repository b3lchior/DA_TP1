//
// Created by tomas on 3/13/2023.
//

#include "../headers/Graph.h"


int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(const string &id) const {
    for (auto v : vertexSet)
        if (v->getId() == id)
            return v;
    return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
int Graph::findVertexIdx(const string &id) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getId() == id)
            return i;
    return -1;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(string name,string district,string municipality,string township,string line) {
    if (findVertex(name) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(name,district,municipality,township,line));
    return true;
}

bool Graph::removeVertex(const string &id) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getId() == id) {
            auto v = *it;
            v->removeOutgoingEdges();
            for (auto u : vertexSet) {
                u->removeEdge(v->getId());
            }
            vertexSet.erase(it);
            delete v;
            return true;
        }
    }
    return false;
}


/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const string &sourc, const string &dest, double w, string service) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w,service);
    return true;
}

Edge* Graph::findEdge(Vertex * dest,Vertex *orig,double weight,string service){
    for(Edge* e : orig->getAdj()){
        if(e->getDest() == dest && e->getService() == service){
            return e;
        }
    }
}

Edge* Graph::findEdge(Edge e1){
    for(Edge* e : e1.getOrig()->getAdj()){
        if(e->getDest() == e1.getDest() && e->getService() == e1.getService()){
            return e;
        }
    }
}

Edge* Graph::findEdge(string orig , string dest){
    Vertex* v = findVertex(orig);
    for(Edge* e : v->getAdj()){
        if(e->getDest()->getId() == dest ){
            return e;
        }
    }
}

bool Graph::addBidirectionalEdge(const string &sourc, const string &dest, double w , string service) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w , service);
    auto e2 = v2->addEdge(v1, w,service);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}