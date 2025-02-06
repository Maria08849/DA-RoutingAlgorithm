#include "Funcs.h"

/*!
 * Default constructor, sets graphs
 */
Funcs::Funcs(): customGraph(Graph(false)), TG_shippingGraph(Graph(false)), TG_stadiumsGraph(Graph(false)),
                TG_tourismGraph(Graph(false)), RW_graph1(Graph(false)), RW_graph2(Graph(false)), RW_graph3(Graph(false)),
                EFCG_graph25(Graph(false)), EFCG_graph50(Graph(false)), EFCG_graph75(Graph(false)), EFCG_graph100(Graph(false)),
                EFCG_graph200(Graph(false)), EFCG_graph300(Graph(false)), EFCG_graph400(Graph(false)), EFCG_graph500(Graph(false)),
                EFCG_graph600(Graph(false)), EFCG_graph700(Graph(false)), EFCG_graph800(Graph(false)), EFCG_graph900(Graph(false)) {}


/*!
 * Reads the dataset,
 * always reads custom added files in DataFiles.h if they are added (if the edges file path != "")
 * @param option defines which additional files are read: 1 means only toy graphs will be read, 2 means toy and real world graphs will be read, and 3 means toy, extra fully connected and real world graphs will be read
 */
void Funcs::readFiles(int option, int *RWfilesread, int *EFCGfilesread) {
    cout << "Reading files...\n" << endl;
    if (EDGES_FILE != "") {
        if (NODES_FILE != "") customGraph.readFiles(NODES_FILE, EDGES_FILE);
        else customGraph.readEdgesFile(EDGES_FILE);
    }
    switch (option) {
        case 1:
            TG_shippingGraph.readEdgesFile(TG_SHIPPING_FILE);
            TG_stadiumsGraph.readEdgesFile(TG_STADIUMS_FILE);
            TG_tourismGraph.readEdgesFile(TG_TOURISM_FILE);
            break;
        case 2:
            *RWfilesread = 1;
            TG_shippingGraph.readEdgesFile(TG_SHIPPING_FILE);
            TG_stadiumsGraph.readEdgesFile(TG_STADIUMS_FILE);
            TG_tourismGraph.readEdgesFile(TG_TOURISM_FILE);
            RW_graph1.readFiles(RW_G1_NODES, RW_G1_EDGES);
            RW_graph2.readFiles(RW_G2_NODES, RW_G2_EDGES);
            RW_graph3.readFiles(RW_G3_NODES, RW_G3_EDGES);
            break;
        case 3:
            *RWfilesread = 1;
            *EFCGfilesread = 1;
            TG_shippingGraph.readEdgesFile(TG_SHIPPING_FILE);
            TG_stadiumsGraph.readEdgesFile(TG_STADIUMS_FILE);
            TG_tourismGraph.readEdgesFile(TG_TOURISM_FILE);
            RW_graph1.readFiles(RW_G1_NODES, RW_G1_EDGES);
            RW_graph2.readFiles(RW_G2_NODES, RW_G2_EDGES);
            RW_graph3.readFiles(RW_G3_NODES, RW_G3_EDGES);
            EFCG_graph25.readEdgesFile(EFCG_EDGES_25);
            EFCG_graph50.readEdgesFile(EFCG_EDGES_50);
            EFCG_graph75.readEdgesFile(EFCG_EDGES_75);
            EFCG_graph100.readEdgesFile(EFCG_EDGES_100);
            EFCG_graph200.readEdgesFile(EFCG_EDGES_200);
            EFCG_graph300.readEdgesFile(EFCG_EDGES_300);
            EFCG_graph400.readEdgesFile(EFCG_EDGES_400);
            EFCG_graph500.readEdgesFile(EFCG_EDGES_500);
            EFCG_graph600.readEdgesFile(EFCG_EDGES_600);
            EFCG_graph700.readEdgesFile(EFCG_EDGES_700);
            EFCG_graph800.readEdgesFile(EFCG_EDGES_800);
            EFCG_graph900.readEdgesFile(EFCG_EDGES_900);
            break;
        default:
            exit(1);
    }
}


/*!
 * Calls the backtracking algorithm and prints the output in the console
 * O(2^V)
 * @param input graph in which we want to apply the backtracking
 */
void Funcs::backtracking(int input) {
    pair<vector<Vertex *>, double> r;
    switch (input) {
        case 1:
            r = TG_shippingGraph.backtracking();
            cout << "Path taken: ";

            for (auto v : r.first) {
                if (v == r.first.back()) {
                    cout << v->getId() << endl;
                }
                else cout << v->getId() << " -> ";
            }
            cout << "Total distance: " << r.second << endl;
            break;
        case 2:
            r = TG_stadiumsGraph.backtracking();
            cout << "Path taken: ";

            for (auto v : r.first) {
                if (v == r.first.back()) {
                    cout << v->getId() << endl;
                }
                else cout << v->getId() << " -> ";
            }
            cout << "Total distance: " << r.second << endl;
            break;
        case 3:
            r = TG_tourismGraph.backtracking();
            cout << "Path taken: ";

            for (auto v : r.first) {
                if (v == r.first.back()) {
                    cout << v->getId() << endl;
                }
                else cout << v->getId() << " -> ";
            }
            cout << "Total distance: " << r.second << endl;
            break;
        case 4:
            if (EDGES_FILE == "") break;
            r = customGraph.backtracking();
            cout << "Path taken: ";

            for (auto v : r.first) {
                if (v == r.first.back()) {
                    cout << v->getId() << endl;
                }
                else cout << v->getId() << " -> ";
            }
            cout << "Total distance: " << r.second << endl;
            break;
    }
}


/*!
 * Calls the triangular approximation algorithm and prints the output in the console
 * O((V + E) log V)
 * @param group group of graphs to perform the algorithm
 * @param input graph in which we want to perform the algorithm
 */
void Funcs::triangular(string group, int input) {
    pair<vector<pair<Vertex *, Vertex *>>, double> r;
    if (group == "") {
        r = customGraph.triangularApprox();
        cout << "MST:" << endl;
        for (auto &x : r.first) {
            cout << x.first->getId() << " -> " << x.second->getId() << endl;
        }
        cout << "Total distance: " << r.second << endl;
    }
    else if (group == "toy") {
        switch (input) {
            case 1:
                r = TG_shippingGraph.triangularApprox();
                cout << "MST:" << endl;
                for (auto &x : r.first) {
                    cout << x.first->getId() << " -> " << x.second->getId() << endl;
                }
                cout << "Total distance: " << r.second << endl;
                break;
            case 2:
                r = TG_stadiumsGraph.triangularApprox();
                cout << "MST:" << endl;
                for (auto &x : r.first) {
                    cout << x.first->getId() << " -> " << x.second->getId() << endl;
                }
                cout << "Total distance: " << r.second << endl;
                break;
            case 3:
                r = TG_tourismGraph.triangularApprox();
                cout << "MST:" << endl;
                for (auto &x : r.first) {
                    cout << x.first->getId() << " -> " << x.second->getId() << endl;
                }
                cout << "Total distance: " << r.second << endl;
                break;
            default:
                break;
        }
    }
    else if (group == "rw") {
        switch (input) {
            case 1:
                r = RW_graph1.triangularApprox();
                cout << "MST:" << endl;
                for (auto &x : r.first) {
                    cout << x.first->getId() << " -> " << x.second->getId() << endl;
                }
                cout << "Total distance: " << r.second << endl;
                break;
            case 2:
                r = RW_graph2.triangularApprox();
                cout << "MST:" << endl;
                for (auto &x : r.first) {
                    cout << x.first->getId() << " -> " << x.second->getId() << endl;
                }
                cout << "Total distance: " << r.second << endl;
                break;
            case 3:
                r = RW_graph3.triangularApprox();
                cout << "MST:" << endl;
                for (auto &x : r.first) {
                    cout << x.first->getId() << " -> " << x.second->getId() << endl;
                }
                cout << "Total distance: " << r.second << endl;
                break;
            default:
                break;
        }
    }
    else if (group == "efcg") {
        switch (input) {
            case 1:
                r = EFCG_graph25.triangularApprox();
                cout << "MST:" << endl;
                for (auto &x : r.first) {
                    cout << x.first->getId() << " -> " << x.second->getId() << endl;
                }
                cout << "Total distance: " << r.second << endl;
                break;
            case 2:
                r = EFCG_graph50.triangularApprox();
                cout << "MST:" << endl;
                for (auto &x : r.first) {
                    cout << x.first->getId() << " -> " << x.second->getId() << endl;
                }
                cout << "Total distance: " << r.second << endl;
                break;
            case 3:
                r = EFCG_graph75.triangularApprox();
                cout << "MST:" << endl;
                for (auto &x : r.first) {
                    cout << x.first->getId() << " -> " << x.second->getId() << endl;
                }
                cout << "Total distance: " << r.second << endl;
                break;
            case 4:
                r = EFCG_graph100.triangularApprox();
                cout << "MST:" << endl;
                for (auto &x : r.first) {
                    cout << x.first->getId() << " -> " << x.second->getId() << endl;
                }
                cout << "Total distance: " << r.second << endl;
                break;
            case 5:
                r = EFCG_graph200.triangularApprox();
                cout << "MST:" << endl;
                for (auto &x : r.first) {
                    cout << x.first->getId() << " -> " << x.second->getId() << endl;
                }
                cout << "Total distance: " << r.second << endl;
                break;
            case 6:
                r = EFCG_graph300.triangularApprox();
                cout << "MST:" << endl;
                for (auto &x : r.first) {
                    cout << x.first->getId() << " -> " << x.second->getId() << endl;
                }
                cout << "Total distance: " << r.second << endl;
                break;
            case 7:
                r = EFCG_graph400.triangularApprox();
                cout << "MST:" << endl;
                for (auto &x : r.first) {
                    cout << x.first->getId() << " -> " << x.second->getId() << endl;
                }
                cout << "Total distance: " << r.second << endl;
                break;
            case 8:
                r = EFCG_graph500.triangularApprox();
                cout << "MST:" << endl;
                for (auto &x : r.first) {
                    cout << x.first->getId() << " -> " << x.second->getId() << endl;
                }
                cout << "Total distance: " << r.second << endl;
                break;
            case 9:
                r = EFCG_graph600.triangularApprox();
                cout << "MST:" << endl;
                for (auto &x : r.first) {
                    cout << x.first->getId() << " -> " << x.second->getId() << endl;
                }
                cout << "Total distance: " << r.second << endl;
                break;
            case 10:
                r = EFCG_graph700.triangularApprox();
                cout << "MST:" << endl;
                for (auto &x : r.first) {
                    cout << x.first->getId() << " -> " << x.second->getId() << endl;
                }
                cout << "Total distance: " << r.second << endl;
                break;
            case 11:
                r = EFCG_graph800.triangularApprox();
                cout << "MST:" << endl;
                for (auto &x : r.first) {
                    cout << x.first->getId() << " -> " << x.second->getId() << endl;
                }
                cout << "Total distance: " << r.second << endl;
                break;
            case 12:
                r = EFCG_graph900.triangularApprox();
                cout << "MST:" << endl;
                for (auto &x : r.first) {
                    cout << x.first->getId() << " -> " << x.second->getId() << endl;
                }
                cout << "Total distance: " << r.second << endl;
                break;
            default:
                break;
        }
    }
}


/*!
 * Calls a greedy approach to an approximation algorithm and prints the output in the console
 * O(V^2)
 * @param group group of graphs to perform the algorithm
 * @param input graph in which we want to perform the algorithm
 */
void Funcs::otherApprox(string group, int input) {
    pair<vector<Vertex *>, double> r;
    if (group == "") {
        r = customGraph.approxByVertexes();
        for (auto v : r.first) {
            if (v == r.first.back()) {
                cout << v->getId() << endl;
            }
            else cout << v->getId() << " -> ";
        }
        cout << "Total distance: " << r.second << endl;
    }
    else if (group == "rw") {
        switch (input) {
            case 1:
                r = RW_graph1.approxByVertexes();
                for (auto v : r.first) {
                    if (v == r.first.back()) {
                        cout << v->getId() << endl;
                    }
                    else cout << v->getId() << " -> ";
                }
                cout << "Total distance: " << r.second << endl;
                break;
            case 2:
                r = RW_graph2.approxByVertexes();
                for (auto v : r.first) {
                    if (v == r.first.back()) {
                        cout << v->getId() << endl;
                    }
                    else cout << v->getId() << " -> ";
                }
                cout << "Total distance: " << r.second << endl;
                break;
            case 3:
                r = RW_graph3.approxByVertexes();
                for (auto v : r.first) {
                    if (v == r.first.back()) {
                        cout << v->getId() << endl;
                    }
                    else cout << v->getId() << " -> ";
                }
                cout << "Total distance: " << r.second << endl;
                break;
            default:
                break;
        }
    }
}
