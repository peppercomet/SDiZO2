#pragma once
#include <string>

using namespace std;

class Menu
{
public:
    void mainMenu();

private:

    char sideMenu(string name, bool problemChoice);
    void mst();
    void spp();
    void test();

};

