//
// Created by tomas on 15/03/2023.
//

#include <fstream>
#include <sstream>
#include "../headers/Manager.h"

void Manager::read_files(){
    ReadStations();
    ReadRoutes();
}
GraphAlgorithms Manager::getGraph(){
    return graph_algorithms;
}
void Manager::ReadStations() {

    ifstream file;
    file.open("../data/stations.csv");
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
    }
    string full_str;
    string name = "",district = "",municipality = "",township = "",line = "";
    getline(file,full_str,'\n');
    while(file.good()) {
        getline(file, full_str, '\n');
        stringstream ss(full_str);
        getline(ss, name, ',');
        getline(ss, district, ',');
        getline(ss, municipality, ',');
        getline(ss, township, ',');
        getline(ss, line, ',');
        graph_algorithms.addVertex(name,district,municipality,township,line);//future add hasmap
    }
}

void Manager::ReadRoutes(){

    ifstream file;
    file.open("../data/network.csv");
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
    }
    string full_str;
    string station_A="",station_B="",capacity="",service="";
    getline(file,full_str,'\n');
    while(file.good()) {
        getline(file, full_str, '\n');
        stringstream ss(full_str);
        getline(ss, station_A, ',');
        getline(ss, station_B, ',');
        getline(ss,capacity, ',');
        getline(ss, service, ',');
        graph_algorithms.addBidirectionalEdge(station_A,station_B, stoi(capacity),service);
    }
}
int Manager::MaxFlow(string source, string target){
    Vertex* s = graph_algorithms.findVertex(source);
    Vertex* t = graph_algorithms.findVertex(target);
    if( s== nullptr or t== nullptr){
        return -1;
    }
    return graph_algorithms.edmondsKarp(s,t);
}

vector<MaxTrainPair> Manager::MaxFlowFromNetwork(){
    vector<MaxTrainPair> res = graph_algorithms.find_max_flow();
    return res;
}

int Manager::find_max_number_of_trains_to_station(string stationID){
    int res = graph_algorithms.find_max_number_of_trains_to_station(stationID);
    return res;
}

vector<FlowPerMunicOrDis> Manager::TopKDistricsForWithMoreTraficPotencial(int k){
    return graph_algorithms.TopKDistricsForWithMoreTraficPotencial(k);
}
vector<FlowPerMunicOrDis> Manager::TopKMunicipesForWithMoreTraficPotencial(int k){
    return graph_algorithms.TopKMunicipesForWithMoreTraficPotencial(k);
}

pair<int,int> Manager::MaxFlowWithMinCost(string s,string t){
    int price = INT16_MAX;
    Vertex* v1=graph_algorithms.findVertex(s);
    Vertex* v2=graph_algorithms.findVertex(t);
    if( v1== nullptr or v2== nullptr){
        return make_pair(-1,-1);
    }
    int tmp = graph_algorithms.edmondsKarpWithDijska(graph_algorithms.findVertex(s),graph_algorithms.findVertex(t),price);
    return make_pair(tmp,tmp*price);
}
// é assim que se usa as funções
//vector<Edge> edges;
//edges.push_back(Edge(graph.findVertex("Porto Campanhã"),graph.findVertex("Espinho"),6,"STANDARD"));
//cout<<manager.MaxFlowWithWithReducedConectivity("Porto Campanhã","Espinho" , edges);

int Manager::MaxFlowWithWithReducedConectivity(string s,string t , vector<EdgeSearch> unusableEdges){
    vector<Edge*> edges;
    for(EdgeSearch e : unusableEdges){
        edges.push_back(graph_algorithms.findEdge(e.station1 , e.station2));
    }
    return graph_algorithms.edmondsKarpReducedConnectivity(graph_algorithms.findVertex(s),graph_algorithms.findVertex(t),edges);
}

vector<AfectedStation> Manager::TopKStationsThatAreAffectedByReducedConectivity(int k ,vector<EdgeSearch> unusedEdges){
    return graph_algorithms.TopKStationsThatAreAffectedByReducedConectivity(k,unusedEdges);
}