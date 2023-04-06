//
// Created by tomas on 15/03/2023.
//

#ifndef DA_TP1_MANAGER_H
#define DA_TP1_MANAGER_H
#include "Graph.h"
#include "GraphAlgorithms.h"
class Manager {
    GraphAlgorithms graph_algorithms;
public:
    void read_files();
    void ReadStations();
    void ReadRoutes();
    GraphAlgorithms getGraph();
    int MaxFlow(string source, string target);
    vector<MaxTrainPair> MaxFlowFromNetwork();
    int find_max_number_of_trains_to_station(string stationID);
    vector<FlowPerMunicOrDis> TopKDistricsForWithMoreTraficPotencial(int k);
    vector<FlowPerMunicOrDis> TopKMunicipesForWithMoreTraficPotencial(int k);
    pair<int, int> MaxFlowWithMinCost(string s, string t);
    int MaxFlowWithWithReducedConectivity(string s,string t , vector<EdgeSearch> unusableEdges);
    vector<AfectedStation> TopKStationsThatAreAffectedByReducedConectivity(int k ,vector<EdgeSearch> unusedEdges);
};


#endif //DA_TP1_MANAGER_H
