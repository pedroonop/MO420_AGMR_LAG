#include "defines.h"
#include "graph.h"

#ifndef IO_H
#define IO_H

/*
Argumentos: o caminho para o arquivo de entrada.
Retorno: o grafo descrito pelo arquivo.
*/
graph read_graph(const char *file_name);

#endif