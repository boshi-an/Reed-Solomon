#include "ReedSolomon.h"

vector<int> disturb(vector<int> code, int num)
{
	for(int i=0; i<num; i++) code[rand()%code.size()] = rand()%P;
	return code;
}

int main()
{
	srand(time(0));
	int k, n, x;
	vector<int> src, code, ans;
	cin >> k >> n;
	for(int i=0; i<k; i++)
	{
		cin >> x;
		src.push_back(x);
	}
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

	return 0;
}