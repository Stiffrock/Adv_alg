#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <climits>
#include <cstdio>

using namespace std;
//Dp with memoization
//Börja på pos 0 och gå igenom alla möjliga adjecent, addera dem så att pos 0 får det värdet

int cost[11][110];
int mat[11][110];
int path[11][110];

int N, M;

//int dp(int n, int m) 
//{
//	if (n >= N) // om vi har nått sista tile
//		return 0;
//	if (cost[m][n] != INT_MAX) // om tile redan är besökt, returnera värdet
//		return cost[m][n];
//
//		for (int k = 2; k >= 0; k--)
//		{
//			if (mat[(m + 1) - k][n + 1])
//			{
//				int val = mat[m][n] + dp(n + 1, (m + 1 - k));
//
//				if (cost[m][n] > val || (cost[m][n] == val && path[m][n] > m+1-k)) // För raden i path[m] lagras m's bästa rad sekvens
//				{
//					cost[m][n] = val;
//					path[m][n] = m + 1 - k;
//				}
//			}
//			else //Special property
//			{
//				if (k == 0) //Special property bottom to top
//				{
//					int val = mat[m][n] + dp(n + 1, 0);
//
//					if (cost[m][n] > val || (cost[m][n] == val && path[m][n] > 0))
//					{
//						cost[m][n] = val;
//						path[m][n] = 0;
//					}
//				}
//
//				if (k == 2) //Special property top to bottom
//				{
//
//					int val = mat[m][n] + dp(n + 1, M-1);
//
//					if (cost[m][n] > val || (cost[m][n] == val && path[m][n] > M-1))
//					{
//						cost[m][n] = val;
//						path[m][n] = M-1;
//					}
//				}
//			}
//		}
// 	return cost[m][n];
//}

int dp2(int i, int j) {
	if (j >= N)
		return 0;
	if (cost[i][j] != INT_MAX) 
		return cost[i][j];

	int p[3] = { i - 1, i, i + 1 };

	if (i == 0) 
		p[0] = M - 1;
	if (i == M - 1) 
		p[2] = 0;

	for (int k = 0; k <= 2; k++) {
		int val = mat[i][j] + dp2(p[k], j + 1);

		if (cost[i][j] > val || (cost[i][j] == val && path[i][j] > p[k])) {
			cost[i][j] = val;

			path[i][j] = p[k];
		}
	}
	return cost[i][j];

}

int main()
{
	while (scanf_s("%d %d\n", &M, &N) == 2)
	{	
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 110; j++)
			{
				mat[i][j] = 0;
				cost[i][j] = 0;
			}
		}
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++) 
			{
				int x;
				scanf_s("%d", &x);
				mat[i][j] = x;	
				cost[i][j] = INT_MAX;
			}
		//for (int i = 0; i < M; i++)
		//	for (int j = 0; j < N; j++) {
		//		scanf_s("%d", &mat[i][j]);
		//		cost[i][j] = INT_MAX;
		//	}

		int best = INT_MAX;
		int r = 0;
		for (int i = 0; i < M; i++)
		{
		//	dp(0, i);
			dp2(i, 0);
			if (cost[i][0] < best)
			{
				best = cost[i][0];
				r = i; //använd r till path[r][..] so row-trace läggs i en row i path
			}
		}
		//for (int i = 0; i < N; i++)
		//{
		//	cout << r + 1 << " ";	// +1 för kompensation av offset
		//	r = path[r][i];
		//}
		//cout << "\n" << best << "\n";

		for (int j = 0; j < N; j++) {
			printf(j == 0 ? "%d" : " %d", r + 1);
			r = path[r][j];
		}
		printf("\n%d\n", best);
	}
	return 0;
}