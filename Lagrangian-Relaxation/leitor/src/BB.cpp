#include "LagrangianRelaxation.h"

Solution BB(Data&data){
    Solution sol;
    Node root; // Getting root
    double UB;
    // Starting tree
    list<Node> tree; 
    tree.push_back(root);
    vector<pair<int, int>> ed;

    double upper_bound = INFINITY; // Starting Upper_Bound
    vector<int> seq; // Starting Sequence
    while (!tree.empty()){
        //Taking last node (DFS)
        Node node = tree.back();
        tree.pop_back();
        solve_node(data, node, UB); // solving AT_TSP of the node

        if (node.lower_bound > upper_bound) {
            continue;
        }
        
        // Updanting values
        if (node.feasible && (min(node.lower_bound, upper_bound) == node.lower_bound)) {
            upper_bound = node.lower_bound;
            ed = node.edges;
        } else {
            for (size_t i = 0; i < node.chosen.second; i++){
                Node n; // Getting Children
                n.forbidden_arcs = node.forbidden_arcs;
                pair<int, int> forbidden = { node.subtour[chosen][i], node.subtour[chosen][i+1] };
                n.forbidden_arcs.push_back(forbidden);
                tree.push_back(n);
            }
        }
    }
    
    // Updanting solution
    sol.cost = upper_bound;
    seq.push_back(1);
    int cont=0;
    while(!ed.empty()){
        if(ed[cont].first == seq.back()){
            seq.push_back(ed[cont].second);
            ed.erase(ed.begin()+cont);
            cont=-1;
        }
        if(ed[cont].second == seq.back()){
            seq.push_back(ed[cont].first);
            ed.erase(ed.begin()+cont);
            cont=-1;
        }
        cont++;
    }
    sol.sequence = seq;
    return sol;
}