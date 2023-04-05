//
// Created by tomas on 3/13/2023.
//

#ifndef DA_TP1_GRAPH_H
#define DA_TP1_GRAPH_H


#include <vector>
#include "VertexEdge.h"
using namespace std;
class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given ID.
    */
    Vertex *findVertex(const string &id) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(string name,string district,string municipality,string township,string line);
    bool removeVertex(const string &id);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const string &sourc, const string &dest, double w , string service);
    bool addBidirectionalEdge(const string &sourc, const string &dest, double w, string service);
    Edge* findEdge(Vertex * dest,Vertex *orig,double weight,string service);
    Edge* findEdge(string orig , string dest);
    Edge* findEdge(Edge e);
    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;
protected:
    std::vector<Vertex *> vertexSet;    // vertex set

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const string &id) const;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);


#endif //DA_TP1_GRAPH_H
