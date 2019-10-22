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
