//
// Created by tomas on 15/03/2023.
//

#ifndef DA_TP1_MANAGER_H
#define DA_TP1_MANAGER_H
#include "Graph.h"
class Manager {
private:
    Graph graph;
public:
    void read_files();
    void ReadStations();
    void ReadRoutes();
    Graph getGraph();
};


#endif //DA_TP1_MANAGER_H
