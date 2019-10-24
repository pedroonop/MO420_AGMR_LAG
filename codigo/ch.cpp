#include "ch.h"
#include "defines.h"
#include "graph.h"

int cost(int n, vector<ii> edges){
	int degree[n];
	for (int i = 0; i < n; i++){
		degree[i] = 0;
	}

	for (ii edge : edges){
		int u = edge.ff, v = edge.ss;
		degree[u]++;
		degree[v]++;
	}

	int cont = 0;
	for (int i = 0; i < n; i++){
		if (degree[i] > 2) cont++;
	}

	return cont;
}

void random_dfs(graph g, int color[], int u, vector<ii> &edges, int seed){
	vector<int> adj = g[u];
	shuffle(adj.begin(), adj.end(), default_random_engine(rand()));
	for (int v : adj){
		if (color[v] == 0){
			color[v] = 1;
			edges.push_back(ii(min(u,v), max(u,v)));
			random_dfs(g, color, v, edges, rand());
		}
	}
}

pair<int, vector<bool> > construcive_heuristic(graph g, int k, int seed){
	srand(seed);

	int best = INF;
	vector<ii> edges;

	for (int i = 0; i < k; i++){
		vector<ii> current;
		int color[g.n];
		for (int i = 0; i < g.n; i++){
			color[i] = 0;
		}
		int u = rand() % g.n;
		color[u] = 1;
		random_dfs(g, color, u, current, rand());

		int c = cost(g.n, current);

		if (c < best){
			best = c;
			edges = current;
		}
	}

	vector<bool> r;
	r.resize(g.m, false);

	for (ii edge : edges){
		int i = lower_bound(g.edges.begin(), g.edges.end(), edge) - g.edges.begin();
		r[i] = true;
	}

	return make_pair(best, r);
}

