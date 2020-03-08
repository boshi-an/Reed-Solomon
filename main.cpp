#include "ReedSolomon.h"

vector<int> disturb(vector<int> code, int num)
{
	for(int i=0; i<num; i++) code[rand()%code.size()] = rand()%P;
	return code;
}

bool same_vector(vector<int> a, vector<int> b)
{
	if(a.size() != b.size()) return false;
	for(int i=0; i<a.size(); i++)
		if(a[i] != b[i]) return false;
	return true;
}

int main()
{
	srand(time(0));
	int k, n, x;
	vector<int> src, code, ans;
	cin >> k >> n;

	while(1)
	{
		src.clear();
		for(int i=0; i<k; i++) src.push_back(rand()%P);

		cout << "source : ";
		for(auto i : src) cout << i << " ";
		cout << endl;

		code = encode(src, n);

		cout << "transmit : ";
		for(auto i : code) cout << i << " ";
		cout << endl;

		code = disturb(code, rand()%((n-k)/2+1));

		cout << "recieve : ";
		for(auto i : code) cout << i << " ";
		cout << endl;

		ans = decode(code, k);

		cout << "ans : ";
		for(auto i : ans) cout << i << " ";
		cout << endl;

		if(!same_vector(ans, src))
		{
			break;
		}
	}
	return 0;
}