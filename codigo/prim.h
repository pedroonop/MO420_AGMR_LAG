#include "defines.h"
#include "graph.h"

/*
Argumentos: o grafo e uma matriz de pesos, onde a
posição (i,j) indica o peso da aresta (i,j).
Retorno: um vetor de booleanos de tamanho m, onde
uma posição e vale 1 se e somente se a aresta
está na AGM.
*/
vector<bool> prim(graph g, double *weights[]);