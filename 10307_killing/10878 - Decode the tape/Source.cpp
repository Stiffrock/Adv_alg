#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
	int m[8]{ 128, 64, 32, 16, 8, 4, 2, 1 };
	string input;
	string output;

	while (input[0] != '|')
	{
		getline(cin, input);
	}

	while (input[0] == '|')
	{
		int value = 0;
		{
			char n;
			int k = 0;
			for (int i = 0; i < 11; i++)
			{
				n = input[i];
				if (n == 'o')
				{
					value += m[k];
					k++;
				}
				if (n == ' ')
				{
					k++;
				}

			}

		}
		output.push_back(static_cast<char>(value));

		getline(cin, input);
	}
	cout << output;
	/*cin.get();*/
}