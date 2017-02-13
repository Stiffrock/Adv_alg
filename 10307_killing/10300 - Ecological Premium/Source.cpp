#include<cstdio>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;


int main()
{

	int TestCases, Farmers, SizeOfFarm, NrOfAnimals, EcoValue;
	long long total;
	scanf("%d", &TestCases);
	int TotalArray[20];

	for (int i = 0; i < TestCases; i++)
	{
		scanf("%d", &Farmers);

		total = 0;

		for (int j = 0; j < Farmers; j++)
		{
			scanf("%d %d %d", &SizeOfFarm, &NrOfAnimals, &EcoValue);
			total += (long long)SizeOfFarm * EcoValue;
		}
		TotalArray[i] = total;

	}

	for (int i = 0; i < TestCases; i++)
	{
		printf("%d\n", TotalArray[i]);
	}

	return 0;
}