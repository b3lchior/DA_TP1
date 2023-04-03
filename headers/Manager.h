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
    void read_files();
    void ReadStations();
    void ReadRoutes();
    Graph getGraph();
    void Karp(string source, string target);
    void MaxFlowFromNetwork();
    int find_max_number_of_trains_to_station(string stationID);
    vector<string> TopKDistricsForWithMoreTraficPotencial(int k);
    vector<string> TopKMunicipesForWithMoreTraficPotencial(int k);
    int karpWithDijska(string s,string t);
    int KarpWithReducedConectivity(string s,string t , vector<Edge> unusableEdges);
};


#endif //DA_TP1_MANAGER_H
