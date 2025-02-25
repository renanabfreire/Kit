#include <iostream>
#include <list>
#include <algorithm>
#include <unistd.h>
#include "BB.h"       

using namespace std;

int main(int argc, char** argv) {
    // Cria e lê os dados
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

    // Inicializa a lista de nós a serem explorados
    list<Node> tree;
    tree.push_back(root);

    double upper_bound = INFINITY;
    while (!tree.empty()){
        // Obtém e remove o primeiro nó da lista
        Node node = tree.front();
        tree.pop_front();
        // Recalcula a solução do nó atual
        for (int i = 0; i < data->getDimension(); i++){
            for (int j = 0; j < data->getDimension(); j++){
                cost[i][j] = data->getDistance(i, j);
            }
        }
        solve_node(data, node, cost, mode, p);

        // Se a cota inferior do nó for pior que a melhor solução conhecida, descarte-o
        if (node.lower_bound > upper_bound) {
            continue;
        }
        
        // Se o nó é viável, atualiza a cota superior
        if (node.feasible) {
            upper_bound = min(node.lower_bound, upper_bound);
        } else {
            // Para cada arco do subtour escolhido, cria um nó filho com o arco proibido
            int chosen = node.chosen;
            for (size_t i = 0; i < node.subtour[chosen].size() - 1; i++){
                Node n;
                // Copia os arcos proibidos do nó atual
                // Proíbe o arco atual
                pair<int, int> forbidden = { node.subtour[chosen][i], node.subtour[chosen][i+1] };
                n.forbidden_arcs.push_back(forbidden);
                tree.push_back(n);
            }
        }
    }
    cout << upper_bound << endl;

    // Liberação de memória: desaloca a matriz de custos
    delete data;
    hungarian_free(&p);
	for (int i=0; i < data->getDimension(); i++) delete [] cost[i];
	delete [] cost;
	return 0;
}
