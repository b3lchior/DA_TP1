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
Graph Manager::getGraph(){
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
void Manager::Karp(string source, string target){
    Vertex* s = graph_algorithms.findVertex(source);
    Vertex* t = graph_algorithms.findVertex(target);
    cout << graph_algorithms.edmondsKarp(s,t);
}

void Manager::MaxFlowFromNetwork(){
    vector<MaxTrainPair> res = graph_algorithms.find_max_flow();
    for(auto result : res){
        cout<<"\n"<<result.station1->getId()<<"------"<<result.numTrains<<"-------------->"<<result.station2->getId()<<"\n";
    }
}

int Manager::find_max_number_of_trains_to_station(string stationID){
    int res = graph_algorithms.find_max_number_of_trains_to_station(stationID);
    return res;
}

vector<string> Manager::TopKDistricsForWithMoreTraficPotencial(int k){
    return graph_algorithms.TopKDistricsForWithMoreTraficPotencial(k);
}
vector<string> Manager::TopKMunicipesForWithMoreTraficPotencial(int k){
    return graph_algorithms.TopKMunicipesForWithMoreTraficPotencial(k);
}

int Manager::karpWithDijska(string s,string t){
    int price = INT16_MAX;
    int tmp = graph_algorithms.edmondsKarpWithDijska(graph_algorithms.findVertex(s),graph_algorithms.findVertex(t),price);
    cout<<"Number of trains :"<<tmp<<"Price :"<<tmp*price;
    return 1;
}

int Manager::KarpWithReducedConectivity(string s,string t , vector<Edge> unusableEdges){
    vector<Edge*> edges;
    for(Edge e : unusableEdges){
        edges.push_back(graph_algorithms.findEdge(e));
    }
    return graph_algorithms.edmondsKarpReducedConnectivity(graph_algorithms.findVertex(s),graph_algorithms.findVertex(t),edges);
}
