//
// Created by tomas on 15/03/2023.
//

#include <fstream>
#include <sstream>
#include "Manager.h"

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
    cout << graph_algorithms.edmondsKarp(source,target);
}

