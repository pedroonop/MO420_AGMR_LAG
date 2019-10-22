#include "inspect.h"
#include "defines.h"

vector<bool> inspect(int n, double weights[]){
	vector<bool> r;
	r.resize(n);
	for (int i = 0; i < n; i++){
		if (weights[i] < 0) r[i] = true;
		else r[i] = false;
	}
	return r;
}
