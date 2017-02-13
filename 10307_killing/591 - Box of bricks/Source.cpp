#include <string>
#include <sstream>
#include <iostream>

using namespace std;

int main()
{
	int moveArray[50];
	int counter = 0;
	while (true)
	{

		int stacks = 0;
		int heights[50];
		int k = 0;
		int blocks = 0;
		int targetHeight = 0;

		scanf("%d", &stacks);
		if (stacks == 0)
			break;

		string input;
		cin.get();
		getline(std::cin, input);
		stringstream stream(input);

		while (true)
		{
			int n;
			stream >> n;
			if (!stream)
				break;

			heights[k] = n;
			blocks += n;
			k++;
		}
		targetHeight = blocks / stacks;

		int moves = 0;
		for (int i = 0; i < stacks; i++)
		{
			int currentStack = heights[i];

			if (heights[i] > targetHeight)
				moves += currentStack - targetHeight;
			else if (heights[i] <= targetHeight)
				moves += targetHeight - currentStack;
		}

		moves = moves / 2;

		moveArray[counter] = moves;
		counter++;
	}

	for (int i = 0; i < counter; i++)
	{
		cout << "Set #" << i + 1 << endl << "The minimum number of moves is " << moveArray[i] << "." << endl << "\n";
	}
	return 0;
}