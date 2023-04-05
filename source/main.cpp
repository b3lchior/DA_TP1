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
    //vector<EdgeSearch> edges;
    //edges.push_back({"Pinhal Novo","Grândola"});
    //edges.push_back({"Entrecampos","Pinhal Novo"});
    //cout<<manager.MaxFlowWithWithReducedConectivity("Pinhal Novo","Porto Campanhã" , edges);
    //vector<EdgeSearch> edges;
    vector<EdgeSearch> edges;
    edges.push_back({"Pinhal Novo","Grândola"});
    edges.push_back({"Entrecampos","Pinhal Novo"});
    edges.push_back({"São João do Estoril","Estoril"});
    auto vetor = manager.TopKStationsThatAreAffectedByReducedConectivity(100000,edges);
    for(auto v : vetor){

            cout<<v.station->getId()<<"    diferença :"<<v.numTrainsBefore-v.numTrainsAfter<<"       "<<v.numTrainsBefore<<"\n";

    }
    //    vector<Edge*> edges;
    //    cout<<"\n";
    //    cout<<manager.find_max_number_of_trains_to_station("Lisboa Oriente");
    //    cout<<"\n";
    //    cout<<manager.find_max_number_of_trains_to_station("Lisboa Oriente");
    //auto v = manager.TopKDistricsForWithMoreTraficPotencial(30);
    //for(auto e : v){
    //    cout<<e.DistrOrMunic<<"         "<<e.numTrains<<"\n";
    //}
    //cout<<manager.find_max_number_of_trains_to_station("Vila Real de Stº António");
    return 0;
}
