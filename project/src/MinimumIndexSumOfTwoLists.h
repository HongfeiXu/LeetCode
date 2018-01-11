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
		pair<string, int> curr_least({ "", INT_MAX });	// �洢��ǰ���� least list index sum ����ͬ������

		if (list1.size() > list2.size())
			list1.swap(list2);

		// �Խϳ��� list ���� unordered_map����¼ÿ�����ʵ��±�
		unordered_map<string, int> um;
		for (int i = 0; i < list2.size(); ++i)
			um[list2[i]] = i;

		// �Խ϶̵� list ������
		for (int i = 0; i < list1.size(); ++i)
		{
			// ��� i ���� curr_least.second������Ҫ����Ѱ���ˣ���Ϊ�������϶������и�С�� list index sum
			if(i > curr_least.second)	
				break;

			// Ѱ���Ƿ������ͬ����
			if (um.find(list1[i]) != um.end())
			{
				pair<string, int> temp = { list1[i], i + um[list1[i]] };
				if (curr_least.second > temp.second)	// �����µĸ����ķ��꣬����Ҫ���result��Ȼ������µķ���
				{
					curr_least = temp;
					result.clear();
					result.push_back(curr_least.first);
				}
				else if (curr_least.second == temp.second)	// ���µķ���������ķ��������ͬ��������µķ���
				{
					result.push_back(temp.first);
				}
			}
		}

		return result;
	}
};
