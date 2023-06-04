//
// Created by zart0 on 5/28/2023.
//

#ifndef SDIZO2_SPP_H
#define SDIZO2_SPP_H


#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

struct EdgeSPP {
    int source;
    int destination;
    int weight;
};

class ShortestPath {
public:

    ShortestPath(); // Constructor
    ~ShortestPath(); // Destructor
    void readFromFile(string filename);
    void generateGraph(int count, float density);
    void display();

    void FullDijsktra();
    void DijkstraMatrix(int startVertex);
    void DijkstraList(int startVertex);

    void FullBellman();
    void BellmanMatrix(int startVertex);
    void BellmanList(int startVertex);


private:
    int numVertices;
    vector<std::vector<int>> adjacencyMatrix;
    vector<std::vector<EdgeSPP>> adjacencyList;
    int startVertex = 0;
    void clearData();
};

#endif  // SHORTEST_PATH_H


#endif //SDIZO2_SPP_H
