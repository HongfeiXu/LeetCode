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
 You may assume k is always valid, ie: 1 �� k �� input array's size for non-empty array.

 Follow up:
 Could you solve it in linear time?

 Approach:

 ˫�˶��еĻ��ð���

 ���ڱ��������� nums �е��±꣬�����жϴ����Ƿ����ˡ�
 ������ÿ����һ������ʱ����֤���������ִ��ڵ�ǰ��������֣���С����β���ӡ���Ϊ������߲��Ҳ������������ֲ������ǵ�ǰ�����Լ�֮�󴰿ڵ����ֵ��
 ������֤�˴�������˵�����Ϊ��ǰ���ڵ����ֵ��
 ���⣬�������Ѿ����ˣ� ����˵����ǰ����������Ϊ nums[i]������������������Ϊ nums[i-k]�������ֲ����� nums[i] Ϊ�յ�ĳ�Ϊk�Ĵ����У�������Ҫͷ���ӡ�

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
		deque<int> window;		// �浱ǰ������Ԫ���� nums �е��±�
		vector<int> result;

		// ÿ�򴰿������һ�������֣���Ҫ����ߵ����ֶ�����������Ȼ��ɾ����
		for (int i = 0; i < k; ++i)
		{
			while (!window.empty() && nums[window.back()] <= nums[i])
				window.pop_back();
			window.push_back(i);
		}

		// ������ nums[i] Ϊ�յ�Ĵ���
		for (int i = k; i < nums.size(); ++i)
		{
			// �� nums[i-1]Ϊ�յ�Ĵ��ڵ����ֵΪ��ǰ���������Ԫ�ص�ֵ��
			result.push_back(nums[window.front()]);
			if (i - window.front() == k)	// ������������Ҫ������ߵ�Ԫ��ɾ��
				window.pop_front();
			// ��ӵ�ǰ��Ԫ�ص������ұߣ����֮ǰ��ɾ��������С�ڵ��ڸ�Ԫ�ص�����
			while (!window.empty() && nums[window.back()] <= nums[i])
				window.pop_back();
			window.push_back(i);
		}
		// ������һ�����ڵ�������֣���windowΪ�գ���˵�� nums Ϊ�գ���ʱ���صĽ�� result ҲΪ��
		if (!window.empty())
			result.push_back(nums[window.front()]);
		
		return result;
	}
};