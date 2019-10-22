#include "prim.h"
#include "defines.h"
#include "graph.h"

vector<bool> prim(graph g, double *weights[]){
	vector<bool> S;
	S.resize(g.n, false);

	vector<double> d;
	d.resize(g.n, INF);
	d[0] = 0;

	vector<int> pi;
	pi.resize(g.n, -1);

	priority_queue<di, vector<di>, greater<di> > pq;
	pq.push(di(0, 0));

	while (!pq.empty()){
		int u = pq.top().ss;
		pq.pop();

		if (S[u]) continue;
		S[u] = true;

		for (int v : g[u]){
			if (!S[v] && weights[u][v] < d[v]){
				d[v] = weights[u][v];
				pi[v] = u;
				pq.push(di(d[v], v));
			}
		}
	}

	vector<bool> r;
	r.resize(g.m, false);

	for (int i = 1; i < g.n; i++){
		ii edge = ii(min(i,pi[i]), max(i,pi[i]));
		int j = lower_bound(g.edges.begin(), g.edges.end(), edge) - g.edges.begin();
		r[j] = true;
	}

	return r;
}