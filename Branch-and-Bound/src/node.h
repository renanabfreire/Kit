#ifndef NODE_H
#define NODE_H

#include_next <vector>

typedef struct{
	std::vector<pair<int, int>> forbidden_arcs;
	std::vector<std::vector<int>> subtour;
	double lower_bound;
	int chosen;
	bool feasible;
}Node;

#endif // NODE_H
