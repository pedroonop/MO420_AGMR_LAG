#include "defines.h"
#include "io.h"
#include "graph.h"
#include "subgradient.h"

int main(const int argc, const char *argv[]){

	if (argc < 6){
		printf("./main <caminho_arquivo> <max_iteracoes> <tempo limite> <ek> <pre_processamento>\n");
		exit(1);
	}

	graph g = read_graph(argv[1]);
	int maxk = stoi(argv[2]);
	int time_limit = stoi(argv[3]);
	double ek = stod(argv[4]);
	int type = stoi(argv[5]);

	int dk = -1, pk = -1;
	vector<bool> solution;
	di r;
	if (type) r = subgradient_preprocess(g, maxk, time_limit, ek, dk, pk, solution);
	else r = subgradient(g, maxk, time_limit, ek, dk, pk, solution);

	printf("%lf %d\n", r.ff, dk);
	printf("%d %d\n", r.ss, pk);
	printf("%d\n", maxk);

	return 0;
}