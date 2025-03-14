#include "Kruskal.h"
#include "Data.h"
#include "Solution.h"
#include "node.h"

#include <list>

void solveLambda(int, double**, SolutionLambda&, vector<double>);
void subgradientMethod(SolutionLambda&, int, double**, double, double, int, double);

void solve_node(Data&, Node&, double);
Solution BB(Data& data);