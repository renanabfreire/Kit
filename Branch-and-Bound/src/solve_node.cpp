#include "BB.h"

void solve_node(Data * data, Node& no){
	// Taking cost matrix
    double** cost = new double*[data->getDimension()];
    for (int i = 0; i < data->getDimension(); i++){
        cost[i] = new double[data->getDimension()];
        for (int j = 0; j < data->getDimension(); j++){
            cost[i][j] = data->getDistance(i, j);
        }
    }
	for (int i=0; i < no.forbidden_arcs.size(); i++){
		cost[no.forbidden_arcs[i].first][no.forbidden_arcs[i].second] = 99999;
	}
	
	// solving node with Hungarian Algorithm
	hungarian_problem_t p;
	int mode = HUNGARIAN_MODE_MINIMIZE_COST;
	hungarian_init(&p, cost, data->getDimension(), data->getDimension(), mode);
	no.lower_bound = hungarian_solve(&p);

	// Updanting subsequences of the node
	vector<int> subseq(p.num_rows);
	vector<int> tsubseq;
	int cont_seq = 0;
	for(int i=0;i<p.num_rows;i++) // AssigmentMatrix -> ConnectionsVector
		for(int j=0;j<p.num_cols;j++){
			if(p.assignment[i][j] == 1){
				subseq[i] = j;		
		}
	}
	for(int i=0; i<p.num_rows;i++){ // ConnectionsVector -> SubsequencesVectorVector
		if(subseq[cont_seq] == -1)
		{
			tsubseq.push_back(tsubseq.front());
			cont_seq = 0;
			while(subseq[cont_seq] == -1)
				cont_seq ++;
			no.subtour.push_back(tsubseq);
			tsubseq.clear();
		}
		tsubseq.push_back(subseq[cont_seq]);
		subseq[cont_seq] = -1;
		cont_seq = tsubseq.back();
	}
	tsubseq.push_back(tsubseq.front());
	no.subtour.push_back(tsubseq);
	
	// Checking if it is feasible
	if((no.subtour[0].size()-1) == data->getDimension()){
		no.feasible = true;
	} else {
		no.feasible = false;
	}
	
	int the_chosen = 0; // Taking smallest sequence
	for(int i=0; i<no.subtour.size(); i++){
		if(no.subtour[i].size() < no.subtour[the_chosen].size()){
			the_chosen = i;
		}
	}
	no.chosen = the_chosen;
    hungarian_free(&p);
	for (int i=0; i < data->getDimension(); i++) delete [] cost[i];
	delete [] cost;
}
