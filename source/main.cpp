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
    //manager.Karp("Porto Campanhã","Lisboa Oriente");
    cout<<manager.find_max_number_of_trains_to_station("Porto Campanhã");
    return 0;
}
