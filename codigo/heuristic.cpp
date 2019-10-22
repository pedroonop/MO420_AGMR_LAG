#include "heuristic.h"
#include "defines.h"
#include "graph.h"

pair<int, vector<bool> > heuristic(graph g, vector<bool> xk, vector<bool> yk){
	int dv[g.n];
	for (int i = 0; i < g.n; i++){
		dv[i] = 0;
	}

	for (int i = 0; i < g.m; i++){
		if (xk[i]){
			int u = g.edges[i].ff, v = g.edges[i].ss;
			dv[u]++;
			dv[v]++;
		}
	}

	int cont = 0;
	for (int i = 0; i < g.n; i++){
		if (dv[i] > 2) cont++;
	}

	return make_pair(cont, xk);
}
