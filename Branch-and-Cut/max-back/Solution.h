#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>

typedef struct{
    std::vector<int> sequence;
    double value;
}Solution;

typedef struct{
    std::vector<std::pair<int, int>> edges;
    double value;
}SolutionRelaxed;

#endif