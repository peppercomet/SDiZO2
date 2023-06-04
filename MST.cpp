#include <algorithm>
#include "MST.h"

Edge::Edge(int src, int dest, int w) {
    source = src;
    destination = dest;
    weight = w;
}


void MST::clearData() {
    // Usunięcie macierzy sąsiedztwa
    adjacencyMatrix.clear();

    // Usunięcie listy sąsiedztwa
    for (auto& list : adjacencyList) {
        list.clear();
    }
    adjacencyList.clear();

    // Usunięcie krawędzi
    for (auto edge : edges) {
        delete edge;
    }
    edges.clear();

    // Zerowanie liczby wierzchołków
    numVertices = 0;
}


MST::MST() {
    numVertices = 0;
}

MST::~MST() {
    clearData();
}

//wczytujemy z pliku
void MST::readFromFile(std::string filename) {
    std::ifstream file(filename + ".txt");
    if (!file.is_open()) {
        std::cout << "Wystapil blad przy otwarciu pliku." << std::endl;
        return;
    }

    clearData();

    int numEdges;
    file >> numEdges >> numVertices;

    adjacencyMatrix.resize(numVertices, std::vector<int>(numVertices, 0));
    adjacencyList.resize(numVertices);

    for (int i = 0; i < numEdges; ++i) {
        int source, destination, weight;
        file >> source >> destination >> weight;

        // Dodajemy krawędź do listy krawędzi
        Edge* edge = new Edge(source, destination, weight);
        edges.push_back(edge);

        // Macierz sąsiedztwa
        adjacencyMatrix[source][destination] = weight;
        adjacencyMatrix[destination][source] = weight;

        // lista sąsedztwa
        adjacencyList[source].push_back(destination);
        adjacencyList[destination].push_back(source);
    }

    file.close();
}

//Generowanie grafu
void MST::generateGraph(int count, float density) {
    // Wyczyszczenie danych w grafie
    clearData();

    // Inicjalizacja liczby wierzcholkow
    numVertices = count;

    // Inicjalizacja macierzy sasiedztwa i listy sasiedztwa
    adjacencyMatrix.resize(numVertices, std::vector<int>(numVertices, 0));
    adjacencyList.resize(numVertices);

    // Obliczenie maksymalnej liczby krawedzi dla grafu pelnego
    int maxEdges = (numVertices * (numVertices - 1)) / 2;

    // Obliczenie liczby krawedzi na podstawie gestosci
    int numEdges = static_cast<int>(density / 100 * maxEdges);

    // Inicjalizacja generatora liczb losowych
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> weightDist(1, 100);

    // Generowanie krawedzi losowo
    for (int i = 0; i < numEdges; ++i) {
        // Losowanie losowego zrodla i celu krawedzi
        int src = rand() % numVertices;
        int dest = rand() % numVertices;

        // Sprawdzenie czy zrodlo i cel sa rozne oraz czy krawedz juz istnieje
        while (src == dest || adjacencyMatrix[src][dest] != 0) {
            src = rand() % numVertices;
            dest = rand() % numVertices;
        }

        // Losowanie wagi krawedzi
        int weight = weightDist(gen);

        // Dodanie krawedzi do macierzy sasiedztwa
        adjacencyMatrix[src][dest] = weight;
        adjacencyMatrix[dest][src] = weight;

        // Dodanie krawedzi do listy sasiedztwa
        adjacencyList[src].push_back(dest);
        adjacencyList[dest].push_back(src);

        // Dodanie krawedzi do listy krawedzi
        edges.push_back(new Edge(src, dest, weight));
    }
}


//wypisz
void MST::display() {
    cout << "\nStruktura macierzowa:" << endl;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nStruktura listowa:" << endl;
    for (int i = 0; i < numVertices; ++i) {
        cout << "Wierszcholek " << i << ": ";
        for (int j : adjacencyList[i]) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void MST::PrimFull(){
    mstPrimMatrix();
    mstPrimList();
}


void MST::mstPrimMatrix() {
    if (numVertices == 0) {
        std::cout << "Graf nie istnieje" << std::endl;
        return;
    }

    vector<int> parent(numVertices, -1); // Wektor przechowujący rodziców wierzchołków
    vector<int> key(numVertices, INT_MAX); // Wektor przechowujący klucze wierzchołków
    vector<bool> inMST(numVertices, false); // Wektor przechowujący informację, czy wierzchołek należy do MST

    // Wybieramy pierwszy wierzchołek jako źródło
    int src = 0;
    key[src] = 0; // Ustawiamy klucz źródła na 0

    // Pętla wykonuje się dopóki wszystkie wierzchołki nie zostaną dodane do MST
    for (int i = 0; i < numVertices - 1; ++i) {
        // Wybieramy wierzchołek o najmniejszym kluczu spośród tych, które nie należą jeszcze do MST
        int minKey = INT_MAX;
        int minIndex = -1;
        for (int v = 0; v < numVertices; ++v) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }
        }

        // Dodajemy wybrany wierzchołek do MST
        inMST[minIndex] = true;

        // Aktualizujemy klucze i rodziców sąsiednich wierzchołków
        for (int v = 0; v < numVertices; ++v) {
            if (!inMST[v] && adjacencyMatrix[minIndex][v] && adjacencyMatrix[minIndex][v] < key[v]) {
                parent[v] = minIndex;
                key[v] = adjacencyMatrix[minIndex][v];
            }
        }
    }

    // Wyświetlamy drzewo rozpinające macierzowo
    //display();

    // Wyświetlamy drzewo rozpinające listowo
   /* cout << "Minimalne drzewo rozpinajace (Prim - Macierz):" << endl;
    int totalWeight = 0;
    for (int i = 1; i < numVertices; ++i) {
        std::cout << parent[i] << " -- " << i << " (Waga: " << adjacencyMatrix[i][parent[i]] << ")" << std::endl;
        totalWeight += adjacencyMatrix[i][parent[i]];
    }
    cout << "\nSumaryczna waga: " << totalWeight << endl;
    cout << std::endl;*/
}

void MST::mstPrimList() {
    if (numVertices == 0) {
        std::cout << "Graf nie istnieje" << std::endl;
        return;
    }

    std::vector<int> parent(numVertices, -1); // Wektor do przechowywania rodziców wierzchołków
    std::vector<int> key(numVertices, INT_MAX); // Wektor do przechowywania rodziców wierzchołków
    std::vector<bool> inMST(numVertices, false); // Wektor do śledzenia, czy wierzchołek znajduje się w MST

    int src = 0; // Zaczynamy od pierwszego wierzchołka
    key[src] = 0; // Ustuwiamy klucz wierzchołka źródłowego na 0

    for (int i = 0; i < numVertices - 1; ++i) {
        int minKey = INT_MAX;
        int minIndex = -1;

        // Szukamy wierzchołek z minimalną wartością klucza wśród wierzchołków nieuwzględnionych jeszcze w MST
        for (int v = 0; v < numVertices; ++v) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }
        }

        // Dodajemy wybrany wierzchołek do MST
        inMST[minIndex] = true;

        // Aktulizujemy klucze i rodziców sąsiednich wierzchołków
        for (int v : adjacencyList[minIndex]) {
            int weight = adjacencyMatrix[minIndex][v];
            if (!inMST[v] && weight < key[v]) {
                parent[v] = minIndex;
                key[v] = weight;
            }
        }
    }

    // Wypisujemy MST
    /*std::cout << "Minimalne drzewo rozpinajace (Prim - lista):" << std::endl;
    int totalWeight = 0;
    for (int i = 1; i < numVertices; ++i) {
        std::cout << parent[i] << " -- " << i << " (Waga: " << key[i] << ")" << std::endl;
        totalWeight += key[i];
    }
    std::cout << "\nSumaryczna waga: " << totalWeight << std::endl;
    std::cout << std::endl;*/
}

void MST::KruskalFull(){

    mstKruskalMatrix();
    mstKruskalList();

}

void MST::mstKruskalMatrix() {
    if (numVertices == 0) {
        std::cout << "Grafu jeszcze nie ma." << std::endl;
        return;
    }

    // Tworzymy wektor do przechowywania rodzica każdego wierzchołka
    vector<int> parent(numVertices);

    // Tworzymy wektor do przechowywania rangi każdego wierzchołka (dla znalezienia związku)
    vector<int> rank(numVertices, 0);

    // Inicjalizacja wektor parent
    for (int i = 0; i < numVertices; ++i) {
        parent[i] = i;
    }

    // Tworzymy wektor do przechowywania krawędzi MST
    vector<Edge*> mst;
    int mstWeight = 0;

    // Przetworzamy macierz sąsiedztwa, aby wygenerować krawędzie
    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) {
            int weight = adjacencyMatrix[i][j];
            if (weight != 0) {
                Edge* edge = new Edge(i, j, weight);
                edges.push_back(edge);
            }
        }
    }

    // Sortujemy krawędzie według niemalejącej kolejności ich wag
    sort(edges.begin(), edges.end(), [](const Edge* a, const Edge* b) {
        return a->weight < b->weight;
    });

    //  Kruskal algorytm
    for (Edge* edge : edges) {
        int src = edge->source;
        int dest = edge->destination;

        // Szzukamy korzenie zbioru źródłowego i docelowego
        int rootSrc = find(parent, src);
        int rootDest = find(parent, dest);

        // Sprawdzamy, czy włączenie bieżącej krawędzi tworzy cykl
        if (rootSrc != rootDest) {
            // Dodajemy wirzcholek do MST
            mst.push_back(edge);
            mstWeight += edge->weight;

            // Polaczamy grupy
            unionSet(parent, rank, rootSrc, rootDest);
        }
    }

    // Wypisujemy
    /*cout << "Minimalne drzewo rozpinajace (Kruskal - macierz):" << endl;
    for (Edge* edge : mst) {
        cout << edge->source << " -- " << edge->destination << " (Waga: " << edge->weight << ")" << endl;
    }
    cout << "\nSumaryczna waga: " << mstWeight << endl;
    cout << endl;*/
}

void MST::mstKruskalList() {
    if (numVertices == 0) {
        cout << "Grafu jeszcze nie ma." << endl;
        return;
    }

    // Tworzymy wektor do przechowywania rodzica każdego wierzchołkax
    vector<int> parent(numVertices);

    // wektor do przechowywania rangi każdego wierzchołka (dla znalezienia związku)
    vector<int> rank(numVertices, 0);

    // Inicjalizacja wektor parent
    for (int i = 0; i < numVertices; ++i) {
        parent[i] = i;
    }

    // Wektor do przechowywania krawędzi MST
    vector<Edge*> mst;
    int mstWeight = 0;

    // Przetworzamy listę sąsiedztwa, aby wygenerować krawędzie
    for (int i = 0; i < numVertices; ++i) {
        for (const int dest : adjacencyList[i]) {
            int src = i;
            int weight = adjacencyMatrix[i][dest];
            Edge* newEdge = new Edge(src, dest, weight);
            edges.push_back(newEdge);
        }
    }

    // Sortujemy krawędzie według niemalejącej kolejności ich wag
    sort(edges.begin(), edges.end(), [](const Edge* a, const Edge* b) {
        return a->weight < b->weight;
    });

    // Kruskal algorytm
    for (Edge* edge : edges) {
        int src = edge->source;
        int dest = edge->destination;

        // Szukamy korzenie zbioru źródłowego i docelowego
        int rootSrc = find(parent, src);
        int rootDest = find(parent, dest);

        // Sprawdzamy, czy włączenie bieżącej krawędzi tworzy cykl
        if (rootSrc != rootDest) {
            // Dodajemy edge do drzewa MST
            mst.push_back(edge);
            mstWeight += edge->weight;

            // Polaczamy grupy
            unionSet(parent, rank, rootSrc, rootDest);
        }
    }

    // Wypisujemy
    /*cout << "Minimalne drzewo rozpinajace (Kruskal - lista):" << std::endl;
    for (Edge* edge : mst) {
        std::cout << edge->source << " -- " << edge->destination << " (Waga: " << edge->weight << ")" << std::endl;
    }
    cout << "\nSumaryczna waga: " << mstWeight << std::endl;
    cout << std::endl;*/
}


int MST::find(vector<int>& parent, int vertex) {
    if (parent[vertex] != vertex) {
        // Rekurencyjnie znajdź korzeń zbioru, do którego należy wierzchołek
        parent[vertex] = find(parent, parent[vertex]);
    }
    return parent[vertex];
}


void MST::unionSet(vector<int>& parent, vector<int>& rank, int x, int y) {
    int xRoot = find(parent, x); // Znajdź korzeń zbioru dla wierzchołka x
    int yRoot = find(parent, y); // Znajdź korzeń zbioru dla wierzchołka y

    if (rank[xRoot] < rank[yRoot]) {
        parent[xRoot] = yRoot; // Dołącz zbiór x do zbioru y
    }
    else if (rank[xRoot] > rank[yRoot]) {
        parent[yRoot] = xRoot; // Dołącz zbiór y do zbioru x
    }
    else {
        parent[yRoot] = xRoot; // Dołącz zbiór y do zbioru x
        rank[xRoot]++; // Zwiększ rangę zbioru x
    }
}


void MST::swapEdges(int i, int j) {
    std::swap(edges[i], edges[j]);
}

void MST::backMenu()
{
    clearData();
}

