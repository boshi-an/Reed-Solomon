#include "ReedSolomon.h"

int qpow(int x, int t)
{
	int ret = 1;
	while(t)
	{
		if(t & 1) ret = ret*x % P;
		x = x*x % P;
		t >>= 1;
	}
	return ret;
}

int inv(int x)
{
	return qpow(x, P-2);
}

int calc_poly(vector<int> poly, int x)
{
	int ret = 0;
	reverse(poly.begin(), poly.end());
	for(auto p : poly) ret = (ret*x + p) % P;
	return ret;
}

//up = dn*first + second;

pair<vector<int>, vector<int> > poly_div(vector<int> up, vector<int> dn)
{
	vector<int> ans;
	while(up.size() && dn.size() && !up.back() && !dn.back()) up.pop_back(), dn.pop_back();
	int len = up.size()-dn.size();
	assert(len >= 0);
	for(int i=len; i>=0; i--)
	{
		int mul = up[i+dn.size()-1] * inv(dn.back()) % P;
		ans.push_back(mul);
		for(int j=0; j<dn.size(); j++) up[i+j] = (up[i+j] - mul*dn[j] + P*P) % P;
	}
	reverse(ans.begin(), ans.end());
	while(up.size() && !up.back()) up.pop_back();
	return make_pair(ans, up);
}

//0 for multiple solutions
//1 for single solution

pair<int, vector<int> > gauss(vector<vector<int> > mat, int n, int m)
{
	vector<int> sol;
	assert(mat.size() == n);
	for(int i=0; i<n; i++) assert(mat[i].size() == m+1);
	for(int i=0; i<m; i++)
	{
		int mxp = i;
		for(int j=i+1; j<n; j++)
			if(mat[j][i])
				mxp = j;
		swap(mat[i], mat[mxp]);
		if(!mat[i][i]) return make_pair(0, sol);
		int mul = inv(mat[i][i]);
		for(int j=i; j<=m; j++) mat[i][j] = mat[i][j] * mul % P;
		for(int j=0; j<n; j++)
		{
			if(j == i) continue;
			mul = mat[j][i];
			for(int k=0; k<=m; k++) mat[j][k] = (mat[j][k] + P*P - mul*mat[i][k]) % P;
		}
	}
	for(int i=0; i<m; i++) sol.push_back(mat[i][m]);
	return make_pair(1, sol);
}