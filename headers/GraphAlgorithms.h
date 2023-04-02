//
// Created by tomas on 17/03/2023.
//

#ifndef DA_TP1_GRAPHALGORITHMS_H
#define DA_TP1_GRAPHALGORITHMS_H
#include "Graph.h"


struct MaxTrainPair {
    string station1;
    string station2;
    int numTrains;
};


class GraphAlgorithms: public Graph {
public:
    /**
 * @brief Computes the maximum flow from source to sink using the Edmonds-Karp algorithm.
 * @param source The ID of the source vertex.
 * @param target The ID of the sink vertex.
 * @return The maximum flow from source to sink.
 *
 * This function has a time complexity of O(V * E^2), where V is the number of vertices and E is the number of edges in the graph.
 */
    int edmondsKarp(string source, string target);
    /**
 * @brief Finds the maximum flow between all pairs of vertices in the graph.
 * @return A vector of MaxTrainPair objects representing the maximum flow between each pair of vertices.
 *
 * This function has a time complexity of O(V^3 * E^2), where V is the number of vertices and E is the number of edges in the graph.
 */
    vector<MaxTrainPair> find_max_flow();
protected:
    bool findArgumentingPath(Vertex* s,Vertex* t);
    int finMinResidualaLongPath(Vertex* s,Vertex* t);
    void argumentFlowAlongPath(Vertex* s,Vertex* t,int f);
    void testAndVisit(std::queue<Vertex*>& q,Edge* e ,Vertex* w ,double residual);
};


#endif //DA_TP1_GRAPHALGORITHMS_H
