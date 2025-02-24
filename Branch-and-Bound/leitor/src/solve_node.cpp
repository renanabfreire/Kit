#include "BB.h"

void solve_node(Data * data, Node& no){
	double **cost = new double*[data->getDimension()];
	for (int i = 0; i < data->getDimension(); i++){
		cost[i] = new double[data->getDimension()];
		for (int j = 0; j < data->getDimension(); j++){
			cost[i][j] = data->getDistance(i,j);
		}
	}

	hungarian_problem_t p;
	int mode = HUNGARIAN_MODE_MINIMIZE_COST;
	hungarian_init(&p, cost, data->getDimension(), data->getDimension(), mode); // Carregando o problema

	no.lower_bound = hungarian_solve(&p);

	vector<int> subseq(p.num_rows);
	vector<int> tsubseq;
	int cont_seq = 0;
	for(int i=0;i<p.num_rows;i++)
		for(int j=0;j<p.num_cols;j++){
			if(p.assignment[i][j] == 1){
				subseq[i] = j;
				continue;		
		}
	}
	for(int i=0; i<p.num_rows;i++){
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
	
	if(no.subtour.size() == data->getDimension()){
		no.feasible = true;
	} else {
		no.feasible = false;
	}
	
	int the_chosen = 0;
	for(int i=0; i<no.subtour.size(); i++){
		if(no.subtour[i].size() < no.subtour[the_chosen].size()){
			the_chosen = i;
		}
	}
	no.chosen = the_chosen;

	for(int i = 0; i<no.subtour[the_chosen].size()-1; i++){
		no.forbidden_arcs.push_back({i,i+1});
	}

	hungarian_free(&p);
	for (int i = 0; i < data->getDimension(); i++) delete [] cost[i];
	delete [] cost;
	delete data;
}
