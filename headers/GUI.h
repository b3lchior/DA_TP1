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
private:
    Manager manager;

    void printManagement();

    void printMaxTrainStation();
};


#endif //DA_TP1_GUI_H
