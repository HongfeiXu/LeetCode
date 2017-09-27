#pragma once

/*

167. Two Sum II - Input array is sorted

Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. 
Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution and you may not use the same element twice.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2

Approach My:
numbers is sorted, so we can use Binary Search to find target - numbers[i]

Approach :
bi-direction sweep
COOL

*/

#include <vector>
#include <cassert>

using namespace std;

class Solution {
private:
	int findNum(vector<int>& numbers, int left, int right, int target)
	{
		assert(left <= right);

		int mid = 0;
		while (left <= right)
		{
			mid = (left + right) / 2;
			if (numbers[mid] < target)
				left = mid + 1;
			else if (numbers[mid] > target)
				right = mid - 1;
			else
				return mid;
		}

		return -1;
	}

public:
	vector<int> twoSum(vector<int>& numbers, int target)
	{
		vector<int> result;
		int first = -1;
		int second = -1;

		for (int i = 0; i < numbers.size(); i++)
		{
			first = i;
			second = findNum(numbers, i + 1, numbers.size() - 1, target - numbers[first]);
			if (second != -1)
			{
				result.push_back(first + 1);
				result.push_back(second + 1);
				break;
			}
		}

		return result;
	}

	vector<int> twoSum_v2(vector<int>& numbers, int target)
	{
		vector<int> result;

		int first = 0;
		int second = numbers.size() - 1;

		do 
		{
			if (numbers[first] + numbers[second] == target)
			{
				result.push_back(first + 1);
				result.push_back(second + 1);
				break;
			}
			else if (numbers[first] + numbers[second] < target)
			{
				first++;
			}
			else
			{
				second--;
			}
		} while (1);

		return result;
	}
};