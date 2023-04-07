//
// Created by pedropassos on 03-04-2023.
//

#include "../headers/GUI.h"
#include "../headers/Manager.h"
#include <iomanip>
#include <unistd.h>

void GUI::start() {
    manager.read_files();
    Graph graph = manager.getGraph();
    while (true) {
        if(!printUserMenu()){
            break;
        }
    }
}

bool GUI::printUserMenu() {
    cout << "╒══════════════════════════════════════╤═══════════════════════════════════════════════════════════════════════════════╕\n"
            "│          Network Information         │                               Service Metrics                                 │\n"
            "╞══════════════════════════════════════╪═══════════════════════════════════════════════════════════════════════════════╡\n"
            "│  List of Munícipes.            [11]  │  -Maximum flow of trains between two stations.                          [21]  │\n"
            "│                                      │  -Which pair of stations require the most amount of trains to take full [22]  │\n"
            "│  List of Districts.            [12]  │   advantage of network capacity.                                              │\n"
            "│                                      │  -Where management should assign larger budgets for purchasing and      [23]  │\n"
            "│  List of Stations of a given   [13]  │   maintenance of trains.                                                      │\n"
            "│  Munícipe or District                │  -Maximum number of trains that can simultaneously arrive at            [24]  │\n"
            "│  List of Destinations of a     [14]  │   a given station.                                                            │\n"
            "│  given station.                      │  -Calculate the maximum amount of trains that can simultaneously        [25]  │\n"
            "│                                      │   travel between two specific stations with minimum cost for the company.     │\n"
            "│  List of Stations.             [15]  │  -Calculate the maximum number of trains that can simultaneously        [26]  │\n"
            "╞══════════════════════════════════════╡   travel between two specific stations in a network of reduced connectivity.  │\n"
            "│            Other operations          │  -Report of the stations that will be most affected from a segment      [27]  │\n"
            "╞══════════════════════════════════════╡   failure.                                                                    │\n"
            "│  Exit                           [31] │                                                                               │\n"
            "╘══════════════════════════════════════╧═══════════════════════════════════════════════════════════════════════════════╛\n"
            "                                                                                                                  \n";
    string operation;
    cin >> operation;
    cin.ignore();
    try {
        switch (stoi(operation)) {
            case 11:
                printListOfMunicipes();
                break;
            case 12:
                printListOfDistricts();
                break;
            case 13:
                printListOfStationsOfMandD();
                break;
            case 14:
                printListOfEdges();
                break;
            case 15:
                printListOfStations();
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
                printMaxNumTrainsWithMinCost();
                break;
            case 26:
                printMaxTrainsWithRedCon();
                break;
            case 27:
                printMostAffectedStationsRedCon();
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
    pair<string,string> p=printSourceAndDest();
    if(p.first=="1"){
        return;
    }
    int num=manager.MaxFlow(p.first,p.second);
    if(num==-1){
        cout << "╒═══════════════════════════════════════════════════════════════════════════════════════╕\n"
                "│  Error invalid source or destination                                                  │\n"
             "╞═══════════════════════════════════════════════════════════════════════════════════════╡\n"
             "│  Press enter to return                                                                │\n"
             "╘═══════════════════════════════════════════════════════════════════════════════════════╛\n"
             "                                                                                         \n";
    }else{
        cout << "╒═══════════════════════════════════════════════════════════════════════════════════════╕\n"
             << "   "<< num << " trains can simultaneously travel between " << p.first << " and " << p.second << endl <<
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
        cout <<" With a maximum of "<<setw(3)<<result.numTrains<<" trains between :"<<endl<<
         " Station:"<<result.station1->getId()<<endl
         <<" Station:"<<result.station2->getId()<<endl<<

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
        cout <<" "<<setw(40)<<left<<result.DistrOrMunic<<left<<to_string(result.numTrains)+" trains" <<"\n"<<
            "╞════════════════════════════════════════════════════════════════╡\n";
    }
    cout<< "│  Press enter to return                                         │\n"
           "╘════════════════════════════════════════════════════════════════╛\n"
           "                                                          \n";
    cin.ignore();
}

void GUI::printMaxTrainStation() {
    string station;
    cout <<    "╒═════════════════════════════════════════════╕\n"
               "│                   Station                   │\n"
               "╞═════════════════════════════════════════════╡\n"
               "│  Write the station name                     │\n"
               "╞═════════════════════════════════════════════╡\n"
               "│  Return                                [1]  │\n"
               "╘═════════════════════════════════════════════╛\n"
               "                                               \n";
    getline(cin, station);
    if(station=="1"){
        return ;
    }
    int res=manager.find_max_number_of_trains_to_station(station);
    if(res==0){
        cout << "╒═══════════════════════════════════════════════════════════════════════════════════════╕\n"
                "│  Error invalid station                                                                │\n"
                "╞═══════════════════════════════════════════════════════════════════════════════════════╡\n"
                "│  Press enter to return                                                                │\n"
                "╘═══════════════════════════════════════════════════════════════════════════════════════╛\n"
                "                                                                                         \n";
    }else{
        cout << "╒═══════════════════════════════════════════════════════════════════════════════════════╕\n"
             << "   "<< res << " trains can simultaneously arrive at " << station << endl <<
             "╞═══════════════════════════════════════════════════════════════════════════════════════╡\n"
             "│  Press enter to return                                                                │\n"
             "╘═══════════════════════════════════════════════════════════════════════════════════════╛\n"
             "                                                                                         \n";
        cin.ignore();
    }
}

void GUI::printMaxNumTrainsWithMinCost() {
    pair<string,string> p=printSourceAndDest();
    if(p.first=="1"){
        return;
    }
    pair<int,int> res=manager.MaxFlowWithMinCost(p.first,p.second);
    if(res.first==-1){
        cout << "╒═══════════════════════════════════════════════════════════════════════════════════════╕\n"
                "│  Error invalid station                                                                │\n"
                "╞═══════════════════════════════════════════════════════════════════════════════════════╡\n"
                "│  Press enter to return                                                                │\n"
                "╘═══════════════════════════════════════════════════════════════════════════════════════╛\n"
                "                                                                                         \n";
    }else{
        cout << "╒═══════════════════════════════════════════════════════════════════════╕\n"
             << "   "<< res.first << " trains with a minimum cost of " << res.second << endl <<
                "╞═══════════════════════════════════════════════════════════════════════╡\n"
                "│  Press enter to return                                                │\n"
                "╘═══════════════════════════════════════════════════════════════════════╛\n"
                "                                                                                         \n";
    }
    cin.ignore();
}

void GUI::printMaxTrainsWithRedCon() {
    vector<EdgeSearch> edges=printEdgesGathering();
    pair<string,string> p=printSourceAndDest();
    if(p.first=="1"){
        return;
    }
    int res=manager.MaxFlowWithWithReducedConectivity(p.first,p.second,edges);
    if(res==-1){
        cout << "╒═══════════════════════════════════════════════════════════════════════════════════════╕\n"
                "│  Error invalid source or destination                                                  │\n"
                "╞═══════════════════════════════════════════════════════════════════════════════════════╡\n"
                "│  Press enter to return                                                                │\n"
                "╘═══════════════════════════════════════════════════════════════════════════════════════╛\n"
                "                                                                                         \n";
    }else if(res==-2){
        cout << "╒═══════════════════════════════════════════════════════════════════════════════════════╕\n"
                "│  Error one or more invalid edges                                                      │\n"
                "╞═══════════════════════════════════════════════════════════════════════════════════════╡\n"
                "│  Press enter to return                                                                │\n"
                "╘═══════════════════════════════════════════════════════════════════════════════════════╛\n"
                "                                                                                         \n";
    }else{
        cout << "╒═══════════════════════════════════════════════════════════════════════════════════════════════════════╕\n"
             << " With the reduced connectivity applied "<< res << " trains can simultaneously travel between " << p.first << " and " << p.second << endl <<
             "╞═══════════════════════════════════════════════════════════════════════════════════════════════════════╡\n"
             "│  Press enter to return                                                                                │\n"
             "╘═══════════════════════════════════════════════════════════════════════════════════════════════════════╛\n"
             "                                                                                         \n";
    }
    cin.ignore();
}

void GUI::printMostAffectedStationsRedCon() {
    vector<EdgeSearch> edges=printEdgesGathering();
    if(edges.empty()){
        return;
    }
    int numberOf;
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
    vector<AfectedStation> v=manager.TopKStationsThatAreAffectedByReducedConectivity(numberOf,edges);
    if(v[0].numTrainsAfter==-2){
        cout << "╒═══════════════════════════════════════════════════════════════════════════════════════╕\n"
                "│  Error one or more invalid edges                                                      │\n"
                "╞═══════════════════════════════════════════════════════════════════════════════════════╡\n"
                "│  Press enter to return                                                                │\n"
                "╘═══════════════════════════════════════════════════════════════════════════════════════╛\n"
                "                                                                                         \n";
        cin.ignore();
        return;
    }
    cout << "╒════════════════════════════════════════════════════════════════════════╕\n"
            "│  Most affected stations                                                │\n"
            "╞════════════════════════════════════════════════════════════════════════╡\n";
    for(auto a : v){
        int percentage;
        if(a.numTrainsBefore != 0){
            percentage = 100 - (a.numTrainsAfter*100)/a.numTrainsBefore;
        }else{
            percentage = 0;
        }

        cout << " Station :"<<left<<setw(40)<<setfill(' ')<<a.station->getId()<<endl
        <<" a loss in max flow of trains of :"<<setw(2)<<percentage<<"%"<<" With a diference of :"<<setw(3)<<a.numTrainsBefore - a.numTrainsAfter<<" trains."<<endl<<
           "╞═════════════════════════════════════════════════════════════════════╡\n";
    }
    cout<< "│  Press enter to return                                              │\n"
           "╘═════════════════════════════════════════════════════════════════════╛\n"
           "                                                          \n";
    cin.ignore();
}

vector<EdgeSearch> GUI::printEdgesGathering(){
    string source,destination;
    vector<EdgeSearch> edges;
    while(true) {
        GraphAlgorithms graphAlgorithms = manager.getGraph();
        while (true){
            cout << "╒═══════════════════════════════════════════════════════════╕\n"
                    "│   Add an edge to the ones you dont want the graph to use  │\n"
                    "╞═══════════════════════════════════════════════════════════╡\n"
                    "│  Write the source station name                            │\n"
                    "╞═══════════════════════════════════════════════════════════╡\n"
                    "│  Return                                              [1]  │\n"
                    "╘═══════════════════════════════════════════════════════════╛\n"
                    "                                               \n";
            getline(cin, source);
            if (source == "1") {
                return {};
            }
            if(graphAlgorithms.findVertex(source)!= nullptr){
                break;
            }else{
                cout << "╒═══════════════════════════════════════════════════════════════════════════════════════╕\n"
                        "│  Error Station not found type again                                                   │\n"
                        "╘═══════════════════════════════════════════════════════════════════════════════════════╛\n";
            }
        } ;
        while (true){
            cout << "╒═══════════════════════════════════════════════════════════╕\n"
                    "│   Add an edge to the ones you dont want the graph to use  │\n"
                    "╞═══════════════════════════════════════════════════════════╡\n"
                    "│  Write the destination station name                       │\n"
                    "╞═══════════════════════════════════════════════════════════╡\n"
                    "│  Return                                              [1]  │\n"
                    "╘═══════════════════════════════════════════════════════════╛\n"
                    "                                               \n";
            getline(cin, destination);
            if (destination == "1") {
                return {};
            }
            if(graphAlgorithms.findVertex(destination)!= nullptr){
                break;
            }else{
                cout << "╒═══════════════════════════════════════════════════════════════════════════════════════╕\n"
                        "│  Error Station not found type again                                                   │\n"
                        "╘═══════════════════════════════════════════════════════════════════════════════════════╛\n";
            }
        }
        if(graphAlgorithms.findEdge(source,destination)!= nullptr){
            edges.push_back({source,destination});
        }else{
            cout << "╒═══════════════════════════════════════════════════════════════════════════════════════╕\n"
                    "│  Error Line not found type again                                                      │\n"
                    "╘═══════════════════════════════════════════════════════════════════════════════════════╛\n";
            continue;
        }
        cout << "╒════════════════════════════════════════╕\n"
                "│  Add one more edge?                    │\n"
                "╞════════════════════════════════════════╡\n"
                "│  Yes                              [2]  │\n"
                "╞════════════════════════════════════════╡\n"
                "│  No                               [1]  │\n"
                "╘════════════════════════════════════════╛\n"
                "                                               \n";
        int a;
        cin >> a;
        cin.ignore();
        if(a==1){
            break;
        }
    }
    return edges;
}

pair<string,string> GUI::printSourceAndDest(){
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
        return {"1","1"};
    }
    cout <<    "╒═════════════════════════════════════════════╕\n"
               "│                 Destination                 │\n"
               "╞═════════════════════════════════════════════╡\n"
               "│  Write the destination station name         │\n"
               "╞═════════════════════════════════════════════╡\n"
               "│  Return                                [1]  │\n"
               "╘═════════════════════════════════════════════╛\n"
               "                                               \n";
    getline(cin, destination);
    if(destination=="1"){
        return {"1","1"};
    }
    return {source,destination};
}

void GUI::printListOfMunicipes() {
    vector<string> v=manager.getGraph().getMunicipes();
    cout << "╒════════════════════════════════════════════╕\n"
            "│                 Munícipes                  │\n"
            "╞════════════════════════════════════════════╡\n";
    for(auto a : v){
        cout << "   "<<a<<endl<<
            "╞════════════════════════════════════════════╡\n";
    }
    cout<<  "│  Press enter to return                     │\n"
            "╘════════════════════════════════════════════╛\n"
           "                                                          \n";
    cin.ignore();
}

void GUI::printListOfDistricts() {
    vector<string> v=manager.getGraph().getDistrics();
    cout << "╒════════════════════════════════════════════╕\n"
            "│                 Districts                  │\n"
            "╞════════════════════════════════════════════╡\n";
    for(auto a : v){
        cout << "   "<<a<<endl<<
             "╞════════════════════════════════════════════╡\n";
    }
    cout<<  "│  Press enter to return                     │\n"
            "╘════════════════════════════════════════════╛\n"
            "                                                          \n";
    cin.ignore();
}

void GUI::printListOfStationsOfMandD() {
    int type;
    string name;
    cout <<    "╒══════════════════════════════════════════════════════════╕\n"
               "│      You want the station of a District or Munícipe      │\n"
               "╞══════════════════════════════════════════════════════════╡\n"
               "│  Munícipe                                           [2]  │\n"
               "│  District                                           [1]  │\n"
               "╞══════════════════════════════════════════════════════════╡\n"
               "│  Return                                             [0]  │\n"
               "╘══════════════════════════════════════════════════════════╛\n"
               "                                               \n";
    cin>>type;
    if(type==0){
        return ;
    }
    cin.ignore();
    vector<Vertex*> v;
    if(type==1){
        cout <<    "╒═════════════════════════════════════════════╕\n"
                   "│                  District                   │\n"
                   "╞═════════════════════════════════════════════╡\n"
                   "│  Write the district name                    │\n"
                   "╞═════════════════════════════════════════════╡\n"
                   "│  Return                                [1]  │\n"
                   "╘═════════════════════════════════════════════╛\n"
                   "                                               \n";
        getline(cin,name);
        v=manager.getGraph().findVertexsInDistricts(name);
    }else if(type==2){
        cout <<    "╒═════════════════════════════════════════════╕\n"
                   "│                  Munícipe                   │\n"
                   "╞═════════════════════════════════════════════╡\n"
                   "│  Write the munícipe name                    │\n"
                   "╞═════════════════════════════════════════════╡\n"
                   "│  Return                                [1]  │\n"
                   "╘═════════════════════════════════════════════╛\n"
                   "                                               \n";
        getline(cin,name);
        v=manager.getGraph().findVertexsInMunicipe(name);
    }else{
        cout << "Error select one of the valid options!";
        printListOfStationsOfMandD();
        return;
    }
    cout << "╒════════════════════════════════════════════╕\n"
            "            Stations - "<< name<< endl<<
            "╞════════════════════════════════════════════╡\n";
    for(auto a : v){
        cout << "   "<<a->getId()<<endl<<
             "╞════════════════════════════════════════════╡\n";
    }
    cout<<  "│  Press enter to return                     │\n"
            "╘════════════════════════════════════════════╛\n"
            "                                                          \n";
    cin.ignore();
}

void GUI::printListOfStations() {
    vector<Vertex*> v=manager.getGraph().getVertexSet();
    cout << "╒════════════════════════════════════════════╕\n"
            "│                  Stations                  │\n"
            "╞════════════════════════════════════════════╡\n";
    for(auto a : v){
        cout << "   "<<a->getId()<<endl<<
             "╞════════════════════════════════════════════╡\n";
    }
    cout<<  "│  Press enter to return                     │\n"
            "╘════════════════════════════════════════════╛\n"
            "                                                          \n";
    cin.ignore();
}

void GUI::printListOfEdges() {
    string station;
    cout <<    "╒═════════════════════════════════════════════╕\n"
               "│                   Station                   │\n"
               "╞═════════════════════════════════════════════╡\n"
               "│  Write the station code                     │\n"
               "╞═════════════════════════════════════════════╡\n"
               "│  Return                                [1]  │\n"
               "╘═════════════════════════════════════════════╛\n"
               "                                               \n";
    getline(cin, station);
    if(station=="1"){
        return;
    }
    vector<Edge *> v=manager.getGraph().findVertex(station)->getAdj();
    cout << "╒════════════════════════════════════════════╕\n"
            "         Destinations - "<< station <<endl<<
            "╞════════════════════════════════════════════╡\n";
    for(auto e : v){
        cout << "   "<<station<<" ---> "<<e->getDest()->getId()<<endl<<
        "╞════════════════════════════════════════════╡\n";
    }
    cout<<  "│  Press enter to return                     │\n"
            "╘════════════════════════════════════════════╛\n"
            "                                                          \n";
    cin.ignore();
}






