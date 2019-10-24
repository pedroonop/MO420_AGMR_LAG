#include "defines.h"
#include "graph.h"

#ifndef CH_H
#define CH_H

pair<int, vector<bool> > construcive_heuristic(graph g, int k, int seed);

int cost(int n, vector<ii> edges);

void random_dfs(graph g, int color[], int u, vector<ii> &edges, int seed);

#endif