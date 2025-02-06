#ifndef PROJDA2_MENU_H
#define PROJDA2_MENU_H

#include "Funcs.h"
#include <stack>

using namespace std;

class Menu {
    Funcs f;
    int userinput;
    int RWfilesread = 0;
    int EFCGfilesread = 0;

public:
    Menu();
    void readInput (int userchoice, int max);
    void Mainmenu();
    void selectFromToyGraphs(string algorithm);
    void selectFromToyGraphsAndCustom();
    void selectFromEFCGGraphs(string algorithm);
    void selectFromRWGraphs(string algorithm);
};


#endif //PROJDA2_MENU_H
