#pragma once

/*

321. Create Maximum Number

Related Topics: DP, Greedy

Approach:

1. Create the maximum number of one array, vector<int> maxNumber(vector<int>& nums, int k)
	i: maxNumber_v1, greedy, firstAppear
	ii: maaxNumber, greedy, stack
2. Create maximum number by merging 2 arrays into 1 array, vector<int> merge(vector<int> &nums1, vector<int> &nums2)
(cause the 2 arrays are not sorted, we need a greater() function)
3. we get i digits from nums1, and k-i digits from nums2, we iteration all possible i to get the maximum result

*/

#include "HelpFunc.h"
#include <vector>
#include <array>
#include <cassert>

using namespace std;

class Solution {
private:
	// the rule is: as long as we have a biggest digit,
	// and there are enough digits from this big digit to the end digit to form a k digits number,
	// we add this digit to the result
	// then we seach next suitable biggest digit from the rest right digits.
	vector<int> maxNumber_v1(vector<int>& nums, int k)
	{
		vector<int> currentNums(nums);
		vector<int> ret;

		// from left to right of nums, so we use firstAppear
		vector<int> firstAppear(10, -1);	// for current Nums
		for (int i = currentNums.size() - 1; i >= 0; i--)
		{
			firstAppear[currentNums[i]] = i;
		}

		while (k != 0)
		{
			// from bigger to smaller, so we search from 9 to 0
			for (int i = 9; i >= 0; i--)
			{
				// i exists in currentNums and length is enough for k
				if (firstAppear[i] != -1 && static_cast<int>(currentNums.size()) - firstAppear[i] >= k)
				{
					ret.push_back(i);
					// update currentNums(the left part to firstAppear[i])
					currentNums.erase(currentNums.begin(), currentNums.begin() + firstAppear[i] + 1);

					// update firstAppear
					firstAppear.assign(10, -1);
					for (int j = currentNums.size() - 1; j >= 0; j--)
					{
						firstAppear[currentNums[j]] = j;
					}

					k--;
					break;
				}
			}
		}
		return ret;
	}

	// enlightened by RemoveKDigits removeKdigits_v2
	// use stack to get a maxNumber
	// select k digits from nums to form a biggest number == remove nums.size() - k digits from nus to form a biggest number
	vector<int> maxNumber(vector<int>& nums, int k)
	{
		vector<int> digitStack;
		int digitsNeedRemove = nums.size() - k;

		if (nums.empty() || digitsNeedRemove < 0)
		{
			return digitStack;
		}

		digitStack.push_back(nums[0]);
		for (int i = 1; i < nums.size(); i++)
		{
			while (!digitStack.empty() 
				   && digitStack.back() < nums[i] 
				   && digitsNeedRemove > 0)
			{
				digitStack.pop_back();
				digitsNeedRemove--;
			}
			digitStack.push_back(nums[i]);
		}

		// at last, from bottom to up, in the stack, the first k digits is the result we need
		return vector<int>(digitStack.begin(), digitStack.begin() + k);
	}

	// merge 2 maxNumber to form 1 maxNumber, use all the digits
	// two nums are not sorted, consider some special cases
	// nums1 = { 4,0,0,5 }
	// nums2 = { 7,8,0,0,6 }
	vector<int> merge(vector<int> &nums1, vector<int> &nums2)
	{
		vector<int> ret;
		unsigned i, j;
		for (i = 0, j = 0; i < nums1.size() && j < nums2.size(); )
		{
			// select greater one to append first
			if (greater(nums1, i, nums2, j))
			{
				ret.push_back(nums1[i]);
				i++;
			}
			else
			{
				ret.push_back(nums2[j]);
				j++;
			}
		}
		if (i < nums1.size())
			ret.insert(ret.end(), nums1.begin() + i, nums1.end());
		if (j < nums2.size())
			ret.insert(ret.end(), nums2.begin() + j, nums2.end());

		return ret;
	}

	/*
	used in merge()
	nums1 = {4,0,0,5}, i = 1
	nums2 = {7,8,0,0,6}, j = 2
	nums1 < nums2
	return false

	nums1 = {4,0,0,5}, i = 1
	nums2 = {7,8,0,0}, j = 2
	nums1 > nums2
	return true
	*/
	bool greater(vector<int> &nums1, unsigned i, vector<int> &nums2, unsigned j)
	{
		assert(i >= 0 && j >= 0);
		while (i < nums1.size() && j < nums2.size() && nums1[i] == nums2[j])
		{
			i++;
			j++;
		}

		if (j == nums2.size() || (i < nums1.size() && nums1[i] > nums2[j]))
			return true;
		else
			return false;
	}

public:
	vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k)
	{
		vector<int> result(k, 0);
		vector<int> tempResult;
		vector<int> max1, max2;

		unsigned leftLength;
		unsigned rightLength;
		for (leftLength = 0, rightLength = k; leftLength <= nums1.size(); leftLength++, rightLength--)
		{
			if (leftLength > nums1.size() || rightLength > nums2.size())
				continue;
			max1 = maxNumber(nums1, leftLength);
			max2 = maxNumber(nums2, rightLength);
			tempResult = merge(max1, max2);

			// if tempResult bigger than result, update result
			for (int i = 0; i < k; i++)
			{
				if (result[i] != tempResult[i])
				{
					if (result[i] < tempResult[i])
					{
						result = tempResult;
					}
					break;
				}
			}
		}
		return result;
	}
};

/*

// Test

#include "CreateMaximumNumber.h"
#include "HelpFunc.h"

using namespace std;

int main()
{
Solution solution;

vector<int> nums1 { 2,5,6,4,4,0};
vector<int> nums2 { 7,3,8,0,6,5,7,6,2 };
int k = 15;

vector<int> resutl = solution.maxNumber(nums1, nums2, k);
PrintVector(resutl);

return 0;
}


7 3 8 2 5 6 4 4 0 6 5 7 6 2 0
请按任意键继续. . .


*/