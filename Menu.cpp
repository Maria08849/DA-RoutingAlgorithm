#include "Menu.h"

/*!
 * Checks if the option chosen in the menus is valid
 * @param min minimum option number
 * @param max maximum option number
 */
void Menu::readInput(int min, int max) {
    bool isvalid;
    do {
        cin >> userinput;
        if (cin.fail()) {
            if (cin.eof()) {
                cout << "Have a nice day!\n";
                exit(1);
            }
            else {
                isvalid = false;
                cout << "Invalid option! Choose another!\n";
                cout << "Option: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        else if (userinput > min && userinput < max) {
            isvalid = true;
        }
        else {
            isvalid = false;
            cout << "Invalid option! Choose another!\n";
            cout << "Option: ";
            cin.clear();
        }
    } while (!isvalid);
}


/*!
 * Default constructor
 */
Menu::Menu() {
    cout << endl;
    cout << "Welcome!\n";
    cout << endl;
    cout << "Set data files' path in DataFiles.h\n";
    cout << endl;
    cout << "-----------------------------------------------------------------------------\n";
    cout << "                         Select the files to be read                         \n";
    cout << "-----------------------------------------------------------------------------\n";
    cout << endl;
    cout << "1. Only toy and custom graphs (if added).\n";
    cout << "2. Toy, real world and custom graphs (if added).\n";
    cout << "3. Toy, extra fully connected, real world and custom graphs (if added).\n";
    cout << "4. Exit.\n";
    cout << endl;
    cout << "Choose an option: ";

    readInput(0, 5);

    cout << endl;
    if (userinput < 4) {
        f.readFiles(userinput, &RWfilesread, &EFCGfilesread);
        cout << endl;
        Mainmenu();
    }
    else {
        cout << "\n";
        cout << "Have a nice day!\n";
        exit(0);
    }
}


/*!
 * Corresponds to the main menu
 */
void Menu::Mainmenu() {
    cout << endl;
    cout << "-----------------------------------------------------------------------------\n";
    cout << "                                  Main Menu                                  \n";
    cout << "-----------------------------------------------------------------------------\n";
    cout << "1. Backtracking Algorithm\n";
    cout << "2. Triangular Approximation Heuristic\n";
    cout << "3. Other Heuristics\n";
    cout << "4. Exit\n";
    cout << endl;
    cout << "Choose an option: ";

    readInput(0, 5);

    switch (userinput) {
        case 1: {
            selectFromToyGraphsAndCustom();
            break;
        }
        case 2: {
            cout << endl;
            cout << "Select the file you wish to use the algorithm on\n";
            cout << endl;
            cout << "1. Custom added graph.\n";
            cout << "2. Toy graphs\n";
            cout << "3. Real-world graphs.\n";
            cout << "4. Extra fully connected graphs\n";
            cout << "5. Get back\n";
            cout << endl;
            cout << "Choose an option: ";

            readInput(0, 6);

            switch (userinput) {
                case 1:
                    if (EDGES_FILE != "") f.triangular("", 1);
                    break;
                case 2:
                    selectFromToyGraphs("triangular");
                    break;
                case 3:
                    if (RWfilesread == 1) selectFromRWGraphs("triangular");
                    break;
                case 4:
                    if (EFCGfilesread == 1) selectFromEFCGGraphs("triangular");
                    break;
                case 5:
                    break;
            }
            cout << endl;
            break;
        }
        case 3: {
            cout << endl;
            cout << "Select the file you wish to use the algorithm on\n";
            cout << endl;
            cout << "1. Custom added graph.\n";
            cout << "2. Real-world graphs.\n";
            cout << "3. Get back\n";
            cout << endl;
            cout << "Choose an option: ";

            readInput(0, 4);

            switch (userinput) {
                case 1:
                    if (EDGES_FILE != "") f.otherApprox("", 1);
                    break;
                case 2:
                    if (RWfilesread == 1) selectFromRWGraphs("other");
                    break;
                case 3:
                    break;
            }
            cout << endl;
            break;
        }
        case 4: {
            cout << "\n";
            cout << "Have a nice day!\n";
            exit(0);
        }
    }
    Mainmenu();
}


/*!
 * Allows the user to choose a file and apply an algorithm for toy graphs on it
 * @param algorithm algorithm you want apply to the file
 */
void Menu::selectFromToyGraphs(string algorithm) {
    cout << endl;
    cout << "Select the file you wish to use the algorithm on\n";
    cout << endl;
    cout << "1. Toy Graphs: Shipping file\n";
    cout << "2. Toy Graphs: Stadiums file\n";
    cout << "3. Toy Graphs: Tourism file\n";
    cout << "4. Get back\n";
    cout << endl;
    cout << "Choose an option: ";

    readInput(0, 5);

    switch (userinput) {
        case 4:
            Mainmenu();
            break;
        default:
            if (algorithm == "triangular") f.triangular("toy", userinput);
            else if (algorithm == "other") f.otherApprox("toy", userinput);
            break;
    }
    Mainmenu();
}


/*!
 * Allows the user to choose a file and apply a backtracking algorithm on toy graphs or a custom added file
 */
void Menu::selectFromToyGraphsAndCustom() {
    cout << endl;
    cout << "Select the file you wish to use the algorithm on\n";
    cout << endl;
    cout << "1. Toy Graphs: Shipping file\n";
    cout << "2. Toy Graphs: Stadiums file\n";
    cout << "3. Toy Graphs: Tourism file\n";
    cout << "4. Custom added file.\n";
    cout << "5. Get back\n";
    cout << endl;
    cout << "Choose an option: ";

    readInput(0, 6);

    switch (userinput) {
        case 5:
            Mainmenu();
            break;
        default:
            f.backtracking(userinput);
            break;
    }
    Mainmenu();
}


/*!
 * Allows the user to choose a file and apply an algorithm for real-world graphs on it
 * @param algorithm algorithm you want apply to the file
 */
void Menu::selectFromRWGraphs(string algorithm) {
    cout << endl;
    cout << "Select the file you wish to use the algorithm on\n";
    cout << endl;
    cout << "1. Real-world graphs: Graph 1.\n";
    cout << "2. Real-world graphs: Graph 2.\n";
    cout << "3. Real-world graphs: Graph 3.\n";
    cout << "4. Get back\n";
    cout << endl;
    cout << "Choose an option: ";

    readInput(0, 5);

    switch (userinput) {
        case 4:
            Mainmenu();
            break;
        default:
            if (algorithm == "triangular") f.triangular("rw", userinput);
            else if (algorithm == "other") f.otherApprox("rw", userinput);
            break;
    }
    Mainmenu();
}


/*!
 * Allows the user to choose a file and apply an algorithm for extra fully connected graphs on it
 * @param algorithm algorithm you want apply to the file
 */
void Menu::selectFromEFCGGraphs(string algorithm) {
    cout << endl;
    cout << "Select the file you wish to use the algorithm on\n";
    cout << endl;
    cout << "1.  EFCG: Edges 25.\n";
    cout << "2.  EFCG: Edges 50.\n";
    cout << "3.  EFCG: Edges 75.\n";
    cout << "4.  EFCG: Edges 100.\n";
    cout << "5.  EFCG: Edges 200.\n";
    cout << "6.  EFCG: Edges 300.\n";
    cout << "7.  EFCG: Edges 400.\n";
    cout << "8.  EFCG: Edges 500.\n";
    cout << "9.  EFCG: Edges 600.\n";
    cout << "10. EFCG: Edges 700.\n";
    cout << "11. EFCG: Edges 800.\n";
    cout << "12. EFCG: Edges 900.\n";
    cout << "13. Get back\n";
    cout << endl;
    cout << "Choose an option: ";

    readInput(0, 14);

    switch (userinput) {
        case 13:
            Mainmenu();
            break;
        default:
            if (algorithm == "triangular") f.triangular("efcg", userinput);
            else if (algorithm == "other") f.otherApprox("efcg", userinput);
            break;
    }
    Mainmenu();
}

