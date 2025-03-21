#include "LagrangianRelaxation.h"

Solution BB_BFS(Data&data){
    Solution sol;
    Node root; // Getting root
    std::vector<double> lambdaselect(data.getDimension()-1, 0);
    root.lambda = lambdaselect;
    double UB = UBC(data); // starting Upper Bound to LR
    // Starting tree
    list<Node> tree; 
    tree.push_back(root);
    vector<pair<int, int>> ed;

    double upper_bound = UB; // Starting Upper Bound to BnB
    vector<int> seq; // Starting Sequence
    while (!tree.empty()){
        //Taking First node (BFS)
        Node node = tree.front();
        tree.pop_front();
        solve_node(data, node, UB); // solving TSP_{lambda} of the node

        if (node.lower_bound > upper_bound) {
            continue;
        }
        
        // Updanting values
        if (node.feasible) {
            upper_bound = node.lower_bound;
            ed = node.edges;
        } else {
            for (int i = 0; i < node.edges.size();i++){
                if((node.edges[i].first == node.chosen.first) || (node.edges[i].second == node.chosen.first)){
                    Node n; // Getting Children
                    n.forbidden_arcs = node.forbidden_arcs;
                    // Getting each of the edges with the most frequent node of the solution
                    n.forbidden_arcs.push_back(node.edges[i]);
                    n.lambda = node.lambda;
                    tree.push_back(n);
                }
            }
        }
    }
    
    // Updanting solution
    sol.cost = upper_bound;
    seq.push_back(0);
    int cont=0;
    while(!ed.empty()){
        if(ed[cont].first == seq.back()){
            seq.push_back(ed[cont].second);
            ed.erase(ed.begin()+cont);
            cont=-1;
        } else if(ed[cont].second == seq.back()){
            seq.push_back(ed[cont].first);
            ed.erase(ed.begin()+cont);
            cont=-1;
        }
        cont++;
    }
    sol.sequence = seq;
    return sol;
}

Solution BB_DFS(Data&data){
    Solution sol;
    Node root; // Getting root
    std::vector<double> lambdaselect(data.getDimension()-1, 0);
    root.lambda = lambdaselect;
    double UB = UBC(data); // starting Upper Bound to LR
    // Starting tree
    list<Node> tree; 
    tree.push_back(root);
    vector<pair<int, int>> ed;

    double upper_bound = UB; // Starting Upper Bound to BnB
    vector<int> seq; // Starting Sequence
    while (!tree.empty()){
        //Taking Last node (DFS)
        Node node = tree.back();
        tree.pop_back();
        solve_node(data, node, UB); // solving TSP_{lambda} of the node

        if (node.lower_bound > upper_bound) {
            continue;
        }
        
        // Updanting values
        if (node.feasible) {
            upper_bound = node.lower_bound;
            ed = node.edges;
        } else {
            for (int i = 0; i < node.edges.size();i++){
                if((node.edges[i].first == node.chosen.first) || (node.edges[i].second == node.chosen.first)){
                    Node n; // Getting Children
                    n.forbidden_arcs = node.forbidden_arcs;
                    // Getting each of the edges with the most frequent node of the solution
                    n.forbidden_arcs.push_back(node.edges[i]);
                    n.lambda = node.lambda;
                    tree.push_back(n);
                }
            }
        }
    }
    
    // Updanting solution
    sol.cost = upper_bound;
    seq.push_back(0);
    int cont=0;
    while(!ed.empty()){
        if(ed[cont].first == seq.back()){
            seq.push_back(ed[cont].second);
            ed.erase(ed.begin()+cont);
            cont=-1;
        } else if(ed[cont].second == seq.back()){
            seq.push_back(ed[cont].first);
            ed.erase(ed.begin()+cont);
            cont=-1;
        }
        cont++;
    }
    sol.sequence = seq;
    return sol;
}