#include "Menu.h"
#include "MST.h"
#include "SPP.h"
#include <iostream>
#include <string>
#include <conio.h>

MST mst_user;
ShortestPath spp_user;

void Menu::mainMenu()
{
    char choice = 'a';

    do
    {
        system("CLS");

        cout << "\t=== Main Menu ===" << endl;
        cout << "[1] MST" << endl;
        cout << "[2] Problem Najkrotszej Drogi" << endl;
        cout << "[3] Testy" << endl;
        cout << "[0] Wyjscie" << endl;

        cout << "Wybrane: ";
        choice = _getche();
        cout << endl;

        switch (choice)
        {
            case '0':	//Quit
                break;
            case '1':	//MST
                mst();
                break;
            case '2':	//SPP
                spp();
                break;
            case '3':
                test(); //test
                break;
            default:
                cout << "\nNiepoprawne dane, prosze wprowadzic poprawne\n";
        }
    } while (choice != '0');
}

char Menu::sideMenu(string name, bool problemChoice)
{
    char choice;

    cout << "\t--- " << name << " ---" << endl;

    cout << "[1] Wczytaj z pliku" << endl;
    cout << "[2] Wygeneruj graf losowo" << endl;
    cout << "[3] Wyswietl listowo i macierzowo na ekranie" << endl;

    if (problemChoice == false)
    {
        cout << "[4] Algorytm Prima" << endl;
        cout << "[5] Algorytm Kruskala" << endl;
    }
    if (problemChoice == true)
    {
        cout << "[4] Algorytm Dijkstra" << endl;
        cout << "[5] Algorytm Bellmana" << endl;
    }

    cout << "[0] Main Menu" << endl;

    cout << "Wybrane: ";
    choice = _getche();
    cout << endl;
    return choice;
}

//MST
void Menu::mst()
{
    int userInt_1, userInt_2;
    string userString_1;
    char choice;
    string filename;

    do {
        choice = sideMenu("MST", false);

        switch (choice) {
            case'0':	//Back

                mst_user.backMenu();

                break;
            case'1':	//Wczytaj z pliku

                cout << "\n\npodaj nazwe pliku do  wczytania danych: ";
                cin >> userString_1;
                cout << "\n\n";
                mst_user.readFromFile(userString_1);
                mst_user.display();

                break;
            case'2':	//Wygeneruj graf losowo

                cout << "\n\npodaj ilosc wierszcholkow: ";
                cin >> userInt_1;
                cout << "\npodaj gęstość w odsetkach: ";
                cin >> userInt_2;
                cout << "\n\n";

                mst_user.generateGraph(userInt_1, userInt_2);

                break;
            case'3':	//Wyswietl listowo i macierzowo na ekranie

                mst_user.display();

                break;
            case'4':	//Algorytm Prima

                cout << "\n\n";
                mst_user.PrimFull();

                break;
            case'5':	//Algorytm Kruskala

                cout << "\n\n";
                mst_user.KruskalFull();

                break;
        }

        if (choice == '0') break;

    } while (true);

}

//Problem Najkrotszej sciezki -- do zrobienia
void Menu::spp()
{
    string userString_2;
    char choice;
    string filename;

    do {
        choice = sideMenu("Problem najkrotszej sciezki", true);

        switch (choice) {
            case'0':
                break;
            case'1': //Wczytaj z pliku
                cout << "\n\npodaj nazwe pliku do  wczytania danych: ";
                cin >> userString_2;
                cout << "\n\n";
                spp_user.readFromFile(userString_2);
                spp_user.display();

                break;
            case'2':	//Wygeneruj graf losowo
                break;
            case'3':	//Wyswietl listowo i macierzowo na ekranie
                spp_user.display();
                break;
            case'4':	//Algorytm Dijsstra
                spp_user.FullDijsktra();

                break;
            case'5':	//Algorytm Bellmana
                spp_user.FullBellman();
                break;
        }

        if (choice == '0') break;

    } while (true);

}

void Menu::test() {

    double tempTime = 0;

//=================
//		MST
//=================
    cout << "PRIM MATRIX" << endl;
    for (int V = 50; V <= 200; V += 50) {
        for (int density : {25, 50, 75, 99}) {
            mst_user.generateGraph(V, density);

            for (int i = 0; i < 100; i++) {
                auto startTime = std::chrono::high_resolution_clock::now();

                mst_user.mstPrimMatrix();

                auto endTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

                tempTime += duration;
            }

            tempTime = tempTime / 100;
            cout << "Dla " << V << " wiersz i " << density << " krawedzi, sredni czas: " << tempTime << endl;
            tempTime = 0;
            mst_user.clearData();
        }
    }
    //wykonanie pomiarów czasu Prim Listowy
    cout << "PRIM LIST" << endl;
    for (int V = 50; V <= 200; V += 50) {
        for (int density : {25, 50, 75, 99}) {
            mst_user.generateGraph(V, density);

            for (int i = 0; i < 100; i++) {
                auto startTime = std::chrono::high_resolution_clock::now();

                mst_user.mstPrimList();

                auto endTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

                tempTime += duration;
            }

            tempTime = tempTime / 100;
            cout << tempTime << endl;
            tempTime = 0;
            mst_user.clearData();
        }
    }

    //wykonanie pomiarów czasu Kruskal Macierzowy

    cout << "KRUSKAL MATRIX" << endl;
    for (int V = 50; V <= 200; V += 50) {
        for (int density : {25, 50, 75, 99}) {
            mst_user.generateGraph(V, density);


            for (int i = 0; i < 100; i++) {
                auto startTime = std::chrono::high_resolution_clock::now();

               mst_user.mstKruskalMatrix();

                auto endTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

                tempTime += duration;
            }

            tempTime = tempTime / 100;
            cout << tempTime << endl;
            tempTime = 0;
            mst_user.clearData();
        }
    }

    //wykonanie pomiarów czasu Kruskal Listowy

    //wykonanie pomiarów czasu Kruskal Macierzowy

    cout << "KRUSKAL LIST " << endl;
    for (int V = 50; V <= 200; V += 50) {
        for (int density : {25, 50, 75, 99}) {

            mst_user.generateGraph(V, density);

            for (int i = 0; i < 100; i++) {
                auto startTime = std::chrono::high_resolution_clock::now();

                mst_user.mstKruskalList();

                auto endTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

                tempTime += duration;
            }

            tempTime = tempTime / 100;
            cout << tempTime << endl;
            tempTime = 0;
            mst_user.clearData();
        }
    }

    //=================
    //		PND
    //=================

    //wykonanie pomiarów czasu Dyjkstra Macierzowy

    cout << "SPP DIJKSTRA MATRIX " << endl;
    for (int V = 50; V <= 200; V += 50) {
        for (int density : {25, 50, 75, 99}) {

            spp_user.generateGraph(V, density);

            for (int i = 0; i < 100; i++) {
                auto startTime = std::chrono::high_resolution_clock::now();

                spp_user.DijkstraMatrix(0);

                auto endTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

                tempTime += duration;
            }

            tempTime = tempTime / 100;
            cout << tempTime << endl;
            tempTime = 0;
            mst_user.clearData();
        }
    }

    //wykonanie pomiarów czasu Dyjkstra Listowy
    cout << "SPP DIJKSTRA LIST " << endl;

    for (int V = 50; V <= 200; V += 50) {
        for (int density : {25, 50, 75, 99}) {

            spp_user.generateGraph(V, density);

            for (int i = 0; i < 100; i++) {
                auto startTime = std::chrono::high_resolution_clock::now();

                spp_user.DijkstraList(0);

                auto endTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

                tempTime += duration;
            }

            tempTime = tempTime / 100;
            cout << tempTime << endl;
            tempTime = 0;
            mst_user.clearData();
        }
    }

    //wykonanie pomiarów czasu Bellman Macierzowy

    cout << "SPP BELLMAN MATRIX " << endl;
    for (int V = 50; V <= 200; V += 50) {
        for (int density : {25, 50, 75, 99}) {

            spp_user.generateGraph(V, density);

            for (int i = 0; i < 100; i++) {
                auto startTime = std::chrono::high_resolution_clock::now();

                spp_user.BellmanMatrix(0);

                auto endTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

                tempTime += duration;
            }

            tempTime = tempTime / 100;
            cout << tempTime << endl;
            tempTime = 0;
            mst_user.clearData();
        }
    }

    //wykonanie pomiarów czasu Bellman Listowy

    cout << "SPP BELLMAN LIST " << endl;
    for (int V = 50; V <= 200; V += 50) {
        for (int density : {25, 50, 75, 99}) {
            spp_user.generateGraph(V, density);

            for (int i = 0; i < 100; i++) {
                auto startTime = std::chrono::high_resolution_clock::now();

                spp_user.BellmanList(0);

                auto endTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

                tempTime += duration;
            }

            tempTime = tempTime / 100;
            cout << tempTime << endl;
            tempTime = 0;
            mst_user.clearData();
        }
    }


}

