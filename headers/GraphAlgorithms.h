//
// Created by tomas on 17/03/2023.
//

#ifndef DA_TP1_GRAPHALGORITHMS_H
#define DA_TP1_GRAPHALGORITHMS_H
#include "Graph.h"


struct MaxTrainPair {
    Vertex* station1;
    Vertex* station2;
    int numTrains;
};
struct AfectedStation{
    Vertex* station;
    int numTrainsBefore;
    int numTrainsAfter;
};
struct EdgeSearch{
    string station1;
    string station2;
};

struct FlowPerMunicOrDis {
    string DistrOrMunic;
    int numTrains;
};

class GraphAlgorithms: public Graph {
public:
    /**
 * @brief Computes the maximum flow from source to sink using the Edmonds-Karp algorithm.
 * @param source The ID of the source vertex.
 * @param target The ID of the sink vertex.
 * @return The maximum flow from source to sink.
 *
 * This function has a time complexity of O(V * E^2), where V is the number of vertices and E is the number of edges in the graph.
 */
    int edmondsKarp(Vertex* s,Vertex* t);
    /**
 * @brief Finds the maximum flow between all pairs of vertices in the graph.
 * @return A vector of MaxTrainPair objects representing the maximum flow between each pair of vertices.
 *
 * This function has a time complexity of O(V^3 * E^2), where V is the number of vertices and E is the number of edges in the graph.
 */
    vector<MaxTrainPair> find_max_flow();

    /**

    * @brief Computes the maximum number of trains that can be sent to a given station.
    * @param stationID The ID of the station.
    * @return The maximum number of trains that can be sent to the station.
    * This function uses the Edmonds-Karp algorithm to calculate the maximum number of trains that can be sent to a given station based on the current network congestion. It adds a temporary source vertex and connects it to all vertices with only one outgoing edge, which allows the algorithm to compute the maximum flow from the temporary source to the target station. This function has a time complexity of O(V * E^2), where V is the number of vertices and E is the number of edges in the graph.
*/
    int find_max_number_of_trains_to_station(string stationID);

    /**

    * @brief Finds the top k municipalities with the most traffic potential based on the number of trains that can be routed between stations within each municipality.
    * @param k The number of top municipalities to return.
    * @return A vector of FlowPerMunicOrDis structs representing the top k municipalities and their traffic potential.
    * This function iterates through all municipalities in the graph, and for each municipality it computes the maximum number of trains that can be routed between pairs of stations within the municipality using the Edmonds-Karp algorithm. The result is a vector of FlowPerMunicOrDis structs, where each struct contains the name of a municipality and the number of trains that can be routed between stations within the municipality. The vector is sorted in descending order of traffic potential, and only the top k municipalities are returned.
    * This function has a time complexity of O(M * V^2 * E^2), where M is the number of municipalities in the graph, V is the number of vertices, and E is the number of edges in the graph.
*/
    vector<FlowPerMunicOrDis> TopKMunicipesForWithMoreTraficPotencial(int k);

    /**

    * @brief Computes the top k districts with the highest traffic potential.
    * @param k The number of districts to return.
    * @return A vector of FlowPerMunicOrDis objects representing the top k districts with the highest traffic potential.
    * This function calculates the number of trains that can travel between every pair of stations within each district, and returns the k districts with the highest traffic potential. It achieves this by calling the edmondsKarpReducedConnectivity function for each pair of stations in each district, while excluding any edges that connect stations in different districts (specified in the blackList parameter). The function returns a vector of FlowPerMunicOrDis objects, each representing a district and its associated traffic potential, sorted in decreasing order of traffic potential. If k is greater than the number of districts, the function returns all districts.
*/
    vector<FlowPerMunicOrDis> TopKDistricsForWithMoreTraficPotencial(int k);

/**

    * @brief Computes the maximum flow from source to sink using the Edmonds-Karp algorithm with Dijkstra's algorithm to compute the minimum residual capacity.
    * @param s Pointer to the source vertex.
    * @param t Pointer to the sink vertex.
    * @param price Reference to an integer variable to store the minimum residual capacity of the augmenting path found.
    * @return The maximum flow from source to sink.
    * This function implements the Edmonds-Karp algorithm, which is a variation of the Ford-Fulkerson algorithm. It uses breadth-first search to find an augmenting path with the minimum residual capacity and updates the flow in the edges along that path. Dijkstra's algorithm is used to compute the minimum residual capacity of the augmenting path. The time complexity of this function is O(V^2 * E^2), where V is the number of vertices and E is the number of edges in the graph.
*/
    int edmondsKarpWithDijska(Vertex* s,Vertex* t,int &price);

/**
* @brief Applies the Edmonds-Karp algorithm with reduced connectivity to find the maximum flow from s to t.
*
* @param s The source vertex.
* @param t The target vertex.
* @param edgesReduced A vector of edges to be marked as "reduced connectivity", meaning that they will not be considered
* in the search for argumenting paths. This is useful when trying to avoid paths that cross certain edges in the graph.
* @return The maximum flow from s to t.
*/
    int edmondsKarpReducedConnectivity(Vertex* s,Vertex* t, vector<Edge*> edgesReduced);

    /**
 * @brief Finds the top K stations that are most affected by a reduced connectivity scenario caused by the removal of certain edges.
 *
 * This function computes the number of trains that can still reach each station in the graph after removing a set of edges,
 * and then returns the top K stations that have the biggest difference between the number of trains that can reach them before and after the removal.
 *
 * @param k The number of stations to return.
 * @param unusableEdges A vector containing EdgeSearch objects that represent the edges to be removed from the graph.
 * @return A vector of AfectedStation objects, sorted by the magnitude of the difference between the number of trains that can reach the station before and after removing the edges.
 */
    vector<AfectedStation> TopKStationsThatAreAffectedByReducedConectivity(int k,vector<Edge*> unusedEdges);

    /**
    * @brief returns a vector with the names of all the municipalities present in the graph.
    * @return A vector with the names of all the municipalities present in the graph.
*/
    vector<string> getMunicipes();

    /**
    * @brief returns a vector with the names of all the districts present in the graph.
    * @return A vector with the names of all the districts present in the graph.
*/
    vector<string> getDistrics();

    /**

    * @brief Retrieves a vector of all vertices in the graph that belong to a specific municipality.
    * @param municipe The name of the municipality to search for.
    * @return A vector of vertices that belong to the specified municipality.
    * This function loops through all the vertices in the graph and retrieves vertices whose municipality name matches the provided parameter. If a vertex is found that belongs to the specified municipality, it is added to the result vector. The result vector may be empty if no vertices belong to the specified municipality.
*/
    vector<Vertex*> findVertexsInMunicipe(string municipe);

    /**

    * @brief Retrieves a vector of all vertices in the graph that belong to a specific district.
    * @param district The name of the district to search for.
    * @return A vector of vertices that belong to the specified district.
    * This function loops through all the vertices in the graph and retrieves vertices whose district name matches the provided parameter. If a vertex is found that belongs to the specified district, it is added to the result vector. The result vector may be empty if no vertices belong to the specified district.
*/
    vector<Vertex*> findVertexsInDistricts(string district);

    /**

    * @brief Computes the maximum number of trains that can be sent to a specific station with a congested network.
    * @param stationID The ID of the station to calculate the maximum number of trains for.
    * @param edgesReduced A vector of edges to be removed from the graph to simulate congestion.
    * @return The maximum number of trains that can be sent to the specified station with the given network congestion.
    * This function first finds the target vertex corresponding to the provided station ID, and then creates a source vertex with a unique ID of "DELETE" to simulate the removal of edges from the graph. The function then calls the Edmonds-Karp algorithm with the reduced edge set and returns the resulting maximum flow. This function can be used to calculate the maximum number of trains that can be sent to a station with a congested network.
*/
    int find_max_number_of_trains_to_station_with_congested_network(string stationID,vector<Edge*> edgesReduced);
protected:

    /**

    * @brief Computes the maximum number of trains that can be sent to a specific station without network congestion.
    * @param stationID The ID of the station to calculate the maximum number of trains for.
    * @return The maximum number of trains that can be sent to the specified station without network congestion.
    * This function first finds the target vertex corresponding to the provided station ID, and then creates a source vertex with a unique ID of "DELETE". The function then calls the Edmonds-Karp algorithm and returns the resulting maximum flow. This function can be used to calculate the maximum number of trains that can be sent to a station without network congestion.
*/
    int find_max_number_of_trains_to_stationAux(string stationID);

    /**
 * @brief finds an augmenting path using Dijkstra's algorithm from the source vertex to the sink vertex in the graph.
 * @param s Pointer to the source vertex
 * @param t Pointer to the sink vertex
 * @param mine Reference to an integer that will store the minimum weight of the path found
 * @return true if an augmenting path was found, false otherwise
 *
 * Time Complexity: O((E+V)logV), where E is the number of edges and V is the number of vertices in the graph. This is because the function uses Dijkstra's algorithm, which has a time complexity of O((E+V)logV), to find the augmenting path.
 */
    bool findArgumentingPathWithDijka(Vertex* s,Vertex* t,int &mim);

    /**

 * @brief Tests and visits a vertex using Dijkstra's algorithm to find an augmenting path.
 * This function tests and visits a vertex in the graph using Dijkstra's algorithm to find an augmenting path from the source vertex to the sink vertex. The function updates the distance, path, and visited status of the vertex if certain conditions are met, and inserts the vertex into a mutable priority queue for further exploration.
 * @param q A mutable priority queue of vertices
 * @param e The edge used to reach the vertex being tested and visited
 * @param w The vertex being tested and visited
 * @param residual The residual capacity of the edge used to reach the vertex
 * @param dist_init The initial distance from the source vertex to the vertex being tested and visited
 * @return void
 * Time complexity: O(logV), where V is the number of vertices in the graph, due to the insertion operation on the priority queue.
*/
    void testAndVisitDisjka(MutablePriorityQueue<Vertex>& q,Edge* e ,Vertex* w ,double residual, int dist_init);

    /**

 * @brief Finds vertices in the graph with only one incoming and one outgoing edge.
 * This function iterates through all vertices in the graph and identifies those that have only one incoming and one outgoing edge. It stores these vertices in a vector and returns it.
 * @return A vector of pointers to vertices with only one incoming and one outgoing edge
 * Time complexity: O(V), where V is the number of vertices in the graph, due to the iteration over all vertices and the constant-time operations to check the size of adjacency lists.
*/
    vector<Vertex*> find_vertexes_with_only_one_edge();

/**

 * @brief Finds an augmenting path using breadth-first search from the source vertex to the sink vertex in the graph.
 * This function uses breadth-first search to find an augmenting path from the source vertex to the sink vertex in the graph. It starts by setting all vertices as unvisited and the source vertex as visited, and then uses a queue to explore neighboring vertices. The function tests each vertex and edge it encounters and visits them if certain conditions are met. If the sink vertex is visited, the function returns true; otherwise, it returns false.
 * @param s Pointer to the source vertex
 * @param t Pointer to the sink vertex
 * @return true if an augmenting path was found, false otherwise
 * Time complexity: O(E+V), where E is the number of edges and V is the number of vertices in the graph, due to the traversal of all edges and vertices in the graph in the worst case scenario.
 */
bool findArgumentingPath(Vertex* s,Vertex* t);

/**
 * @brief Finds the minimum residual capacity of an augmenting path from the source vertex to the sink vertex in the graph.
 * This function finds the minimum residual capacity of an augmenting path from the source vertex to the sink vertex in the graph using the path stored in the vertices' path attribute. It iterates backwards from the sink vertex to the source vertex, checking the residual capacities of the edges on the path and updating the minimum value as necessary. The function returns the minimum residual capacity found.
 * @param s Pointer to the source vertex
 * @param t Pointer to the sink vertex
 * @return The minimum residual capacity of an augmenting path from the source vertex to the sink vertex in the graph
 * Time complexity: O(E), where E is the number of edges in the augmenting path, since the function iterates through each edge in the path only once to calculate the minimum residual capacity.
 */
int finMinResidualaLongPath(Vertex* s,Vertex* t);

/**

 * @brief Augments the flow along the given path in the graph by the given amount.
 * This function augments the flow along the given path in the graph by the given amount f, using the path stored in the vertices' path attribute. It iterates backwards from the sink vertex to the source vertex, updating the flow along each edge on the path by adding or subtracting the given amount, depending on the direction of the edge. The function does not return anything.
 * @param s Pointer to the source vertex
 * @param t Pointer to the sink vertex
 * @param f The amount by which to augment the flow along the path
 * Time complexity: O(E), where E is the number of edges in the augmenting path, since the function iterates through each edge in the path only once to update the flow.
*/
void argumentFlowAlongPath(Vertex* s,Vertex* t,int f);

/**

 * @brief Adds the destination vertex of the given edge to the queue if it has not been visited and there is residual capacity on the edge.
 * This function adds the destination vertex of the given edge to the queue if it has not been visited and there is residual capacity on the edge. The function does not return anything.
 * @param q Reference to the queue of vertices to visit
 * @param e Pointer to the edge to test
 * @param w Pointer to the destination vertex of the edge
 * @param residual The residual capacity of the edge
 * Time complexity: O(1), since the function only performs a constant number of operations regardless of the size of the input.
*/
void testAndVisit(std::queue<Vertex*>& q,Edge* e ,Vertex* w ,double residual);

/**

 * @brief Finds the minimum residual capacity along the path from vertex s to vertex t in the graph using a modified version of Dijkstra's algorithm that considers edges with reduced connectivity.
 * @param s Pointer to the source vertex
 * @param t Pointer to the sink vertex
 * @return The minimum residual capacity along the path from vertex s to vertex t
 * Time Complexity: O((E+V)logV), where E is the number of edges and V is the number of vertices in the graph. This is because the function uses a modified version of Dijkstra's algorithm to find the minimum residual capacity, which has a time complexity of O((E+V)logV).
*/
int finMinResidualaLongPathReducedConnectivity(Vertex* s,Vertex* t);

/**

 * This function updates the flow of the edges along a path from source vertex s to target vertex t,
 * with a given flow f, while considering reduced connectivity.
 * The function starts from target vertex t, and follows the path back to source vertex s, updating the flow of the edges along the way.
 * @param s pointer to the source vertex of the path
 * @param t pointer to the target vertex of the path
 * @param f the flow to be added/subtracted along the path
 * @return void
*/
void argumentFlowAlongPathReducedConnectivity(Vertex* s,Vertex* t,int f);

/**

 * @brief Auxiliary function used in the Edmonds-Karp algorithm with reduced connectivity.
 * The function checks if a vertex is visited and if there is still residual capacity on the edge.
 * If both conditions are met, the vertex is marked as visited, its path is set to the edge and it is added to the queue.
 * @param q A reference to the queue of vertices to be visited in the algorithm.
 * @param e A pointer to the edge being tested.
 * @param w A pointer to the vertex to be checked for visitation.
 * @param residual The remaining residual capacity of the edge being tested.
*/
void testAndVisitReducedConnectivity(std::queue<Vertex*>& q,Edge* e ,Vertex* w ,double residual);

/**

@brief Finds an augmenting path in a graph with reduced connectivity using the Edmonds-Karp algorithm.
@param s The source vertex.
@param t The sink vertex.
@return true if there is an augmenting path from s to t, false otherwise.
*/
bool findArgumentingPathReducedConnectivity(Vertex* s,Vertex* t);


};


#endif //DA_TP1_GRAPHALGORITHMS_H
