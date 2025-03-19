#include "LagrangianRelaxation.h"

void solve_node(Data& data, Node& no, double UB){
    //taking cost matrix
    double** cost = new double*[data.getDimension()];
    for (int i=0; i< data.getDimension(); i++){
        cost[i] = new double[data.getDimension()];
        for(int j=0; j<data.getDimension(); j++){
            cost[i][j] = data.getDistance(i+1, j+1);
        }
    }
    for(int i=0; i<no.forbidden_arcs.size(); i++){
        cost[no.forbidden_arcs[i].first][no.forbidden_arcs[i].second] = 99999;
        cost[no.forbidden_arcs[i].second][no.forbidden_arcs[i].first] = 99999;
    }

    // Solving node with Lagrangian Relaxation
    SolutionLambda x;
    subgradientMethod(x ,data.getDimension(), cost, 1, UB, 30, 0.00001);
    no.lower_bound = x.cost;
    no.edges = x.edges;

    // checking if it is feasible
    no.feasible = true;
    int c[data.getDimension()];
    for(int i=0; i<data.getDimension(); i++){
        int cont = 0;
        for(const auto& edge : x.edges) {
            if(edge.first == i || edge.second == i)
                cont++;
        }
        c[i] = cont;
        if(cont != 2) // if some node dont is subject the degree restriction the node isn't feasible
            no.feasible = false;
    }

    // chosing the forbidden node
    int chosed=0;
    for(int i=1; i < data.getDimension(); i++){
        if(c[i] > c[chosed]){
            chosed = i;
        }
    }
    no.chosen.first = chosed;
    no.chosen.second = c[chosed];

    delete [] cost;
}