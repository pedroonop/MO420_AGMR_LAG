#include "defines.h"
#include "graph.h"

#ifndef SUBGRADIENT_H
#define SUBGRADIENT_H

di subgradient(graph g, int &kmax, int time_limit, double ek, int &dk, int &pk, vector<bool> &solution);

di subgradient_preprocess(graph g, int &kmax, int time_limit, double ek, int &dk, int &pk, vector<bool> &solution);

#endif