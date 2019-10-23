#include "defines.h"
#include "graph.h"

#ifndef PREPROCESS_H
#define PREPROCESS_H

void dfs_bridges(graph g, int u, bool color[], int level[], int pi[], int low[], set<ii> &bridges);

vector<int> preprocess(graph g);

#endif