#include <iostream>
#include <list>
#include <algorithm>
#include <unistd.h>
#include "BB.h"       

using namespace std;

int main(int argc, char** argv) {
    Data* data = new Data(argc, argv[1]);
    data->readData();
    Node root;
    hungarian_problem_t p;
    int mode = HUNGARIAN_MODE_MINIMIZE_COST;
    double** cost = new double*[data->getDimension()];
    for (int i = 0; i < data->getDimension(); i++){
        cost[i] = new double[data->getDimension()];
        for (int j = 0; j < data->getDimension(); j++){
            cost[i][j] = data->getDistance(i, j);
        }
    }
    hungarian_init(&p, cost, data->getDimension(), data->getDimension(), mode);

    list<Node> tree;
    tree.push_back(root);

    double upper_bound = INFINITY;
    vector<int> seq;
    while (!tree.empty()){
        Node node = tree.front();
        tree.pop_front();
        solve_node(data, node, cost, mode);

        if (node.lower_bound > upper_bound) {
            continue;
        }
        
        if (node.feasible) {
            upper_bound = min(node.lower_bound, upper_bound);
            if(node.lower_bound < upper_bound) seq = node.subtour[0];
        } else {
            int chosen = node.chosen;
            for (size_t i = 0; i < node.subtour[chosen].size() - 1; i++){
                Node n;
                n.forbidden_arcs = node.forbidden_arcs;
                pair<int, int> forbidden = { node.subtour[chosen][i], node.subtour[chosen][i+1] };
                n.forbidden_arcs.push_back(forbidden);
                tree.push_back(n);
            }
        }
        //sleep(1);
    }
    cout << upper_bound << endl;

    delete data;
    hungarian_free(&p);
	for (int i=0; i < data->getDimension(); i++) delete [] cost[i];
	delete [] cost;
	return 0;
}
