#include <iostream>
using namespace std;

/*Recursively test the input given and see if it is balanced, let the result be returned in the recursion*/

int test(int wl, int dl, int wr, int dr, bool &kill)
{
	int a, b, c, d;
	bool b1 = false, b2 = false;
	if (kill) return 0;

	if (wl == 0)
	{
		cin >> a >> b >> c >> d;
		wl = test(a, b, c, d, b1);	// Skicka in ny input och ny bool. Returnera testvärdet som vikt.
	}

	if (wr == 0)
	{
		cin >> a >> b >> c >> d;
		wr = test(a, b, c, d, b2);
	}

	if (!b1 && !b2 && (wl * dl == wr * dr))
		return wl + wr;

	else
	{
		kill = true;
		return 0;
	}

}

int main()
{
	int n, a, wl, dl, wr, dr;
	bool kill;
	cin >> n;
	while (n--)
	{
		kill = false;
		cin >> wl >> dl >> wr >> dr;

		a = test(wl, dl, wr, dr, kill);

		if (kill || a == 0)
			cout << "NO" << endl;
		else
			cout << "YES" << endl;
		if (n > 0) cout << endl;
	}
}

