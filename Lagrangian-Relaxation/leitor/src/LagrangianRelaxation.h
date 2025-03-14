#include "Kruskal.h"
#include "Data.h"
#include "Solution.h"
#include "node.h"

void solveLambda(int, double**, SolutionLambda&, vector<double>);
Solution subgradientMethod(SolutionLambda&, int, double**, double, double, int, double);

void solve_node(Data&, Node&, double);