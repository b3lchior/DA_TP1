//
// Created by tomas on 17/03/2023.
//

#include "../headers/GraphAlgorithms.h"
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <climits>

using namespace std;
int GraphAlgorithms::finMinResidualaLongPath(Vertex* s,Vertex* t){
    double f  = INT16_MAX;
    for ( Vertex* v = t ; v!=s ;){
        Edge* e = v->getPath();
        if(e->getDest() == v){
            f = std::min(f,e->getWeight() - e->getFlow());
            v = e->getOrig();
            //cout<<v->getId()<<"------>"<<e->getDest()->getId()<<"  price :"<<e->getService()<<"   weight :"<<e->getWeight()-e->getFlow()<<"\n";
        }else{
            f = std::min(f , e->getFlow());
            v = e->getDest();
        }
    }
    //cout<<"\nmin trains :"<<f<<"\n";
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
    if( ! w->isVisited() && residual > 0){
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



 int GraphAlgorithms::edmondsKarp(Vertex* s,Vertex* t) {
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

//-----------------------------------------karp using dijka


bool GraphAlgorithms::findArgumentingPathWithDijka(Vertex* s,Vertex* t,int &mine){

    for( Vertex*  v : getVertexSet()){
        v->setVisited(false);
        v->setDist(INT16_MAX);
    }
    s->setVisited(true);
    MutablePriorityQueue<Vertex> q;
    s->setDist(0);
    q.insert(s);
    while(!q.empty() && !t->isVisited()){
        Vertex* v = q.extractMin();
        for( Edge* e : v->getAdj()){
            testAndVisitDisjka(q,e,e->getDest(),e->getWeight() - e->getFlow(),v->getDist());
        }
        for(Edge* e : v->getIncoming()){
            testAndVisitDisjka(q,e,e->getOrig(),e->getFlow(),v->getDist());
        }
    }
    //cout<<"\nprice min :"<<t->getDist()<<"\n";
    if(t->getDist()<mine){
        mine = t->getDist();
    }
    if(t->getDist()>mine){
        return false;
    }

    return t->isVisited();
}



int GraphAlgorithms::edmondsKarpWithDijska(Vertex* s,Vertex* t,int &price) {
    price = INT16_MAX;
    if(s == nullptr || t == nullptr || s == t)
        return -1;
    for(auto v : vertexSet ){
        for ( auto e : v->getAdj()){
            e->setFlow(0);
        }
    }
    while(findArgumentingPathWithDijka(s,t,price)){
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



void GraphAlgorithms::testAndVisitDisjka(MutablePriorityQueue<Vertex>& q,Edge* e ,Vertex* w ,double residual , int dist_init){
    if( ! w->isVisited() && residual>0){
        w->setVisited(true);
        w->setPath(e);
        if(e->getService() == "STANDARD"){
            w->setDist(dist_init+2);
        }else{
            w->setDist(dist_init+4);
        }

        q.insert(w);
    }
    return;
}










//-----------------------------------------------------------






vector<MaxTrainPair> GraphAlgorithms::find_max_flow(){
    vector<MaxTrainPair> res;
    MaxTrainPair maxi;
    maxi.numTrains = 0;
    res.push_back(maxi);
    //pode se oiptimizar
    for(int j = 0 ; j <vertexSet.size();j++){
        for(int i =j+1; i <vertexSet.size();i++){
            MaxTrainPair tmp;
            tmp.station1 = vertexSet[i];
            tmp.station2 = vertexSet[j];
            tmp.numTrains = edmondsKarp(tmp.station1,tmp.station2);
            if (res[0].numTrains < tmp.numTrains){
                res.clear();
                res.push_back(tmp);
            }else if(res[0].numTrains == tmp.numTrains){
                res.push_back(tmp);
            }

        }
    }
    return res;
}

vector<Vertex*> GraphAlgorithms::find_vertexes_with_only_one_edge(){
    vector<Vertex*> res;
    for(Vertex* vertex : vertexSet){
        if(vertex->getAdj().size() == 1 && vertex->getIncoming().size() == 1){
            res.push_back(vertex);
        }
    }
    return res;
}

//read the data again after this function
int GraphAlgorithms::find_max_number_of_trains_to_station(string stationID){
    Vertex* t = findVertex(stationID);
    addVertex("DELETE","DELETE","DELETE","DELETE","DELETE");
    vector<Vertex*> srcs = find_vertexes_with_only_one_edge();
    for(auto v : srcs){
        //cout<<"AddEdge";
        addEdge("DELETE",v->getId(),INT16_MAX,"delete");
    }
    Vertex* s = findVertex("DELETE");
    auto result = edmondsKarp(s,t);
    removeVertex("DELETE");
    return result;
}

vector<string> GraphAlgorithms::getMunicipes(){
    vector<string> res;
    for(auto v : vertexSet){
        if(find(res.begin(),res.end(),v->getMunicipality()) == res.end() && v->getMunicipality()!=""){
            res.push_back(v->getMunicipality());
        }
    }
    return res;
}
vector<string>  GraphAlgorithms::getDistrics(){
    vector<string> res;
    for(auto v : vertexSet){
        if(find(res.begin(),res.end(),v->getDistric()) == res.end() && v->getDistric()!=""){
            res.push_back(v->getDistric());
        }
    }
    return res;
}
vector<Vertex*>  GraphAlgorithms::findVertexsInMunicipe(string municipe){
    vector<Vertex*> res;
    for(auto v : vertexSet){
        if(municipe == v->getMunicipality()){
            res.push_back(v);
        }
    }
    return res;
}
vector<Vertex*>  GraphAlgorithms::findVertexsInDistricts(string district){
    vector<Vertex*> res;
    for(auto v : vertexSet){
        if(district == v->getDistric()){
            res.push_back(v);
        }
    }
    return res;
}

bool cmpFlow(FlowPerMunicOrDis& a,
         FlowPerMunicOrDis& b)
{
    return a.numTrains > b.numTrains;
}
vector<FlowPerMunicOrDis> GraphAlgorithms::TopKMunicipesForWithMoreTraficPotencial(int k){
    vector<FlowPerMunicOrDis> res;
    vector<string> municipes = getMunicipes();
    for(string municipe : municipes){
        vector<Vertex*> stationsPerMunicipe = findVertexsInMunicipe(municipe);
        FlowPerMunicOrDis tmp;
        tmp.DistrOrMunic = municipe;
        tmp.numTrains=0;
        vector<Edge*> blackList;
        for(Vertex* v : stationsPerMunicipe){
            for(Edge* e : v->getAdj()){
                if(e->getDest()->getMunicipality()!= e->getOrig()->getMunicipality()){
                    blackList.push_back(e);
                }
            }
        }
        for(int i = 0 ; i <stationsPerMunicipe.size();i++){
            for(int j = i+1 ; j <stationsPerMunicipe.size();j++){
                tmp.numTrains+= edmondsKarpReducedConnectivity(stationsPerMunicipe[i],stationsPerMunicipe[j],blackList);
            }
        }
        res.push_back(tmp);
    }
    sort(res.begin(),res.end(),cmpFlow);
    vector<FlowPerMunicOrDis> res_ret;
    for(int i = 0 ; i < k ; i++){
        if(i>=res.size()){
            break;
        }

        res_ret.push_back(res[i]);
    }
    return res_ret;
}
vector<FlowPerMunicOrDis> GraphAlgorithms::TopKDistricsForWithMoreTraficPotencial(int k){
    vector<FlowPerMunicOrDis> res;
    vector<string> districts = getDistrics();
    for(string district : districts){
        vector<Vertex*> stationsPerDistrict = findVertexsInDistricts(district);

        vector<Edge*> blackList;
        for(Vertex* v : stationsPerDistrict){
            for(Edge* e : v->getAdj()){
                if(e->getDest()->getDistric()!= e->getOrig()->getDistric()){
                    blackList.push_back(e);
                }
            }
        }


        FlowPerMunicOrDis tmp;
        tmp.DistrOrMunic = district;
        tmp.numTrains=0;
        for(int i = 0 ; i <stationsPerDistrict.size();i++){
            for(int j = i+1 ; j <stationsPerDistrict.size();j++){
                tmp.numTrains+= edmondsKarpReducedConnectivity(stationsPerDistrict[i],stationsPerDistrict[j],blackList);
            }
        }
        res.push_back(tmp);
    }
    sort(res.begin(),res.end(),cmpFlow);
    vector<FlowPerMunicOrDis> res_ret;
    for(int i = 0 ; i < k ; i++){
        if(i>=res.size()){
            break;
        }
        res_ret.push_back(res[i]);
    }
    return res_ret;
}



//-----------------------------------------------------------------------

int GraphAlgorithms::finMinResidualaLongPathReducedConnectivity(Vertex* s,Vertex* t){
    double f  = INT16_MAX;
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
void GraphAlgorithms::argumentFlowAlongPathReducedConnectivity(Vertex* s,Vertex* t,int f){
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


void GraphAlgorithms::testAndVisitReducedConnectivity(std::queue<Vertex*>& q,Edge* e ,Vertex* w ,double residual){
    if( ! w->isVisited() && residual > 0 && !e->isSelected()){
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
    return;
}
bool GraphAlgorithms::findArgumentingPathReducedConnectivity(Vertex* s,Vertex* t){
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
            testAndVisitReducedConnectivity(q,e,e->getDest(),e->getWeight() - e->getFlow());
        }
        for(Edge* e : v->getIncoming()){
            testAndVisitReducedConnectivity(q,e,e->getOrig(),e->getFlow());
        }
    }
    return t->isVisited();
}



int GraphAlgorithms::edmondsKarpReducedConnectivity(Vertex* s,Vertex* t, vector<Edge*> edgesReduced) {
    for(Vertex* v : vertexSet){
        for(Edge* e : v->getAdj()){
            e->setSelected(false);
        }

    }
    for(Edge* e : edgesReduced){
        e->setSelected(true);
        Edge* e2 = e->getReverse();
        e2->setSelected(true);
        //for(Edge* e3 : e->getDest()->getAdj()){
        //    if(e3->isSelected() && e3->getDest() == e->getOrig()){
        //        cout<<"Ok\n";
        //    }
        //}
    }

    if(s == nullptr || t == nullptr || s == t)
        return -1;
    for(auto v : vertexSet ){
        for ( auto e : v->getAdj()){
            e->setFlow(0);
        }
    }
    while(findArgumentingPathReducedConnectivity(s,t)){
        int f = finMinResidualaLongPathReducedConnectivity(s,t);
        argumentFlowAlongPathReducedConnectivity(s,t,f);
    }
    int sum = 0;
    for(auto i : t->getIncoming()){
        sum +=i->getFlow();
    }
    //cout<<sum<<endl;
    return sum;
    // TODO
}

//-------------------------------------------congested network

int GraphAlgorithms::find_max_number_of_trains_to_stationAux(string stationID){
    Vertex* t = findVertex(stationID);
    Vertex* s = findVertex("DELETE");
    auto result = edmondsKarp(s,t);
    return result;
}

int GraphAlgorithms::find_max_number_of_trains_to_station_with_congested_network(string stationID,vector<Edge*> edgesReduced){
    Vertex* t = findVertex(stationID);
    Vertex* s = findVertex("DELETE");
    auto result = edmondsKarpReducedConnectivity(s,t,edgesReduced);
    return result;
}

bool cmpStation(AfectedStation& a,
         AfectedStation& b)
{
    return a.numTrainsBefore-a.numTrainsAfter > b.numTrainsBefore - b.numTrainsAfter;
}

vector<AfectedStation> GraphAlgorithms::TopKStationsThatAreAffectedByReducedConectivity(int k , vector<EdgeSearch> unusableEdges){
    vector<AfectedStation> res;
    vector<AfectedStation> resTmp;

    addVertex("DELETE","DELETE","DELETE","DELETE","DELETE");
    vector<Vertex*> srcs = find_vertexes_with_only_one_edge();
    for(auto v : srcs){
        addEdge("DELETE",v->getId(),INT16_MAX,"delete");
    }



    for(int i = 0 ; i<vertexSet.size();i++){
        AfectedStation tmp;
        tmp.station = vertexSet[i];
        tmp.numTrainsBefore=find_max_number_of_trains_to_stationAux(vertexSet[i]->getId());
        resTmp.push_back(tmp);
    }
    vector<Edge*> edges;
    for(EdgeSearch& e : unusableEdges){
        Edge * e1 = findEdge(e.station1,e.station2);
        edges.push_back(e1);
        edges.push_back(e1->getReverse());
        //cout<<e1->getOrig()->getId()<<"    "<<e1->getDest()->getId()<<"\n";
    }
    for(int i = 0 ; i<vertexSet.size();i++){
        resTmp[i].numTrainsAfter=find_max_number_of_trains_to_station_with_congested_network(vertexSet[i]->getId(),edges);
        //cout<<resTmp[i].numTrainsBefore<<"     "<<resTmp[i].numTrainsAfter<<"\n";
    }
    removeVertex("DELETE");
    sort(resTmp.begin(),resTmp.end(), cmpStation);
    for(int i = 0 ; i<vertexSet.size();i++){
        if(i>k){
            break;
        }
        res.push_back(resTmp[i]);
    }
    return res;
}


