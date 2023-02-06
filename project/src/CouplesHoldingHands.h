#pragma once

/*

765. Couples Holding Hands

N couples sit in 2N seats arranged in a row and want to hold hands. 
We want to know the minimum number of swaps so that every couple is sitting side by side. 
A swap consists of choosing any two people, then they stand up and switch seats.

The people and seats are represented by an integer from 0 to 2N-1, 
the couples are numbered in order, the first couple being (0, 1), 
the second couple being (2, 3), and so on with the last couple being (2N-2, 2N-1).

The couples' initial seating is given by row[i] being the 
value of the person who is initially sitting in the i-th seat.

Example 1:
Input: row = [0, 2, 1, 3]
Output: 1
Explanation: We only need to swap the second (row[1]) and third (row[2]) person.

Example 2:
Input: row = [3, 2, 0, 1]
Output: 0
Explanation: All couples are already seated side by side.

Note:
len(row) is even and in the range of [4, 60].
row is guaranteed to be a permutation of 0...len(row)-1.

Approach:

Cyclic Swapping

Ref: https://leetcode.com/problems/couples-holding-hands/discuss/113362/JavaC++-O(N)-solution-using-cyclic-swapping

The N couples problem can be solved using exactly the same idea as the N integers problem, (check MiniSwapArray.h)
except now we have different placement requirements: instead of i == row[i], 
we require i == ptn[pos[ptn[row[i]]]], where we have defined two additional arrays ptn and pos:

1. ptn[i] denotes the partner of label i (i can be either a seat or a person) - - ptn[i] = i + 1 if i is even; ptn[i] = i - 1 if i is odd.

2. pos[i] denotes the index of the person with label i in the row array - - row[pos[i]] == i.

The meaning of i == ptn[pos[ptn[row[i]]]] is as follows:

1. The person sitting at seat i has a label row[i], and we want to place him/her next to his/her partner.

2. So we first find the label of his/her partner, which is given by ptn[row[i]].

3. We then find the seat of his/her partner, which is given by pos[ptn[row[i]]].

4. Lastly we find the seat next to his/her partner’s seat, which is given by ptn[pos[ptn[row[i]]]].

Therefore, for each pivot index i, its expected index j is given by ptn[pos[ptn[row[i]]]]. 
As long as i != j, we swap the two elements at index i and j, and continue until the placement requirement is satisfied. 
A minor complication here is that for each swapping operation, we need to swap both the row and pos arrays.

*/

#include <vector>
#include <algorithm>
#include "HelpFunc.h"

using namespace std;

class Solution {
public:
	int minSwapsCouples(vector<int>& row)
	{
		int N = row.size(), result = 0;

		vector<int> pos(N, 0);
		for (int i = 0; i < N; ++i)
			pos[row[i]] = i;

		for (int i = 0; i < N; ++i)
		{
			int j = ptn(pos[ptn(row[i])]);
			while (i != j)
			{
				swap(row[i], row[j]);
				swap(pos[row[i]], pos[row[j]]);
				j = ptn(pos[ptn(row[i])]);
				++result;
			}
		}
		return result;
	}

	// ptn(i) denotes the partner of label i (i can be either a seat or a person) -
	int ptn(int i)
	{
		if (i % 2 == 0)
			return i + 1;
		else
			return i - 1;
	}
};