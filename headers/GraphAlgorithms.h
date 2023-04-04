//
// Created by tomas on 17/03/2023.
//

#ifndef DA_TP1_GRAPHALGORITHMS_H
#define DA_TP1_GRAPHALGORITHMS_H
#include "Graph.h"


struct MaxTrainPair {
    Vertex* station1;
    Vertex* station2;
    int numTrains;
};
struct AfectedStation{
    Vertex* station;
    int numTrainsBefore;
    int numTrainsAfter;
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
    int edmondsKarp(Vertex* s,Vertex* t);
    /**
 * @brief Finds the maximum flow between all pairs of vertices in the graph.
 * @return A vector of MaxTrainPair objects representing the maximum flow between each pair of vertices.
 *
 * This function has a time complexity of O(V^3 * E^2), where V is the number of vertices and E is the number of edges in the graph.
 */
    vector<MaxTrainPair> find_max_flow();
    int find_max_number_of_trains_to_station(string stationID);
    vector<string> TopKMunicipesForWithMoreTraficPotencial(int k);
    vector<string> TopKDistricsForWithMoreTraficPotencial(int k);
    int edmondsKarpWithDijska(Vertex* s,Vertex* t,int &price);
    int edmondsKarpReducedConnectivity(Vertex* s,Vertex* t, vector<Edge*> edgesReduced);
    vector<AfectedStation> TopKStationsThatAreAffectedByReducedConectivity(int k,vector<Edge> unusedEdges);
    vector<string> getMunicipes();
    vector<string> getDistrics();
    vector<Vertex*> findVertexsInMunicipe(string municipe);
    vector<Vertex*> findVertexsInDistricts(string district);
    int find_max_number_of_trains_to_station_with_congested_network(string stationID,vector<Edge*> edgesReduced);
protected:
    int find_max_number_of_trains_to_stationAux(string stationID);
    bool findArgumentingPathWithDijka(Vertex* s,Vertex* t,int &mim);
    void testAndVisitDisjka(MutablePriorityQueue<Vertex>& q,Edge* e ,Vertex* w ,double residual, int dist_init);
    vector<Vertex*> find_vertexes_with_only_one_edge();
    bool findArgumentingPath(Vertex* s,Vertex* t);
    int finMinResidualaLongPath(Vertex* s,Vertex* t);
    void argumentFlowAlongPath(Vertex* s,Vertex* t,int f);
    void testAndVisit(std::queue<Vertex*>& q,Edge* e ,Vertex* w ,double residual);

    int finMinResidualaLongPathReducedConnectivity(Vertex* s,Vertex* t);
    void argumentFlowAlongPathReducedConnectivity(Vertex* s,Vertex* t,int f);
    void testAndVisitReducedConnectivity(std::queue<Vertex*>& q,Edge* e ,Vertex* w ,double residual);
    bool findArgumentingPathReducedConnectivity(Vertex* s,Vertex* t);


};


#endif //DA_TP1_GRAPHALGORITHMS_H
