#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>

/*Linetrace and then math for slopes and exposure*/

using namespace std;

bool compare(pair<int, int> p1, pair<int, int> p2)
{
	return p1.first > p2.first;
}

int main()
{
	int cases;
	scanf_s("%d", &cases);


	for (int i = 0; i < cases; i++)
	{
		int N;
		vector<pair<int, int>> coord;
		scanf_s("%d", &N);
		for (int j = 0; j < N; j++)
		{
			pair<int, int> p;
			scanf_s("%d %d", &p.first, &p.second);
			coord.push_back(p);
		}
		
		sort(coord.begin(), coord.end(), compare);
		int min = 0;
		float sunnySlope = 0;
		int max = 0;
		for (int k = 1; k < coord.size(); k++)
		//for (int k = coord.size() - 1; k > 0; k--)

		{
			if (coord[k].second > max)
			{
				float x, y;
				x = coord[k].first - (float)(coord[k].first - coord[k - 1].first) * (coord[k].second - max) /( coord[k].second - coord[k - 1].second);
				//x = D[i].x - (double)(D[i].x - D[i - 1].x)*(D[i].y - maxH) / (D[i].y - D[i - 1].y);
				y = max;
				sunnySlope += sqrt((x - coord[k].first)*(x - coord[k].first) + (y - coord[k].second)*(y - coord[k].second));
				max = coord[k].second;
			
			}
		}
		//cout << setprecision(2) << fixed << sunnySlope;
		printf("%.2lf\n", sunnySlope);
	}
}