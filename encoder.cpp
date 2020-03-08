#include "ReedSolomon.h"

vector<int> encode(vector<int> src, int n)
{
	vector<int> ret;
	assert(n >= src.size());
	for(int i=0; i<n; i++) ret.push_back(calc_poly(src, i));
	return ret;
}