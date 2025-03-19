#include "Kruskal.h"
#include "Data.h"
#include "Solution.h"
#include "node.h"
#include "InsertInfo.h"

#include <list>
#include <algorithm>

// Functions to apply Lagrangian Relaxation
void solveLambda(int, double**, SolutionLambda&, vector<double>);
void subgradientMethod(SolutionLambda&, int, double**, double, double, int, double);

// Functions to apply BnB
void solve_node(Data&, Node&, double);
Solution BB_DFS(Data& data);
Solution BB_BFS(Data& data);
double UBC(Data&);