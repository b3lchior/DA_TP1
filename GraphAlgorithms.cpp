//
// Created by tomas on 17/03/2023.
//

#include "GraphAlgorithms.h"
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Graph.h"
using namespace std;

int GraphAlgorithms::finMinResidualaLongPath(Vertex* s,Vertex* t){
    double f  = INT_MAX;
    for ( Vertex* v = t ; v!=s ;){
        Edge* e = v->getPath();
        if(e->getDest() == v){
            f = std::min(f,e->getWeight() - e->getFlow());
            v = e->getOrig();
        }else{
            f = std::min(f , e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}
void GraphAlgorithms::argumentFlowAlongPath(Vertex* s,Vertex* t,int f){
    for( auto v = t ; v != s ;){
        Edge* e = v->getPath();
        double flow = e->getFlow();
        if(e->getDest() == v){
            e->setFlow(flow + f);
            v =e->getOrig();
        }else{
            e->setFlow(flow-f);
            v = e->getDest();
        }
    }
    return;
}


void GraphAlgorithms::testAndVisit(std::queue<Vertex*>& q,Edge* e ,Vertex* w ,double residual){
    if( ! w->isVisited() && residual>0){
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
    return;
}
bool GraphAlgorithms::findArgumentingPath(Vertex* s,Vertex* t){
    for( Vertex*  v : getVertexSet()){
        v->setVisited(false);
    }
    s->setVisited(true);
    std::queue<Vertex*>q;
    q.push(s);
    while(!q.empty() && !t->isVisited()){
        Vertex* v = q.front();
        q.pop();
        for( Edge* e : v->getAdj()){
            testAndVisit(q,e,e->getDest(),e->getWeight() - e->getFlow());
        }
        for(Edge* e : v->getIncoming()){
            testAndVisit(q,e,e->getOrig(),e->getFlow());
        }
    }
    return t->isVisited();
}


 int GraphAlgorithms::edmondsKarp(string source, string target) {
    Vertex* s = findVertex(source);
    Vertex* t = findVertex(target);
    if(s == nullptr || t == nullptr || s == t)
        return -1;
    for(auto v : vertexSet ){
        for ( auto e : v->getAdj()){
            e->setFlow(0);
        }
    }
    while(findArgumentingPath(s,t)){
        int f = finMinResidualaLongPath(s,t);
        argumentFlowAlongPath(s,t,f);
    }
    int sum = 0;
    for(auto i : t->getIncoming()){
        sum +=i->getFlow();
    }
    //cout<<sum<<endl;
    return sum;
    // TODO
}






vector<MaxTrainPair> GraphAlgorithms::find_max_flow(){
    vector<MaxTrainPair> res;
    MaxTrainPair maxi;
    maxi.numTrains = 0;
    res.push_back(maxi);
    //pode se oiptimizar
    for(auto vertex : vertexSet){
        for(auto vertex1:vertexSet){
            if(vertex->getId() == vertex1->getId()){
                continue;
            }
            MaxTrainPair tmp;
            tmp.numTrains = edmondsKarp(vertex->getId(),vertex1->getId());;
            tmp.station1 = vertex->getId();
            tmp.station2 = vertex1->getId();
            if (res[0].numTrains < tmp.numTrains){
                res.clear();
                res.push_back(tmp);
            }
            if(res[0].numTrains == tmp.numTrains){
                res.push_back(tmp);
            }

        }
    }
    return res;
}




