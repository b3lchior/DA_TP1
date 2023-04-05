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
    cout << "╒══════════════════════════════════════════════════╤═════════════════════════════════════════════════════════════╕\n"
            "│              Stations Information                │                      Network information                    │\n"
            "╞══════════════════════════════════════════════════╪═════════════════════════════════════════════════════════════╡\n"
            "│                                                  │  -Maximum flow of trains between two stations.        [21]  │\n"
            "│                                                  │  -Which stations require the most amount of           [22]  │\n"
            "│                                                  │  trains to take full advantage of network capacity.         │\n"
            "│                                                  │  -Where management should assign larger budgets for   [23]  │\n"
            "│                                                  │  purchasing and maintenance of trains.                      │\n"
            "│                                                  │                                                             │\n"
            "╞══════════════════════════════════════════════════╡                                                             │\n"
            "│                Other operations                  │                                                             │\n"
            "╞══════════════════════════════════════════════════╡                                                             │\n"
            "│  Exit                                       [31] │                                                             │\n"
            "╘══════════════════════════════════════════════════╧═════════════════════════════════════════════════════════════╛\n"
            "                                                                                                                  \n";
    string operation;
    cin >> operation;
    cin.ignore();
    try {
        switch (stoi(operation)) {
            case 11: {

                break;
            }
            case 12:

                break;
            case 13:
                break;
            case 21:
                printMaxNumTrains();
                break;
            case 22:
                printMaxFlowNetwork();
                break;
            case 23:
                printManagement();
                break;
            case 24:
                printMaxTrainStation();
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
    int num=manager.MaxFlow(source,destination);
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

void GUI::printMaxFlowNetwork() {
    vector<MaxTrainPair> res=manager.MaxFlowFromNetwork();
    cout << "╒═══════════════════════════════════════════════════════════════════════════════╕\n";
    for(auto result : res){
        cout << "         "<<result.station1->getId()<<"------"<<result.numTrains<<"-------------->"<<result.station2->getId()<<endl<<
                "╞═══════════════════════════════════════════════════════════════════════════════╡\n";
    }
    cout<< "│  Press enter to return                                                        │\n"
           "╘═══════════════════════════════════════════════════════════════════════════════╛\n"
           "                                                                                 \n";
    cin.ignore();
}

void GUI::printManagement() {
    int type,numberOf;
    cout <<    "╒══════════════════════════════════════════════════════════╕\n"
               "│     You want the result to be Districts or Munícipes     │\n"
               "╞══════════════════════════════════════════════════════════╡\n"
               "│  Munícipes                                          [2]  │\n"
               "│  Districts                                          [1]  │\n"
               "╞══════════════════════════════════════════════════════════╡\n"
               "│  Return                                             [0]  │\n"
               "╘══════════════════════════════════════════════════════════╛\n"
               "                                               \n";
    cin>>type;
    if(type==0){
        return ;
    }
    cout <<    "╒═════════════════════════════════════════════╕\n"
               "│ This function will return the top k results │\n"
               "╞═════════════════════════════════════════════╡\n"
               "│  Write the number of results you want       │\n"
               "╞═════════════════════════════════════════════╡\n"
               "│  Return                                [0]  │\n"
               "╘═════════════════════════════════════════════╛\n"
               "                                               \n";
    cin>>numberOf;
    if(numberOf==0){
        return ;
    }
    cin.ignore();
    if(numberOf<0){
        cout << "╒═════════════════════════════════════════════════════════════════════════╕\n"
                "│  Error invalid number of results                                        │\n"
                "╞═════════════════════════════════════════════════════════════════════════╡\n"
                "│  Press enter to return                                                  │\n"
                "╘═════════════════════════════════════════════════════════════════════════╛\n"
                "                                                                                         \n";
        cin.ignore();
        return;
    }
    vector<FlowPerMunicOrDis> res;
    if(type==1){
        res=manager.TopKDistricsForWithMoreTraficPotencial(numberOf);
    }else if(type==2){
        res=manager.TopKMunicipesForWithMoreTraficPotencial(numberOf);
    }
    cout << "╒════════════════════════════════════════════════════════════════╕\n";
    for(auto result : res){
        cout << "         "<<result.DistrOrMunic<<"------"<<result.numTrains<<" trains"<<endl<<
            "╞════════════════════════════════════════════════════════════════╡\n";
    }
    cout<< "│  Press enter to return                                         │\n"
           "╘════════════════════════════════════════════════════════════════╛\n"
           "                                                          \n";
    cin.ignore();
}

void GUI::printMaxTrainStation() {

}




