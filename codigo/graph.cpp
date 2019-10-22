#include "graph.h"
#include "defines.h"

vector<int> &graph::operator[](int i){
	return this->adj[i];
}
