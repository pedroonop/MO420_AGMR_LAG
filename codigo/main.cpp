#include "defines.h"
#include "io.h"
#include "graph.h"
#include "subgradient.h"

int main(const int argc, const char *argv[]){

	graph g = read_graph(argv[1]);
	int time_limit = stoi(argv[3]);
	int maxk = 1000000000;
	double ek = 0.1;
	int type = 1;

	int dk = -1, pk = -1;
	vector<bool> solution;
	di r;
	if (type) r = subgradient_preprocess(g, maxk, time_limit, ek, dk, pk, solution);
	else r = subgradient(g, maxk, time_limit, ek, dk, pk, solution);

	write_data(argv[2], g, r.ff, dk, r.ff, pk, maxk, solution);

	printf("%lf %d\n", r.ff, dk);
	printf("%d %d\n", r.ss, pk);
	printf("%d\n", maxk);

	return 0;
}