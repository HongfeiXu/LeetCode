#pragma once

/*

239. Sliding Window Maximum

Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. 
You can only see the k numbers in the window. Each time the sliding window moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

 Therefore, return the max sliding window as [3,3,5,5,6,7].

 Note:
 You may assume k is always valid, ie: 1 ≤ k ≤ input array's size for non-empty array.

 Follow up:
 Could you solve it in linear time?

 Approach:

 双端队列的活用啊。

 窗口保存数字在 nums 中的下标，方便判断窗口是否满了。
 并且在每插入一个数字时，保证其左侧的数字大于当前插入的数字，若小于则尾出队。因为在其左边并且不大于它的数字不可能是当前窗口以及之后窗口的最大值。
 这样保证了窗口最左端的数字为当前窗口的最大值。
 另外，若窗口已经满了， 就是说若当前待插入数字为 nums[i]，而窗口最左侧的数字为 nums[i-k]，该数字不在以 nums[i] 为终点的长为k的窗口中，所以需要头出队。

 Time: O(n)
 Time Complexity: O(n). It seems more than O(n) at first look. If we take a closer look, 
 we can observe that every element of array is added and removed at most once. So there are total 2n operations.
 Auxiliary Space: O(k)

*/

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k)
	{
		deque<int> window;		// 存当前窗口中元素在 nums 中的下标
		vector<int> result;

		// 每向窗口中添加一个新数字，需要其左边的数字都大于它，不然就删除，
		for (int i = 0; i < k; ++i)
		{
			while (!window.empty() && nums[window.back()] <= nums[i])
				window.pop_back();
			window.push_back(i);
		}

		// 处理以 nums[i] 为终点的窗口
		for (int i = k; i < nums.size(); ++i)
		{
			// 以 nums[i-1]为终点的窗口的最大值为当前窗口最左边元素的值。
			result.push_back(nums[window.front()]);
			if (i - window.front() == k)	// 窗口已满，需要将最左边的元素删除
				window.pop_front();
			// 添加当前的元素到窗口右边，添加之前，删除窗口中小于等于该元素的数字
			while (!window.empty() && nums[window.back()] <= nums[i])
				window.pop_back();
			window.push_back(i);
		}
		// 添加最后一个窗口的最大数字，若window为空，则说明 nums 为空，此时返回的结果 result 也为空
		if (!window.empty())
			result.push_back(nums[window.front()]);
		
		return result;
	}
};