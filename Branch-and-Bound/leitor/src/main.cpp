#include <iostream>
#include "BB.h"
using namespace std;

int main(int argc, char** argv) {

	Data * data = new Data(argc, argv[1]);
	data->readData();

	Node node;
	solve_node(data, node);

	return 0;
}
