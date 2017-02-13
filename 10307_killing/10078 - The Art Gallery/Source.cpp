#include <vector>
#include <iostream>

using namespace std;

//Check if always right turns or always left turns, if true it has no critpoints
//Example, if there is a left turn amongs consecutive right turns this will create critpoint


int cross(pair<int, int> p0, pair<int, int> p1, pair<int, int>  p2) 
{
	int x1 = p1.first - p0.first;
	int x2 = p2.first - p0.first;
	int y1 = p1.second - p0.second;
	int y2 = p2.second - p0.second;
	return x1 * y2 - x2 * y1;
}

int main()
{
	int N = 1;
	while (true)
	{
		scanf_s("%d", &N);

		if (N == 0)
			return false;

		pair<int, int> c[51];

		for (int i = 0; i < N; i++)
		{
			pair<int, int> p;
			scanf_s("%d%d", &p.first, &p.second);
			c[i] = p;
		}
		c[N] = c[0];
		c[N + 1] = c[1];

		bool convex = true;
		int crossProd = cross(c[0], c[1], c[2]);

		for (int i = 1; i < N; i++)
		{
			int tempCrossProd = crossProd;
			crossProd= cross(c[i], c[i+1], c[i+2]);

			if (tempCrossProd * crossProd < 0)
			{
				convex = false;
				break;
			}
		}
		if (!convex)
		{
			cout << "Yes" << endl;
		}
		else
		{
			cout << "No" << endl;
		}
	}
	return 0;
}





