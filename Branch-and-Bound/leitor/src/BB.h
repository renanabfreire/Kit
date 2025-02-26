#include "data.h"
#include "node.h"
#include "Solution.h"
#include "hungarian.h"

#include <iostream>
#include <list>
#include <algorithm>
#include <unistd.h>

void solve_node(Data*, Node&);
Solution BB_DFS(Data*);
Solution BB_BFS(Data*);
