
//
// Created by zart0 on 5/28/2023.
#include <sstream>
#include <queue> // Include the queue header
#include "SPP.h"

ShortestPath::ShortestPath() {
    numVertices = 0;
}

ShortestPath::~ShortestPath() {
    clearData();
}

void ShortestPath::readFromFile(string filename) {
    std::ifstream file(filename + ".txt");
    if (file.is_open()) {
        clearData();

        int numEdges;
        int numVertices;
        file >> numEdges >> numVertices >> startVertex;

        this->numVertices = numVertices; // Update the number of vertices

        adjacencyMatrix.resize(numVertices, std::vector<int>(numVertices, 0)); // Initialize with 0

        adjacencyList.resize(numVertices);

        for (int i = 0; i < numEdges; i++) {
            int source, destination, weight;
            file >> source >> destination >> weight;

            adjacencyMatrix[source][destination] = weight;

            // Check if the edge already exists in the adjacency list
            auto it = std::find_if(adjacencyList[source].begin(), adjacencyList[source].end(), [&](const EdgeSPP& edge) {
                return edge.destination == destination;
            });

            if (it != adjacencyList[source].end()) {
                // Update the weight of the existing edge
                it->weight = weight;
            }
            else {
                // Add a new edge to the adjacency list
                EdgeSPP edge;
                edge.source = source;
                edge.destination = destination;
                edge.weight = weight;
                adjacencyList[source].push_back(edge);
            }
        }

        file.close();
    }
    else {
        std::cout << "Failed to open file: " << filename << std::endl;
    }
}



void ShortestPath::generateGraph(int count, float density) {
    clearData();

    // Generate a complete graph with count vertices
    numVertices = count;
    adjacencyMatrix.resize(count, std::vector<int>(count, 0));
    adjacencyList.resize(count);

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (i != j) {
                adjacencyMatrix[i][j] = 1;
                EdgeSPP edge;
                edge.source = i;
                edge.destination = j;
                adjacencyList[i].push_back(edge);
            }
        }
    }

    // Calculate the number of edges to remove based on density
    int numEdges = count * (count - 1);
    int numEdgesToRemove = static_cast<int>(numEdges * (1 - density));

    // Randomly remove edges
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, count - 1);

    for (int i = 0; i < numEdgesToRemove; i++) {
        int source = dis(gen);
        int destination = dis(gen);

        if (adjacencyMatrix[source][destination] == 1) {
            adjacencyMatrix[source][destination] = 0;
            adjacencyList[source].erase(std::remove_if(adjacencyList[source].begin(), adjacencyList[source].end(),
                                                       [destination](const EdgeSPP& edge) { return edge.destination == destination; }),
                                        adjacencyList[source].end());
        }
    }

    // Add edges to ensure each vertex has at least one incoming edge
    for (int i = 0; i < count; i++) {
        if (adjacencyList[i].empty()) {
            int destination = dis(gen);
            adjacencyMatrix[i][destination] = 1;
            EdgeSPP edge;
            edge.source = i;
            edge.destination = destination;
            adjacencyList[i].push_back(edge);
        }
    }
}

void ShortestPath::display() {
    std::cout << "Adjacency Matrix:" << std::endl;
    for (int i = 0; i < numVertices; i++) {
        std::cout << std::endl;
        for (int j = 0; j < numVertices; j++) {
            std::cout << "\t" << adjacencyMatrix[i][j];
        }
        std::cout << std::endl;
    }

    std::cout << "Adjacency List:" << std::endl;
    for (int i = 0; i < numVertices; i++) {
        std::cout << i ;
        for (const EdgeSPP& edge : adjacencyList[i]) {
            std::cout << " -> " << edge.destination << ":" << edge.weight;
        }
        std::cout << std::endl;
    }
}

void ShortestPath::clearData() {
    numVertices = 0;
    adjacencyMatrix.clear();
    adjacencyList.clear();
}

/*
void ShortestPath::FullDijkstra() {
    DijkstraMatix(source);
    //DijkstraList(source);
}
*/

void ShortestPath::FullDijsktra(){
    int source = 0;

    DijkstraMatrix(source);
    DijkstraList(source);

}


void ShortestPath::DijkstraMatrix(int source) {
    std::vector<int> distance(numVertices, std::numeric_limits<int>::max());
    distance[startVertex] = 0;

    std::vector<std::vector<int>> path(numVertices, std::vector<int>());

    std::vector<bool> visited(numVertices, false);

    // Define a custom comparison function for the priority queue
    auto comp = [&](int u, int v) {
        return distance[u] > distance[v];
    };

    // Priority queue using the custom comparison function
    priority_queue<int, vector<int>, decltype(comp)> pq(comp);
    pq.push(startVertex);

    while (!pq.empty()) {
        int minVertex = pq.top();
        pq.pop();

        if (visited[minVertex])
            continue;

        visited[minVertex] = true;

        for (int v = 0; v < numVertices; ++v) {
            if (!visited[v] && adjacencyMatrix[minVertex][v] != 0 &&
                distance[minVertex] != std::numeric_limits<int>::max() &&
                distance[minVertex] + adjacencyMatrix[minVertex][v] < distance[v]) {
                distance[v] = distance[minVertex] + adjacencyMatrix[minVertex][v];
                path[v] = path[minVertex];
                path[v].push_back(v);
                pq.push(v); // Push the updated vertex to the priority queue
            }
        }
    }

    /*std::cout << "Shortest distances from vertex " << startVertex << " using Dijkstra's algorithm (adjacency matrix with heap):" << std::endl;
    for (int v = 0; v < numVertices; ++v) {
        std::cout << "Vertex " << v << ": ";
        if (distance[v] == std::numeric_limits<int>::max())
            std::cout << "No path";
        else {
            std::cout << "Cost: " << distance[v] << ", Path: ";
            for (int p : path[v])
                std::cout << p << " ";
        }
        std::cout << std::endl;
    }*/
}


void ShortestPath::DijkstraList(int source) {
    std::vector<int> distance(numVertices, std::numeric_limits<int>::max());
    distance[startVertex] = 0;

    std::vector<std::vector<int>> path(numVertices, std::vector<int>());

    std::vector<bool> visited(numVertices, false);

    // Define a custom comparison function for the priority queue
    auto comp = [&](int u, int v) {
        return distance[u] > distance[v];
    };

    // Priority queue using the custom comparison function
    std::priority_queue<int, std::vector<int>, decltype(comp)> pq(comp);
    pq.push(startVertex);

    while (!pq.empty()) {
        int minVertex = pq.top();
        pq.pop();

        if (visited[minVertex])
            continue;

        visited[minVertex] = true;

        for (const auto& edge : adjacencyList[minVertex]) {
            int v = edge.destination;
            int weight = edge.weight;

            if (!visited[v] && distance[minVertex] != std::numeric_limits<int>::max() &&
                distance[minVertex] + weight < distance[v]) {
                distance[v] = distance[minVertex] + weight;
                path[v] = path[minVertex];
                path[v].push_back(v);
                pq.push(v); // Push the updated vertex to the priority queue
            }
        }
    }

    /*std::cout << "Shortest distances from vertex " << startVertex << " using Dijkstra's algorithm (adjacency list with heap):" << std::endl;
    for (int v = 0; v < numVertices; ++v) {
        std::cout << "Vertex " << v << ": ";
        if (distance[v] == std::numeric_limits<int>::max())
            std::cout << "No path";
        else {
            std::cout << "Cost: " << distance[v] << ", Path: ";
            for (int p : path[v])
                std::cout << p << " ";
        }
        std::cout << std::endl;
    }*/
}

void ShortestPath::FullBellman() {
    int source = 0;
    BellmanMatrix(source);
    BellmanList(source);

}


void ShortestPath::BellmanMatrix(int startVertex) {


    std::vector<int> distance(numVertices, std::numeric_limits<int>::max());
    distance[startVertex] = 0;

    std::vector<std::vector<int>> path(numVertices, std::vector<int>());

    for (int count = 0; count < numVertices - 1; ++count) {
        for (int v = 0; v < numVertices; ++v) {
            for (int u = 0; u < numVertices; ++u) {
                if (adjacencyMatrix[u][v] != 0 && distance[u] != std::numeric_limits<int>::max() &&
                    distance[u] + adjacencyMatrix[u][v] < distance[v]) {
                    distance[v] = distance[u] + adjacencyMatrix[u][v];
                    path[v] = path[u];
                    path[v].push_back(v);
                }
            }
        }
    }

   /* std::cout << "Shortest distances from vertex " << startVertex << " using Bellman-Ford algorithm (adjacency matrix):" << std::endl;
    for (int v = 0; v < numVertices; ++v) {
        std::cout << "Vertex " << v << ": ";
        if (distance[v] == std::numeric_limits<int>::max())
            std::cout << "No path";
        else {
            std::cout << "Cost: " << distance[v] << ", Path: ";
            for (int p : path[v])
                std::cout << p << " ";
        }
        std::cout << std::endl;
    }
*/
}


void ShortestPath::BellmanList(int startVertex){

    std::vector<int> distance(numVertices, std::numeric_limits<int>::max());
    distance[startVertex] = 0;

    std::vector<std::vector<int>> path(numVertices, std::vector<int>());

    for (int count = 0; count < numVertices - 1; ++count) {
        for (int u = 0; u < numVertices; ++u) {
            for (const auto& edge : adjacencyList[u]) {
                int v = edge.destination;
                int weight = edge.weight;

                if (distance[u] != std::numeric_limits<int>::max() &&
                    distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    path[v] = path[u];
                    path[v].push_back(v);
                }
            }
        }
    }

   /* std::cout << "Shortest distances from vertex " << startVertex << " using Bellman-Ford algorithm (adjacency list):" << std::endl;
    for (int v = 0; v < numVertices; ++v) {
        std::cout << "Vertex " << v << ": ";
        if (distance[v] == std::numeric_limits<int>::max())
            std::cout << "No path";
        else {
            std::cout << "Cost: " << distance[v] << ", Path: ";
            for (int p : path[v])
                std::cout << p << " ";
        }
        std::cout << std::endl;
    }
*/
}


//
