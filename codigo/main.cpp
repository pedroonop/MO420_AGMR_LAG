#include "defines.h"
#include "io.h"
#include "graph.h"
#include "subgradient.h"

int main(const int argc, const char *argv[]){

	if (argc < 4){
		printf("./main <caminho_arquivo> <max_iteracoes> <ek>\n");
		exit(1);
	}

	graph g = read_graph(argv[1]);
	int maxk = stoi(argv[2]);
	double ek = stod(argv[3]);

	int dk = -1, pk = -1;
	vector<bool> solution;
	di r = subgradient_preprocess(g, maxk, ek, dk, pk, solution);

	printf("%lf %d\n", r.ff, r.ss);

	return 0;
}