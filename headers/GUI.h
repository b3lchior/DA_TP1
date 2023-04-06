//
// Created by pedropassos on 03-04-2023.
//

#ifndef DA_TP1_GUI_H
#define DA_TP1_GUI_H


#include "Manager.h"

class GUI {
public:
    void start();
    bool printUserMenu();
    void printMaxNumTrains();
    void printMaxFlowNetwork();
    void printManagement();
    void printMaxTrainStation();
    void printMaxNumTrainsWithMinCost();
    void printMaxTrainsWithRedCon();
    void printMostAffectedStationsRedCon();
    vector<EdgeSearch> printEdgesGathering();
    pair<string, string> printSourceAndDest();
private:
    Manager manager;

    void printListOfMunicipes();

    void printListOfDistricts();

    void printListOfStations();

    void printListOfEdges();

    void printListOfStationsOfMandD();
};


#endif //DA_TP1_GUI_H
