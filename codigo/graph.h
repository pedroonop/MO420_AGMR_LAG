#include "defines.h"

#ifndef GRAPH_H
#define GRAPH_H

class graph
{
public:
	int n, m;
	vector<vector<int> > adj;
	vector<ii> edges;

	vector<int> &operator[](int i);
};

#endif