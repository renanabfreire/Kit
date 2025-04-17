#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
using namespace std;

typedef struct
{
    std::vector<int> sequence;
    double cost;
}Solution;

typedef struct
{
    std::vector<pair<int, int>> edges;
    double cost;
}SolutionLambda;

#endif // SOLUTION_H