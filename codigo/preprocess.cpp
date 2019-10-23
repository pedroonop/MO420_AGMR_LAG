#include "preprocess.h"
#include "defines.h"
#include "graph.h"

void dfs_bridges(graph g, int u, bool color[], int level[], int pi[], int low[], set<ii> &bridges){
	static int time = 1;
	color[u] = true;
	level[u] = low[u] = time++;

	for (int v : g[u]){
		if (!color[v]){
			pi[v] = u;
			dfs_bridges(g, v, color, level, pi, low, bridges);
			low[u] = min(low[u], low[v]);
			if (low[v] > level[u])
				bridges.insert(ii(min(u,v), max(u,v)));
		}
		else if (v != pi[u]){
			low[u] = min(low[u], level[v]);
		}
	}
}

vector<int> preprocess(graph g){
	bool color[g.n];
	int level[g.n], pi[g.n], low[g.n];
	set<ii> bridges;
	for (int i = 0; i < g.n; i++){
		color[i] = false;
		level[i] = low[i] = 0;
		pi[i] = -1;
	}

	dfs_bridges(g, 0, color, level, pi, low, bridges);

	int degree[g.n];
	for (int i = 0; i < g.n; i++) degree[i] = 0;

	for (ii edge : bridges){
		degree[edge.ff]++;
		degree[edge.ss]++;
	}
	
	vector<int> branches;
	for (int i = 0; i < g.n; i++){
		if (degree[i] > 2) branches.push_back(i);
	}

	return branches;
}
