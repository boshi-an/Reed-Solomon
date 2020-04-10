#ifndef _ReedSolomon_H_

#define _ReedSolomon_H_

#include <bits/stdc++.h>

const int P = 251;

using namespace std;

int qpow(int, int);
int inv(int);
int calc_poly(vector<int>, int);
pair<vector<int>, vector<int> > poly_div(vector<int>, vector<int>);
pair<int, vector<int> > gauss(vector<vector<int> >, int, int);

vector<int> encode(vector<int>, int);
vector<int> decode(vector<int>, int);

#endif