#include "BB.h"

void solve_node(Data * data, Node& no, hungarian_problem_t& p){
	no.lower_bound = hungarian_solve(&p);
	cout << "here" << endl;

	vector<int> subseq(p.num_rows);
	vector<int> tsubseq;
	vector<vector<int>> total;
	int cont_seq = 0;
	for(int i=0;i<p.num_rows;i++)
		for(int j=0;j<p.num_cols;j++){
			if(p.assignment[i][j] == 1){
				subseq[i] = j;		
		}
	}
	for(int i=0; i<p.num_rows;i++){
		if(subseq[cont_seq] == -1)
		{
			tsubseq.push_back(tsubseq.front());
			cout << tsubseq.back() << endl;
			cont_seq = 0;
			while(subseq[cont_seq] == -1)
				cont_seq ++;
			total.push_back(tsubseq);
			tsubseq.clear();
		}
		tsubseq.push_back(subseq[cont_seq]);
		cout << tsubseq.back() << endl;
		subseq[cont_seq] = -1;
		cont_seq = tsubseq.back();
	}
	tsubseq.push_back(tsubseq.front());
	cout << tsubseq.back() << endl;
	total.push_back(tsubseq);
	no.subtour = total;
	
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
	hungarian_free(&p);
	delete data;
}
