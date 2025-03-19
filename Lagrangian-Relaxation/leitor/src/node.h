#ifndef NODE_H
#define NODE_H

#include <vector>

typedef struct{
    std::vector<std::pair<int, int>> forbidden_arcs;
    std::vector<double> lambda;
    std::vector<std::pair<int, int>> edges;
    double lower_bound;
    pair<int, int> chosen;
    bool feasible;
}Node;

#endif // NODE_H