//
// Created by tomas on 17/03/2023.
//

#ifndef DA_TP1_GRAPHALGORITHMS_H
#define DA_TP1_GRAPHALGORITHMS_H
#include "Graph.h"

class GraphAlgorithms: public Graph {
public:
    int edmondsKarp(string source, string target);
protected:
    bool findArgumentingPath(Vertex* s,Vertex* t);
    int finMinResidualaLongPath(Vertex* s,Vertex* t);
    void argumentFlowAlongPath(Vertex* s,Vertex* t,int f);
    void testAndVisit(std::queue<Vertex*>& q,Edge* e ,Vertex* w ,double residual);
};


#endif //DA_TP1_GRAPHALGORITHMS_H
