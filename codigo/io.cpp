#include "io.h"
#include "graph.h"
#include "defines.h"

graph read_graph(const char *file_name){
	ifstream file;
	file.open(file_name);

	int n, m;
	file >> n >> m;

	graph g;
	g.n = n;
	g.m = m;
	g.adj.resize(n);

	for (int i = 0; i < m; i++){
		int u, v;
		file >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
		ii edge = ii(min(u,v), max(u,v));
		g.edges.push_back(edge);
	}
	sort(g.edges.begin(), g.edges.end());

	file.close();

	return g;
}

void write_data(const char *file_name, graph g, float dual, int dk, int primal, int pk, int k, vector<bool> solution){
	ofstream file;
	file.open(file_name);

	file << fixed << setprecision(6);

	file << dual << endl;
	file << dk << endl;
	file << primal << endl;
	file << pk << endl;
	file << k << endl;

	for (int i = 0; i < g.m; i++){
		if (solution[i]) file << g.edges[i].ff << " " << g.edges[i].ss << endl;
	}

	file.close();
}