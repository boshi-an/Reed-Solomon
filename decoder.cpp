#include "ReedSolomon.h"

vector<int> decode(vector<int> src, int k)
{
	int n = src.size();
	assert(n >= k);
	for(int e=(n-k)/2; e>=0; e--)
	{
		vector<vector<int> > mat;
		for(int i=0; i<n; i++)
		{
			vector<int> row;
			for(int j=0; j<=e; j++) row.push_back(src[i] * qpow(i, j) % P);
			for(int j=0; j<=e+k-1; j++) row.push_back((P - qpow(i, j)) % P);
			row.push_back(0);
			mat.push_back(row);
		}
		vector<int> row;
		for(int j=0; j<e; j++) row.push_back(0);
		row.push_back(1);
		for(int j=0; j<e+k; j++) row.push_back(0);
		row.push_back(1);
		mat.push_back(row);

		/*cout << "e = " << e << " matrix :" << endl;
		for(auto i : mat)
		{
			for(auto j : i) cout << j << " ";
			cout << endl;
		}
		cout << endl;*/

		pair<int, vector<int> > sol = gauss(mat, n+1, k+2*e+1);
		if(sol.first == 1)
		{
			vector<int> func_e, func_q, func_f, func_r;
			for(int i=0; i<=e; i++) func_e.push_back(sol.second[i]);
			for(int i=0; i<=e+k-1; i++) func_q.push_back(sol.second[e+i+1]);
			pair<vector<int>, vector<int> > ans = poly_div(func_q, func_e);
			if(ans.second.size())
			{
				cerr << "Uncorrectable Error Detected." << endl;
				vector<int> empty_set;
				return empty_set;
			}
			else return ans.first;
		}
	}
	cerr << "Uncorrectable Error Detected." << endl;
	vector<int> empty_set;
	return empty_set;
}