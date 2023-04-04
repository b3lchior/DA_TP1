//
// Created by pedropassos on 03-04-2023.
//

#include "../headers/GUI.h"
#include "../headers/Manager.h"

void GUI::start() {
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
    while (true) {
        if(!printUserMenu()){
            break;
        }
    }
}

bool GUI::printUserMenu() {
    cout << "╒══════════════════════════════════════════════════╤═════════════════════════════════════════════╕\n"
            "│              Flight Management                   │             Airports Information            │\n"
            "╞══════════════════════════════════════════════════╪═════════════════════════════════════════════╡\n"
            "│   Maximum number of trains that can simultaneously travel between two stations            [11] │\n"
            "│                                                                                                │\n"
            "│                                                                                                │\n"
            "│                                                                                                │\n"
            "╞══════════════════════════════════════════════════╡                                             │\n"
            "│                Other operations                  │                                             │\n"
            "╞══════════════════════════════════════════════════╡                                             │\n"
            "│  Exit                                       [31] │                                             │\n"
            "╘══════════════════════════════════════════════════╧═════════════════════════════════════════════╛\n"
            "                                                                                             \n";
    string operation;
    cin >> operation;
    cin.ignore();
    try {
        switch (stoi(operation)) {
            case 11: {
                printMaxNumTrains();
                break;
            }
            case 12:
                break;
            case 13:
                break;
            case 21:
                break;
            case 22:
                break;
            case 23:
                break;
            case 24:
                break;
            case 25:
                break;
            case 31:
                return false;
            default:
                cout << "Invalid Operation..." << endl;
        }
    }catch(std::invalid_argument){
        cout << "Invalid Operation..." << endl;
    }
    return true;
}

void GUI::printMaxNumTrains() {
    string source,destination;
    cout <<    "╒═════════════════════════════════════════════╕\n"
               "│                   Source                    │\n"
               "╞═════════════════════════════════════════════╡\n"
               "│  Write the source station name              │\n"
               "╞═════════════════════════════════════════════╡\n"
               "│  Return                                [1]  │\n"
               "╘═════════════════════════════════════════════╛\n"
               "                                               \n";
    getline(cin, source);
    if(source=="1"){
        return ;
    }
    cout <<    "╒═════════════════════════════════════════════╕\n"
               "│                 Destination                 │\n"
               "╞═════════════════════════════════════════════╡\n"
               "│  Write the target airport code              │\n"
               "╞═════════════════════════════════════════════╡\n"
               "│  Return                                [1]  │\n"
               "╘═════════════════════════════════════════════╛\n"
               "                                               \n";
    getline(cin, destination);
    if(destination=="1"){
        return ;
    }
    int num=manager.Karp(source,destination);
    if(num==-1){
        cout << "╒═══════════════════════════════════════════════════════════════════════════════════════╕\n"
                "│  Error invalid source or destination                                                  │\n"
             "╞═══════════════════════════════════════════════════════════════════════════════════════╡\n"
             "│  Press enter to return                                                                │\n"
             "╘═══════════════════════════════════════════════════════════════════════════════════════╛\n"
             "                                                                                         \n";
    }else{
        cout << "╒═══════════════════════════════════════════════════════════════════════════════════════╕\n"
             << "   "<< num << " trains can simultaneously travel between " << source << " and " << destination << endl <<
             "╞═══════════════════════════════════════════════════════════════════════════════════════╡\n"
             "│  Press enter to return                                                                │\n"
             "╘═══════════════════════════════════════════════════════════════════════════════════════╛\n"
             "                                                                                         \n";
    }
    cin.ignore();
}
