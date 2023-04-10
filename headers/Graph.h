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

    /**
     * @brief Construct a new Graph object
     */
    ~Graph();

    /**
     * @brief find a vertex in the graph with the given id, if it does not exists return nullptr
     *
     * @param stationName Vertex stationName
     * @return Vertex* vertex
     *
     * Complexity:O(V)
     */
    Vertex *findVertex(const string &id) const;

    /**
     * @brief add a vertex to the graph
     *
     * @param station Vertex station
     * @return true Vertex was added
     * @return false Vertex with that id already exists
     *
     * Complexity:O(1)
     */
    bool addVertex(string name,string district,string municipality,string township,string line);

    /**
     * @brief remove a vertex from the graph
     *
     * @param station_name name of the station to remove
     * @return true Vertex was removed
     * @return false Vertex was not found
     *
     * Complexity:O(V^2)
     */
    bool removeVertex(const string &id);

    /**
     * @brief add a edge to a vertex of the graph
     * @param source Source vertex
     * @param dest Destination Vertex
     * @param weight Edge weight
     * @param service Edge service
     * @return true Edge was added
     * @return false Source or destination vertex does not exist
     * Complexity:O(V)
     */
    bool addEdge(const string &sourc, const string &dest, double w , string service);

    /**
     * @brief add a edge from source to destination vertex and another edge the other way
     *
     * @param source Source vertex
     * @param dest Destination Vertex
     * @param weight Edge weight
     * @param service Edge service
     * @return true Edge was added
     * @return false Source or destination vertex does not exist
     * @Complexity O(V), where V is the number of vertexs.
     */
    bool addBidirectionalEdge(const string &sourc, const string &dest, double w, string service);

    /**
     * @brief find edge between two vertices
     * @param dest Destination vertex
     * @param orig Source vertex
     * @param weight Edge weight
     * @param service Edge service
     * @return Edge* Edge
     * @Complexity O(V), where V is the number of vertexs.
     */
    Edge* findEdge(Vertex * dest,Vertex *orig,double weight,string service);

    /**
     * @brief find edge between two vertices
     * @param dest Destination vertex
     * @param orig Source vertex
     * @return Edge* Edge
     * @Complexity O(V), where V is the number of vertexs.
     */
    Edge* findEdge(string orig , string dest);

    /**
     * @brief find edge by edge
     * @param e Edge
     * @return Edge* Edge
     * @Complexity O(V), where V is the number of vertexs.
     */
    Edge* findEdge(Edge e);

    /**
     * @brief get the number of vertex in the graph
     * @return int number of vertex
     */
    int getNumVertex() const;

    /**
     * @brief gets the vertex set
     * @return std::vector<Vertex*> vertex set
     */
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
