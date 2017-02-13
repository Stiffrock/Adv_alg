#include<cstdio>
#include<algorithm>
#include<cmath>
#include <iostream>

using namespace std;

struct Point
{
	double x, y;
	double getLength(const Point& a)
	{
		return sqrt((a.x - x)*(a.x - x) + (a.y - y)*(a.y - y));
	}
}point[10000];

bool compare(Point p1, Point p2)
{
	return p1.x < p2.x;
}

int main()
{
	int n, i;
	while (scanf_s("%d", &n) && n)
	{
		for (i = 0; i < n; i++)
			scanf_s("%lf %lf", &point[i].x, &point[i].y);

		sort(point, point + n, compare);


		double min = 10000;
		for (i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
			{
				if (point[i].x + min < point[j].x)	//Denna kollen jag inte hade sist därav timelimit exceeded probably.
					break;

				double length = point[i].getLength(point[j]);

				if (length < min)
					min = length;
			}

		if (min >= 10000)
		{
		//	cout << "INFINITY" << endl;
			puts("INFINITY");
		}
		else
		{
			printf("%.4lf\n", min);
		}
	}
	return 0;
}




//#include <vector>
//#include <iostream>
//#include <algorithm>
//#include <math.h>
//
//using namespace std;
//
//bool compare(pair<int, int> p1, pair<int, int> p2)
//{
//	return p1.first > p2.first;
//}
//
//int compare2(const void * a, const void * b)
//{
//	return (*(int*)a - *(int*)b);
//}
//
//double getLength(const pair<int, int> &v)
//{
//
//	int x = v[j].first - v[i].first;
//	int y = v[j].second - v[i].second;
//	double length = (x*x) + (y*y);
//	return length;	    
//}
//
//int main()
//{
//	int n;
//	while (true)
//	{
//		scanf_s("%d", &n);
//		if (n == 0)
//			break;
//
//		pair<int, int> v[10000];
//		for (int i = 0; i < n; i++)
//		{
//			int x, y;
//			scanf_s("%d%d", &x, &y);
//			pair<int, int> p;
//			p.first = x;
//			p.second = y;
//			v[i] = p;
//		}
//		qsort(v, n, sizeof(double), compare2);
//		double min = 10000;
//
//		for (i = 0; i < n; i++)
//			for (int j = i + 1; j < n; j++)
//			{
//				if (v[i].first + min < v[j].first)
//					break;
//
//				int x = v[j].first - v[i].first;
//				int y = v[j].second - v[i].second;
//				double length = (x*x) + (y*y);
//
//				if (length < min && length != 0)
//				{
//					min = length;
//				}
//			}
//		min = sqrt(min);
//		if (min >= 10000)
//		{
//			cout << "INFINITY";
//		}
//		else
//		{
//			cout << min;
//		}
//	}
//}

