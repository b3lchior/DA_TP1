//
// Created by tomas on 15/03/2023.
//

#ifndef DA_TP1_VERTEXEDGE_H
#define DA_TP1_VERTEXEDGE_H


#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"

using namespace std;
class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

class Vertex {
public:

    Vertex(string name,string district,string municipality,string township,string line);
    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue
    /**
     * @brief Get the Id object
     * @return string
     */
    string getId() const;

    /**
     * @brief Get the Adj object
     * @return std::vector<Edge *>
     */
    std::vector<Edge *> getAdj() const;

    /**
     * @brief Get the Visited object
     * @return true
     * @return false
     */
    bool isVisited() const;

    /**
     * @brief Get the Processing object
     * @return true
     * @return false
     */
    bool isProcessing() const;

    /**
     * @brief Get the Indegree object
     * @return unsigned int
     */
    unsigned int getIndegree() const;

    /**
     * @brief Get the Dist object
     * @return double
     */
    double getDist() const;

    /**
     * @brief Get the Path object
     * @return Edge *
     */
    Edge *getPath() const;

    /**
     * @brief Get the Incoming object
     * @return std::vector<Edge *>
     */
    std::vector<Edge *> getIncoming() const;

    /**
     * @brief Get the district string
     * @return string
     */
    string getDistric();

    /**
     * @brief Get the muicipality string
     * @return int
     */
    string getMunicipality();

    /**
     * @brief Get the township string
     * @return int
     */
    string getTownship();

    /**
     * @brief Get the line string
     * @return int
     */
    string getLine();

    /**
     * @brief Set the Id object
     * @param info
     */
    void setId(int info);

    /**
     * @brief Set the Visited object
     * @param visited
     */
    void setVisited(bool visited);

    /**
     * @brief Set the Processing object
     * @param processing
     */
    void setProcesssing(bool processing);

    /**
     * @brief Set the Indegree object
     * @param indegree
     */
    void setIndegree(unsigned int indegree);

    /**
     * @brief Set the Dist object
     * @param dist
     */
    void setDist(double dist);

    /**
     * @brief Set the Path object
     * @param path
     */
    void setPath(Edge *path);

    /**
     * @brief adds an  edge to the vertex
     * @param dest Destination vertex
     * @param w Edge weight
     * @param service Edge service
     */
    Edge * addEdge(Vertex *dest, double w , string service);

    /**
     * @brief removes an edge from the vertex
     * @param dest_name Destination vertex name
     * @return true Edge was removed
     * @return false Edge was not found
     */
    bool removeEdge(string dest_name);

    /**
     * @brief removes all the outgoing edges from the vertex
     */
    void removeOutgoingEdges();

    /**
     * @brief removes all the incoming edges from the vertex
     * @param dest_name Destination vertex name
     */
    void deleteEdge(Edge *edge);


    friend class MutablePriorityQueue<Vertex>;
protected:
    string id;//id ou nome
    string district;
    string municipality;
    string township;
    string line;              // identifier
    std::vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS
};

/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double w,string service);

    Vertex * getDest() const;
    string getService() const;
    double getWeight() const;
    bool isSelected() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
protected:
    Vertex * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity
    string service;
    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems
};



#endif //DA_TP1_VERTEXEDGE_H
