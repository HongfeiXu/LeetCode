#pragma once

/*

599. Minimum Index Sum of Two Lists

Suppose Andy and Doris want to choose a restaurant for dinner, and they both have a list of favorite restaurants represented by strings.

You need to help them find out their common interest with the least list index sum. 
If there is a choice tie between answers, output all of them with no order requirement. You could assume there always exists an answer.

Example 1:
Input:
["Shogun", "Tapioca Express", "Burger King", "KFC"]
["Piatti", "The Grill at Torrey Pines", "Hungry Hunter Steakhouse", "Shogun"]
Output: ["Shogun"]
Explanation: The only restaurant they both like is "Shogun".
Example 2:
Input:
["Shogun", "Tapioca Express", "Burger King", "KFC"]
["KFC", "Shogun", "Burger King"]
Output: ["Shogun"]
Explanation: The restaurant they both like and have the least index sum is "Shogun" with index sum 1 (0+1).

Note:
1. The length of both lists will be in the range of [1, 1000].
2. The length of strings in both lists will be in the range of [1, 30].
3. The index is starting from 0 to the list length minus 1.
4. No duplicates in both lists.

*/

#include <vector>
#include <string>
#include <utility>
#include <unordered_map>

using namespace std;

class Solution {
public:
	vector<string> findRestaurant(vector<string>& list1, vector<string>& list2)
	{
		vector<string> result;
		pair<string, int> curr_least({ "", INT_MAX });	// 存储当前具有 least list index sum 的相同饭店名

		if (list1.size() > list2.size())
			list1.swap(list2);

		// 对较长的 list 构建 unordered_map，记录每个单词的下标
		unordered_map<string, int> um;
		for (int i = 0; i < list2.size(); ++i)
			um[list2[i]] = i;

		// 对较短的 list 做迭代
		for (int i = 0; i < list1.size(); ++i)
		{
			// 如果 i 大于 curr_least.second，则不需要继续寻找了，因为接下来肯定不会有更小的 list index sum
			if(i > curr_least.second)	
				break;

			// 寻找是否存在相同单词
			if (um.find(list1[i]) != um.end())
			{
				pair<string, int> temp = { list1[i], i + um[list1[i]] };
				if (curr_least.second > temp.second)	// 发现新的更近的饭店，则需要清空result，然后添加新的饭店
				{
					curr_least = temp;
					result.clear();
					result.push_back(curr_least.first);
				}
				else if (curr_least.second == temp.second)	// 若新的饭店与最近的饭店距离相同，则添加新的饭店
				{
					result.push_back(temp.first);
				}
			}
		}

		return result;
	}
};
