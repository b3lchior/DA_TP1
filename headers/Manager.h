//
// Created by tomas on 15/03/2023.
//

#ifndef DA_TP1_MANAGER_H
#define DA_TP1_MANAGER_H
#include "Graph.h"
#include "GraphAlgorithms.h"
class Manager {
private:
    GraphAlgorithms graph_algorithms;
public:
    /**
     * @brief Function that calls the functions that read the files
     */
    void read_files();

    /**
     * @brief Function that reads the file stations.csv and adds the stations as vertexes to the graph
     */
    void ReadStations();

    /**
     * @brief Function that reads the file network.csv and adds the routes as edges to the graph
     */
    void ReadRoutes();

    /**
     * @brief Function that gets the network graph
     * @return network graph
     */
    GraphAlgorithms getGraph();

    /**
     * @brief Function that calculates the maximum flow between two stations
     * @param source source station
     * @param target target station
     */
    int MaxFlow(string source, string target);

    /**
     * @brief Function that calculates the maximum flow between two stations
     */
    vector<MaxTrainPair> MaxFlowFromNetwork();

    /**
     * @brief Function that calls a function to calculate the max number of trains that can be sent to a station
     * @param stationID station id
     */
    int find_max_number_of_trains_to_station(string stationID);

    /**
     * @brief Function that calls a function that calculates top k stations with more traffic potential
     * @param  k number of stations
     * @return vector with the top k stations with more traffic potential
     */
    vector<FlowPerMunicOrDis> TopKDistricsForWithMoreTraficPotencial(int k);

    /**
     * @brief Function that calls a function that calculates the top k municipalities with more traffic potential
     * @param k number of municipalities
     * @return vector with the top k municipalities with more traffic potential
     */
    vector<FlowPerMunicOrDis> TopKMunicipesForWithMoreTraficPotencial(int k);

    /**
     * @brief Function that calls a function that calculates the max flow with min cost
     * @param  s source station
     * @param  t target station
     * @return max flow with min cost
     */
    pair<int,int> MaxFlowWithMinCost(string s,string t);

    /**
     * @brief Function that calls a function that calculates the max flow with reduced connectivity
     * @param  s source station
     * @param  t target station
     * @param  unusableEdges vector with the edges that are not usable
     * @return max flow with reduced connectivity
     */
    int MaxFlowWithWithReducedConectivity(string s,string t , vector<EdgeSearch> unusableEdges);

    /**
     * @brief Function that calls a function that calculates the top k stations that are affected by reduced connectivity
     * @param  k number of stations
     * @param  unusedEdges vector with the edges that are not usable
     * @return vector with the top k stations that are affected by reduced connectivity
     */
    vector<AfectedStation> TopKStationsThatAreAffectedByReducedConectivity(int k ,vector<EdgeSearch> unusedEdges);
};


#endif //DA_TP1_MANAGER_H
