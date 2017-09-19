#pragma once

/*

670. Maximum Swap

data: 2017.9.16


Given a non-negative integer, you could swap two digits at most once to get the maximum valued number. 
Return the maximum valued number you could get.


Approach #1: Sort and Compare to find the leftPos, rightPos and Swap [Accepted]

Algorithm:
num:		1993
sortedNum:	9931
			|
so we should swap 1 and 9
leftPos = 0
rightPos = ?

1993
  |
rightPos = 2

swap()

1993->9931


Approach #3:  Greedy [Accepted]

Intuition:
At each digit of the input number in order, 
if there is a larger digit that occurs later, 
we know that the best swap must occur with the digit we are currently considering.

Algorithm:
We will compute last[d] = i, the index i of the last occurrence of digit d (if it exists).
Afterwards, when scanning the number from left to right, 
if there is a larger digit in the future, we will swap it with the largest such digit; 
if there are multiple such digits, we will swap it with the one that occurs the latest.

see maximumSwap_v4(int num)

*/

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>	// std::greater
#include <iterator>
#include <sstream>

using namespace std;

class Solution {
public:
	int maximumSwap(int num)
	{
		// 1. num->numString->numDigits
		string numString(to_string(num));
		vector<int> numDigits;

		for (unsigned i = 0; i < numString.size(); i++)
		{
			// get every digit from the numString to numDigits
			numDigits.push_back(numString[i] - '0');	// better way?
		}

		// 2. get sortedNumDigits
		vector<int> sortedNumDigits(numDigits);
		sort(sortedNumDigits.begin(), sortedNumDigits.end(), greater<int>());

		int leftPos = -1;
		int rightPos = -1;
		// 3. Compare each digit in numDigits and sortedNumDigits
		// and find the first different digit position
		for (unsigned i = 0; i < numDigits.size(); i++)
		{
			if (numDigits[i] != sortedNumDigits[i])
			{
				leftPos = i;
				break;
			}
		}
		// if each pair of digits is identical, no need to swap
		if (leftPos == -1)
		{
			return num;
		}

		// 4. find the bigger digit position in numDigits from end to start
		// and swap it
		auto iter = find(numDigits.rbegin(), numDigits.rend(), sortedNumDigits[leftPos]);
		rightPos = iter.base() - numDigits.begin() - 1;	// iter and iter.base()

		swap(numDigits[leftPos], numDigits[rightPos]);

		// 4. numDigits->maxNumString->maxNum
		// better way?
		string maxNumString(numDigits.size(), 0);
		transform(numDigits.begin(), numDigits.end(), maxNumString.begin(),
				  [](int n) { return static_cast<unsigned char> (n + '0'); });
		int maxNum;
		maxNum = stoi(maxNumString);

		return maxNum;
	}

	// Brute Force
	int maximumSwap_v2(int num)
	{
		string numString(to_string(num));
		string maxNumString(numString);
		for (unsigned i = 0; i < numString.size(); i++)
		{
			for (unsigned j = i + 1; j < numString.size(); j++)
			{
				swap(numString[i], numString[j]);	// 交换
				for (unsigned k = 0; k < numString.size(); k++)
				{
					// 从高位到低位，发现有一位数字不相同
					if (numString[k] != maxNumString[k])
					{
						// 如果新的 numString 这一位大于 maxNumString
						// 则更新 maxNumString
						if (numString[k] > maxNumString[k])
						{
							maxNumString = numString;
						}
						break;
					}
				}
				swap(numString[i], numString[j]);	// 复原
			}
		}
		return stoi(maxNumString);
	}

	// Greedy
	int maximumSwap_v3(int num)
	{
		string numString(to_string(num));
		string maxNumString(numString);

		int leftPos = -1;
		int rightPos = -1;

		for (unsigned i = 0; i < numString.size() - 1; i++)
		{
			for (unsigned j = numString.size() - 1; j > i; j--)
			{
				if (maxNumString[i] < maxNumString[j])
				{
					maxNumString[i] = maxNumString[j];
					leftPos = i;
					rightPos = j;
				}
			}
			if (rightPos != -1)
			{
				maxNumString[rightPos] = numString[leftPos];
				break;
			}
		}
		return stoi(maxNumString);
	}

	// SO COOL-----------------------------------
	// Greedy_v2
	int maximumSwap_v4(int num)
	{
		string numString(to_string(num));
		int lastAppear[10];					// 记录数字0~9在num中最后出现的位置
		memset(lastAppear, -1, sizeof(lastAppear));
		for (unsigned i = 0; i < numString.size(); i++)
		{
			lastAppear[numString[i] - '0'] = i;
		}

		for (unsigned i = 0; i < numString.size(); i++)
		{
			for (unsigned j = 9; j > numString[i] - '0'; j--)
			{
				if (lastAppear[j] > static_cast<int>(i))
				{
					swap(numString[i], numString[lastAppear[j]]);
					return stoi(numString);
				}
			}
		}
		return num;
	}
};

