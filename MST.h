#ifndef MST_H
#define MST_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
using namespace std;

class Edge {
public:
    int source;
    int destination;
    int weight;

    Edge(int src, int dest, int w); // Konstruktor struktury Edge
};


class MST {
private:
    int numVertices;
    vector<Edge*> edges;
    vector<vector<int>> adjacencyMatrix;
    vector<vector<int>> adjacencyList;
    //vector<vector<Edge>> adjacencyList;

    // Metoda prywatna do czyszczenia danych w grafie

public:
    MST();  // Konstruktor klasy MST
    ~MST(); // Destruktor klasy MST

    void readFromFile(string filename);        // Metoda do odczytu grafu z pliku
    void generateGraph(int count, float density);   // Metoda do generowania losowego grafu

    void display(); // Metoda do wyświetlania grafu listowo i macierzowo na ekranie
    // Wyświetli listę krawędzi drzewa rozpinającego z wagami oraz sumaryczną wartość

    void PrimFull();
    void mstPrimMatrix();     // Metoda wykonująca algorytm Prima dla minimalnego drzewa rozpinającego MACIERZ
    void mstPrimList();      // Metoda wykonująca algorytm Prima dla minimalnego drzewa rozpinającego LISTA


    void KruskalFull();  // Metoda wykonująca algorytm Kruskala dla minimalnego drzewa rozpinającego
    void mstKruskalMatrix();
    void mstKruskalList();

    int find(vector<int>& parent, int vertex);                                 // Metoda pomocnicza do znajdowania korzenia zbioru dla danego wierzchołka
    void unionSet(vector<int>& parent, vector<int>& rank, int x, int y);  // Metoda pomocnicza do łączenia dwóch zbiorów w jeden
    void swapEdges(int i, int j);                                                   // Metoda pomocnicza do zamiany miejscami krawędzi w liście krawędzi
    void backMenu();

    void clearData();


};

#endif  // MST_H
