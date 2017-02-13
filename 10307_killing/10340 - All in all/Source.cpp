#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ctype.h>

using namespace std;

bool alg(string s, string t)
{
	int k = 0;
	for (int i = 0; i < t.size(); i++)
	{
		if (s[k] == t[i])
		{
			if (k == s.size() - 1)
				return true;
			else
				k++;
		}
	}
	return false;

}

int main()
{
	while (true)
	{
		string input, s, t;
		getline(cin, input);
		if (input == "\0")
			return false;
		stringstream stream(input);
		stream >> s; stream >> t;
		
		if (alg(s, t))
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
}