#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <vector>


using namespace std;

/*Uses character unicode to store a value from 0-9 in an array. Then recursively sets the number from 0-9 at that position based on the number of used romans.
 The value is then accesed easily from a string by simply checking against the char of the roman value. */

int romanValues[256]; //Value for different numbers in second phase
int romansAvailable[256]; //List to see if roman number has occured or not
char currentUsedRomans[7]; //Add roman numbers in formula into this list
char startingRoman[3]; //Check which roman number starts in left, right and sum
int usedRomansCount; //check see how many different roman numbers occured. (Uses romansAvailable)

int GetRomanValue(char t)
{
	switch (t)
	{
	case 'I':
		return 1;
	case 'X':
		return 10;
	case 'C':
		return 100;
	case 'M':
		return 1000;
	case 'V':
		return 5;
	case 'L':
		return 50;
	case 'D':
		return 500;
	default:
		break;
	}
}

string CheckRoman(string leftSide, string rightSide, string equals)
{
	int rsV = 0, lsV = 0, eV = 0;


	for (int i = 0; i < rightSide.length(); i++)
	{
		char t = rightSide[i];
		rsV += GetRomanValue(t);
	}
	for (int i = 0; i < leftSide.length(); i++)
	{
		char t = leftSide[i];
		lsV += GetRomanValue(t);
	}
	for (int i = 0; i < equals.length(); i++)
	{
		char t = equals[i];
		eV += GetRomanValue(t);
	}

	int res = rsV + lsV;

	if (res == eV)
		return "Correct";
	else
		return "Incorrect";


}

void DivideString(string input, string& leftSide, string& rightSide, string& equals)
{
	int counter = 0;
	bool rs = false, e = false, first = true;
	for (int i = 0; i < input.length(); i++)
	{
		char t = input[i];

		if (t == '+')
		{
			rs = true;
			first = true;
			counter++;
			continue;
		}
		if (t == '=')
		{
			e = true;
			rs = false;
			first = true;
			counter++;
			continue;
		}

		if (first)
		{
			startingRoman[counter] = input[i];
			first = false;
		}
		if (romansAvailable[input[i]] == 0)
		{
			romansAvailable[input[i]] = 1; //Gets the character ?unicode and uses that as the position in romansAvailable, so you only need to know the actual char to find the value in array.
			currentUsedRomans[usedRomansCount] = input[i]; // Just adds the actual char to a char array keeping track of the roman chars used
			usedRomansCount++;
		}

		if (!rs && !e)
			leftSide.push_back(input[i]);
		if (rs)
			rightSide.push_back(input[i]);
		if (e)
			equals.push_back(input[i]);
	}
}

void ResetLists()
{
	usedRomansCount = 0;
	memset(romansAvailable, 0, sizeof(romansAvailable));
	memset(currentUsedRomans, '\0', sizeof(currentUsedRomans));
	memset(startingRoman, '\0', sizeof(startingRoman));
}


int CalcArabic(string number) //Calculates the Roman number to arabic with the new numbers
{
	int sum = 0;
	for (int i = 0; i < number.size(); i++)	
		sum = sum * 10 + romanValues[number[i]];	// ex romanValue = [1345] -> (0 * 10 + 1 = 1) -> (1 * 10 + 3 = 13) -> (13 * 10 + 4 = 134) -> (134 * 10 + 5 = 1345)
	return sum;
}

bool bSameValue(int value, int index) //Check if there is a roman number with the same value earlier in the iteration
{
	for (int i = 0; i < index; ++i)
		if (romanValues[currentUsedRomans[i]] == value) 
			return true;
	return false;
}

bool bStarting(int index) //Check if the roman number is one of the starting numbers in the equation
{
	for (int i = 0; i < 3; ++i)
		if (startingRoman[i] == currentUsedRomans[index])
			return true;
	return false;
}

int SolveArabicEncoding(int index, int counter, string leftSide, string rightSide, string equals)
{
	/*This will iterate one roman number 10 times, if there is more than one roman number it will recursivly iterate through that aswell*/ 

	int left, right, eq;

	int starter = 0; //See if number should start at 0 or 1
	if (bStarting(index))
		starter = 1;

	for (int i = starter; i < 10; ++i)
	{
		if (!bSameValue(i, index)) //Check if earlier number in iteration does not have the same value
			romanValues[currentUsedRomans[index]] = i;	//If not set the romanValue at position of the unicode char to the iterator number. This is what goes from 0-9 and is used when calculating.
		else
			continue; // If it has the same value then skip this iteration since roman can only represent one value

		left = CalcArabic(leftSide);
		right = CalcArabic(rightSide);
		eq = CalcArabic(equals);

		if (left + right == eq)
			counter++;

		if (index + 1 < usedRomansCount) // This is the recursion that checks if there is more roman chars available, if so start another iteration from 0-9 for that number and sets it in romanValues.  
			counter = SolveArabicEncoding(index + 1, counter, leftSide, rightSide, equals); 

		if (counter > 1)
			return counter;
	}
	return counter;
}

string CheckArabic(string leftSide, string rightSide, string equals)
{
	int counter = SolveArabicEncoding(0, 0, leftSide, rightSide, equals);

	if (counter == 0)
		return "impossible";
	if (counter == 1)
		return "valid";
	if (counter > 1)
		return "ambiguous";
}


int main()
{
	while (true)
	{		
		string leftSide, rightSide, equals, input;
		ResetLists();
		cin >> input;
		if (input[0] == '#')
			break;
		string romanRes, arabicRes;
		DivideString(input, leftSide, rightSide, equals);
		romanRes = CheckRoman(leftSide, rightSide, equals);
		arabicRes = CheckArabic(leftSide, rightSide, equals);
		cout << romanRes << " " << arabicRes << endl;
	}

	return 0;
}