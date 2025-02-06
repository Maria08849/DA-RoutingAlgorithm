#ifndef PROJDA2_FUNCS_H
#define PROJDA2_FUNCS_H

#include "graph.h"

using namespace std;

class Funcs {
    Graph customGraph;
    Graph TG_shippingGraph;
    Graph TG_stadiumsGraph;
    Graph TG_tourismGraph;
    Graph RW_graph1;
    Graph RW_graph2;
    Graph RW_graph3;
    Graph EFCG_graph25;
    Graph EFCG_graph50;
    Graph EFCG_graph75;
    Graph EFCG_graph100;
    Graph EFCG_graph200;
    Graph EFCG_graph300;
    Graph EFCG_graph400;
    Graph EFCG_graph500;
    Graph EFCG_graph600;
    Graph EFCG_graph700;
    Graph EFCG_graph800;
    Graph EFCG_graph900;

public:
    Funcs();

    void readFiles(int option, int *RWfilesread, int *EFCGfilesread);

    void backtracking(int input);

    void triangular(string group, int input);

    void otherApprox(string group, int input);
};


#endif //PROJDA2_FUNCS_H
