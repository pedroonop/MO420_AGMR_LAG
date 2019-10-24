#include "subgradient.h"
#include "defines.h"
#include "graph.h"
#include "prim.h"
#include "inspect.h"
#include "heuristic.h"
#include "preprocess.h"
#include "ch.h"

di subgradient(graph g, int kmax, int time_limit, double ek, int &dk, int &pk, vector<bool> &solution){
	time_t start_time = time(NULL);
	
	bool verbose = false;
	double best_dual = 0;
	int best_primal = INF;

	vector<int> V_;
	for (int i = 0; i < g.n; i++){
		if (g[i].size() > 2) V_.push_back(i);
	}

	vector<double> lambda;
	lambda.resize(g.n, 0);

	unsigned max_du = 1;
	for (int v : V_){
		unsigned aux = g[v].size();
		max_du = max(max_du, aux);
 	}
	for (int v : V_){
		lambda[v] = 1.0 / max_du;
	}

	int last_update = 0;
	
	for (int k = 0; k < kmax; k++){
		time_t current_time = time(NULL);
		double spent_time = current_time - start_time;
		if (spent_time > time_limit) break;

		if (k - max(last_update, dk) > 30){
			ek = ek / 2;
			last_update = k;
		}

		double *weights1[g.n], weights2[g.n];
		for (int i = 0; i < g.n; i++){
			weights1[i] = (double*)malloc(g.n * sizeof(double));
			for (int j = 0; j < g.n; j++){
				weights1[i][j] = 0;
			}
			weights2[i] = 0;
		}

		for (ii edge : g.edges){
			int u = edge.ff, v = edge.ss;
			weights1[u][v] = lambda[u] + lambda[v];
			weights1[v][u] = lambda[v] + lambda[u];
		}

		for (int v : V_){
			weights2[v] = 1 - (g[v].size() * lambda[v]);
		}

		vector<bool> xk = prim(g, weights1);
		for (int i = 0; i < g.n; i++){
			free(weights1[i]);
		}

		vector<bool> yk = inspect(g.n, weights2);

		double zk = 0;
		for (int v : V_){
			zk += -2 * lambda[v];
		}
		for (int i = 0; i < g.m; i++){
			if (xk[i]){
				int u = g.edges[i].ff, v = g.edges[i].ss;
				zk += lambda[u] + lambda[v];
			}
		}
		for (int v : V_){
			if (yk[v]) zk += 1 - (g[v].size() * lambda[v]);
		}

		pair<int, vector<bool> > fixed = heuristic(g, xk, yk);
		if (verbose) printf("iteration %d: current dual = %lf, current primal = %d\n", k, zk, fixed.ff);

		if (zk > best_dual){
			best_dual = zk;
			dk = k;
			if (!verbose) printf("iteration %d: ", k);
			printf("new best dual = %lf\n", best_dual);
		}

		if (fixed.ff < best_primal){
			best_primal = fixed.ff;
			solution = fixed.ss;
			if (!verbose) printf("iteration %d: ", k);
			printf("new best primal = %d\n", best_primal);
		}

		vector<double> gk;
		gk.resize(g.n);
		for (int v : V_){
			gk[v] = -2;
			if (yk[v]) gk[v] -= g[v].size();
		}
		for (int i = 0; i < g.m; i++){
			if (xk[i]){
				int u = g.edges[i].ff, v = g.edges[i].ss;
				gk[u]++;
				gk[v]++;
			}
		}

		double module2 = 0;
		for (int v : V_){
			module2 += gk[v] * gk[v];
		}

		double tk = ek * (best_primal - zk) / module2;
		for (int v : V_){
			lambda[v] += tk * gk[v];
			if (lambda[v] < 0) lambda[v] = 0;
			if (lambda[v] > 1.0/g[v].size()) lambda[v] = 1.0/g[v].size();
		}
	}
	return make_pair(best_dual, best_primal);
}

di subgradient_preprocess(graph g, int kmax, int time_limit, double ek, int &dk, int &pk, vector<bool> &solution){
	time_t start_time = time(NULL);

	bool verbose = false;
	double best_dual = 0;
	int best_primal = INF;

	vector<int> V_;
	for (int i = 0; i < g.n; i++){
		if (g[i].size() > 2) V_.push_back(i);
	}

	vector<double> lambda;
	lambda.resize(g.n, 0);

	unsigned max_du = 1;
	for (int v : V_){
		unsigned aux = g[v].size();
		max_du = max(max_du, aux);
 	}
	for (int v : V_){
		lambda[v] = 1.0 / max_du;
	}
	vector<int> branches = preprocess(g);

	best_dual = branches.size();
	if (best_dual > 0){
		printf("iteration -1: ");
		printf("new best dual = %lf\n", best_dual);
	}

	pair<int, vector<bool> > ch = construcive_heuristic(g, 100, 0);
	best_primal = ch.ff;
	solution = ch.ss;
	printf("iteration -1: ");
	printf("new best primal = %d\n", ch.ff);

	int last_update = 0;

	for (int k = 0; k < kmax; k++){
		time_t current_time = time(NULL);
		double spent_time = current_time - start_time;
		if (spent_time > time_limit) break;

		if (k - max(last_update, dk) > 30){
			ek = ek / 2;
			last_update = k;
		}

		double *weights1[g.n], weights2[g.n];
		for (int i = 0; i < g.n; i++){
			weights1[i] = (double*)malloc(g.n * sizeof(double));
			for (int j = 0; j < g.n; j++){
				weights1[i][j] = 0;
			}
			weights2[i] = 0;
		}

		for (ii edge : g.edges){
			int u = edge.ff, v = edge.ss;
			weights1[u][v] = lambda[u] + lambda[v];
			weights1[v][u] = lambda[v] + lambda[u];
		}

		for (int v : V_){
			weights2[v] = 1 - (g[v].size() * lambda[v]);
		}
		for (int v : branches){
			weights2[v] = -1;
		}

		vector<bool> xk = prim(g, weights1);
		for (int i = 0; i < g.n; i++){
			free(weights1[i]);
		}

		vector<bool> yk = inspect(g.n, weights2);

		double zk = 0;
		for (int v : V_){
			zk += -2 * lambda[v];
		}
		for (int i = 0; i < g.m; i++){
			if (xk[i]){
				int u = g.edges[i].ff, v = g.edges[i].ss;
				zk += lambda[u] + lambda[v];
			}
		}
		for (int v : V_){
			if (yk[v]) zk += 1 - (g[v].size() * lambda[v]);
		}

		pair<int, vector<bool> > fixed = heuristic(g, xk, yk);
		if (verbose) printf("iteration %d: current dual = %lf, current primal = %d\n", k, zk, fixed.ff);

		if (zk > best_dual){
			best_dual = zk;
			dk = k;
			if (!verbose) printf("iteration %d: ", k);
			printf("new best dual = %lf\n", best_dual);
		}

		if (fixed.ff < best_primal){
			best_primal = fixed.ff;
			solution = fixed.ss;
			if (!verbose) printf("iteration %d: ", k);
			printf("new best primal = %d\n", best_primal);
		}

		vector<double> gk;
		gk.resize(g.n);
		for (int v : V_){
			gk[v] = -2;
			if (yk[v]) gk[v] -= g[v].size();
		}
		for (int i = 0; i < g.m; i++){
			if (xk[i]){
				int u = g.edges[i].ff, v = g.edges[i].ss;
				gk[u]++;
				gk[v]++;
			}
		}

		double module2 = 0;
		for (int v : V_){
			module2 += gk[v] * gk[v];
		}

		double tk = ek * (best_primal - zk) / module2;
		for (int v : V_){
			lambda[v] += tk * gk[v];
			if (lambda[v] < 0) lambda[v] = 0;
			if (lambda[v] > 1.0/g[v].size()) lambda[v] = 1.0/g[v].size();
		}
	}
	return make_pair(best_dual, best_primal);
}
