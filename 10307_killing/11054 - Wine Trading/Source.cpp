#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

int main()
{
	vector<long long> res;

	while (true)
	{
		long long ans = 0;
		long long n = 0, k = 0;
		long long a[100000];
		scanf("%d", &n);
		if (n == 0)
		{
			for (int i = 0; i < res.size(); i++)
				cout << res[i] << endl;
			return false;
		}
		string input;
		cin.get();
		getline(cin, input);
		stringstream stream(input);

		long long x = 0, y = 0, r = 0;

		while (true)
		{
			long long d; stream >> d;
			if (!stream)
				break;

			if (x != 0)
			{
				r += fabs(x);
				x += d;
			}
			else
				x = d;


			a[k] = d;
			k++;	
		}

		res.push_back(r);
	}
}