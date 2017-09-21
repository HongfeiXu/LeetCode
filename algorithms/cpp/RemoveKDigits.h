#pragma once

/*

402. Remove K Digits

Related Topics: Stack, Greedy

Approach my:

remove k digits to get smallest number == select number.length-k digits to get smallest number

Approach Greedy using Stack(COOL):

To get a smallest number, we should put smaller digit in higher position.
So, we need to remove digit with bigger number in higher position.

*/

#include <string>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;


class Solution {
private:
	// select k digit from digits, to form a minimum number by not change the order.
	vector<int> minNumber(vector<int> &digits, unsigned k)
	{
		vector<int> currentDigits(digits);	// init current digits
		vector<int> result;

		vector<int> firstAppear(10, -1);
		for (int i = currentDigits.size() - 1; i >= 0; i--)
		{
			firstAppear[currentDigits[i]] = i;
		}

		while (k != 0)
		{
			for (int i = 0; i <= 9; i++)
			{
				if (firstAppear[i] != -1 && (currentDigits.size() - firstAppear[i] >= k))
				{
					result.push_back(i);
					currentDigits.erase(currentDigits.begin(), currentDigits.begin() + firstAppear[i] + 1);
					
					// update firstAppear for currentDigits
					firstAppear.assign(10, -1);
					for (int i = currentDigits.size() - 1; i >= 0; i--)
					{
						firstAppear[currentDigits[i]] = i;
					}

					k--;
					break;
				}
			}
		}

		return result;
	}

public:
	string removeKdigits(string num, int k)
	{
		vector<int> digits;
		for (unsigned i = 0; i < num.size(); i++)
		{
			digits.push_back(num[i] - '0');
		}

		vector<int> minDigits = minNumber(digits, num.size() - k);
		
		// construct result, remember to skip leading zero
		string result("");
		unsigned j = 0;
		while (!minDigits.empty() && minDigits[j] == 0)
			++j;
		for (unsigned i = j; i < minDigits.size(); i++)
		{
			result.append(to_string(minDigits[i]));
		}

		if (result.empty())
			result.append("0");

		return result;
	}

	string removeKdigits_v2(string num, int k)
	{
		int digitsCnt = num.size() - k;
		vector<char> stack;
		
		// k keeps track of how many characters we can remove
		// if the previous character in stack is larger than the current one
		// then removing it will get a smaller number
		// but we can only do so when k is larger than 0

		// push to stack, compare and remove.
		if (num.empty() || digitsCnt == 0)
			return string("0");
		stack.push_back(num[0]);
		for (unsigned i = 1; i < num.size(); i++)		
		{
			char c = stack.back();
			while (num[i] < c && k > 0)
			{
				stack.pop_back();
				k--;
				// if stack is empty, out while loop
				if(stack.empty())
					break;
				else
					c = stack.back();
			}
			stack.push_back(num[i]);
		}

		// pick first digitsCnt digits from bottom to up of the stack
		vector<char> digits(stack.begin(), stack.begin() + digitsCnt);
		unsigned j = 0;
		while (!digits.empty() && digits[j] == '0')	// skip leading zero
			++j;

		// construct result
		string result(digits.begin() + j, digits.end());
		if (result.empty())
			return string("0");
		return result;
	}
};