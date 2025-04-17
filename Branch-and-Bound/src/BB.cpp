#include "BB.h"

Solution BB_DFS(Data* data){
    Solution sol;
    Node root; // Getting root
    // Starting tree
    list<Node> tree; 
    tree.push_back(root);

    double upper_bound = INFINITY; // Starting Upper_Bound
    vector<int> seq; // Starting Sequence
    while (!tree.empty()){
        //Taking last node (DFS)
        Node node = tree.back();
        tree.pop_back();
        solve_node(data, node); // solving AT_TSP of the node

        if (node.lower_bound > upper_bound) {
            continue;
        }
        
        // Updanting values
        if (node.feasible && (min(node.lower_bound, upper_bound) == node.lower_bound)) {
            upper_bound = node.lower_bound;
            seq = node.subtour[0];
        } else {
            int chosen = node.chosen;
            for (size_t i = 0; i < node.subtour[chosen].size() - 1; i++){
                Node n; // Getting Children
                n.forbidden_arcs = node.forbidden_arcs;
                pair<int, int> forbidden = { node.subtour[chosen][i], node.subtour[chosen][i+1] };
                n.forbidden_arcs.push_back(forbidden);
                tree.push_back(n);
            }
        }
    }
    
    // Updanting solution
    sol.coust = upper_bound;
    sol.sequence = seq;
    return sol;
}

Solution BB_BFS(Data* data){
    Solution sol;
    Node root; // Getting root
    // Starting tree
    list<Node> tree;
    tree.push_back(root);

    double upper_bound = INFINITY; // Starting Upper_Bound
    vector<int> seq; // Starting Sequence
    while (!tree.empty()){
        //Taking first node (BFS)
        Node node = tree.front();
        tree.pop_front();
        solve_node(data, node); // solving AT_TSP of the node

        if (node.lower_bound > upper_bound) {
            continue;
        }
        
        // Updanting values
        if (node.feasible && (min(node.lower_bound, upper_bound) == node.lower_bound)) {
            upper_bound = node.lower_bound;
            seq = node.subtour[0];
        } else {
            int chosen = node.chosen;
            for (size_t i = 0; i < node.subtour[chosen].size() - 1; i++){
                Node n; // Getting Children
                n.forbidden_arcs = node.forbidden_arcs;
                pair<int, int> forbidden = { node.subtour[chosen][i], node.subtour[chosen][i+1] };
                n.forbidden_arcs.push_back(forbidden);
                tree.push_back(n);
            }
        }
    }
    
    // Updanting solution
    sol.coust = upper_bound;
    sol.sequence = seq;
    return sol;
}
