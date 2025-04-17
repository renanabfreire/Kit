#include "data.h"
#include "node.h"
#include "Solution.h"
#include "hungarian.h"

#include <iostream>
#include <list>
#include <algorithm>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>

void solve_node(Data*, Node&);
Solution BB_DFS(Data*);
Solution BB_BFS(Data*);
