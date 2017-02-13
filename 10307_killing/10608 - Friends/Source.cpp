#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;


static int parentArray[50000];
static int elementsArray[50000];

int maximum;



void MakeSet(int n)
{
	for (int i = 0; i < n; i++)
	{
		parentArray[i] = i;  // 1, 2, 3, 4, 5... n
		elementsArray[i] = 1; // 1, 1, 1, 1, 1... n
	}
}

int FindSet(int x)
{
	if (parentArray[x] == x)
	{
		return x;
	}
	return FindSet(parentArray[x]);

}

bool SameSet(int x, int y)
{
	return FindSet(x) == FindSet(y); // kollar så att det inte är dubletter, (2, 1) (1, 2)
}

void Link(int x, int y)
{
	if (!SameSet(x, y))
	{
		parentArray[x] = y;
		elementsArray[y] += elementsArray[x];
		maximum = (maximum < elementsArray[y]) ? elementsArray[y] : maximum;
	}
}

// Union two sets.
// First find their representative and link them.
void Union(int x, int y) {
	Link(FindSet(x), FindSet(y));
}

int main() {

	int n, m, a, b;

	int times;
	scanf_s("%d", &times);	// scanf_s


	while (times--) {

		scanf_s("%d %d", &n, &m);	// scanf_s

		MakeSet(n);		// Gör en array med n platser

		maximum = 1;

		while (m--) {
			scanf_s("%d %d", &a, &b); // scanf_s
			Union(a, b);
		}

		cout << maximum << endl;
		cin.get();
	}
	cin.get();
	return 0;
}
