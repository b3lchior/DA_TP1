#include <iostream>
#include "../headers/Graph.h"
#include "../headers/Manager.h"
#include "../headers/GraphAlgorithms.h"
int main() {
    Manager manager = Manager();
    manager.read_files();
    Graph graph = manager.getGraph();
    //test read and write
    /*
    for(Vertex* vertex : graph.getVertexSet()){
        cout<<vertex->getId()<<endl;

        for(Edge* edge : vertex->getAdj()){
            cout<<edge->getOrig()->getId()<<"--->"<<edge->getDest()->getId()<<"   by"<<edge->getWeight()<<"   "<<edge->getService()<<endl;
        }
        cout<<"---------------------------------\n";
    }*/
    //manager.Karp("Lisboa Rossio","Porto Campanhã");
    //cout<<"\n";
    //manager.Karp("Lisboa Oriente","Porto Campanhã");
    //auto res = manager.TopKDistricsForWithMoreTraficPotencial(10);
    //for(auto r : res){
    //    cout<<r<<"\n";
    //}
    //cout<<manager.find_max_number_of_trains_to_station("Porto Campanhã");
    //manager.Karp("Lisboa Oriente","Porto Campanhã");
    //cout<<"\n--------------------------------";
    //manager.MaxFlowWithMinCost("Porto Campanhã","Lisboa Oriente");
    //cout<<"\n";

    //cout<<manager.karpWithDijska("Pinhal Novo","Lisboa Oriente");
    //cout<<"\n";
    //vector<Edge> edges;
    //edges.push_back(Edge(graph.findVertex("Pinhal Novo"),graph.findVertex("Grândola"),4,"ALFA PENDULAR"));
    //edges.push_back(Edge(graph.findVertex("Entrecampos"),graph.findVertex("Pinhal Novo"),10,"ALFA PENDULAR"));
    //cout<<manager.MaxFlowWithWithReducedConectivity("Pinhal Novo","Porto Campanhã" , edges);
    vector<EdgeSearch> edges;
    EdgeSearch tmp;
    edges.push_back({"Pinhal Novo","Grândola"});
    edges.push_back({"Entrecampos","Pinhal Novo"});
    edges.push_back({"São João do Estoril","Estoril"});
    auto vetor = manager.TopKStationsThatAreAffectedByReducedConectivity(15,edges);
    for(auto v : vetor){

            cout<<v.station->getId()<<"    diferença :"<<v.numTrainsBefore-v.numTrainsAfter<<"\n";

    }
    //    vector<Edge*> edges;
    //    cout<<"\n";
    //    cout<<manager.find_max_number_of_trains_to_station("Lisboa Oriente");
    //    cout<<"\n";
    //    cout<<manager.find_max_number_of_trains_to_station("Lisboa Oriente");
    return 0;
}
