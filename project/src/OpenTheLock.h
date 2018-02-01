#pragma once

/*

752. Open the Lock

You have a lock in front of you with 4 circular wheels. 
Each wheel has 10 slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'. 
The wheels can rotate freely and wrap around: for example we can turn '9' to be '0', or '0' to be '9'. 
Each move consists of turning one wheel one slot.

The lock initially starts at '0000', a string representing the state of the 4 wheels.

You are given a list of deadends dead ends, meaning if the lock displays any of these codes, 
the wheels of the lock will stop turning and you will be unable to open it.

Given a target representing the value of the wheels that will unlock the lock, 
return the minimum total number of turns required to open the lock, or -1 if it is impossible.

Example 1:
Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
Output: 6
Explanation:
A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
because the wheels of the lock become stuck after the display becomes the dead end "0102".

Example 2:
Input: deadends = ["8888"], target = "0009"
Output: 1
Explanation:
We can turn the last wheel in reverse to move from "0000" -> "0009".

Example 3:
Input: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
Output: -1
Explanation:
We can't reach the target without getting stuck.

Example 4:
Input: deadends = ["0000"], target = "8888"
Output: -1

Note:
The length of deadends will be in the range [1, 500].
target will not be in the list deadends.
Every string in deadends and the string target will be a string of 4 digits from the 10,000 possibilities '0000' to '9999'.

Approach:
Ref:https://leetcode.com/problems/open-the-lock/solution/
�����⿴Ϊͼ�����·�����⡣
ͼ���� 10000 ���ڵ㣬�ڵ�Ĺؼ���Ϊ '0000' �� '9999' ��Щ�ַ�����
��������ַ���֮�����ֻ��һλ���������ŵģ�'0' �� '9' ���Ҳֻ��һλ���������������ַ��������� deadend��������ͨ�ġ�
���գ�������Ҫ�ҳ��� '0000' ��Ŀ�� 'abcd' �����·����ȷ���䳤�ȣ�������������򷵻� -1��

�ܽ����£�
Every node has 8 edges at most. The nodes in dead ends cannot be visited. Find the shortest path from the initial node to the target.

ʹ�� BFS ������
TODO...
�����ĿҪ����������Ĳ����أ�����������ڽ������У����ؽ�����ÿһ���������ǲ�������
�Ǿ���Ҫ����������������

*/

#include <vector>
#include <string>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
	int openLock(vector<string>& deadends, string target)
	{
		unordered_set<string> dds(deadends.begin(), deadends.end());
		// ����ʼ�ڵ�Ϊ deadends����ֱ�ӷ��� -1
		if (dds.find("0000") != dds.end())
			return -1;
		queue<string> bfs;				// ���й���������������в������޷������ deadends �ڵ�
		unordered_set<string> visited;	// �����Լ����ʹ��ýڵ㣬ʹ��֮�󲻻���η���
		bfs.push("0000");
		visited.insert("0000");
		int result = 0;
		while (!bfs.empty())
		{
			int curr_layer_size = bfs.size();
			// ���ӵ�ǰ��ڵ㣬�����һ��ڵ�
			for (int i = 0; i < curr_layer_size; ++i)
			{
				string curr_node = bfs.front();
				bfs.pop();
				// ����Ŀ�꣬���ؾ���
				if (curr_node == target)
					return result;
				vector<string> neighbor_nodes = getNeighbors(curr_node);
				for (auto node : neighbor_nodes)
				{
					if (dds.find(node) == dds.end() && visited.find(node) == visited.end())
					{
						bfs.push(node);
						visited.insert(node);
					}
				}
			}
			// ��һ�ε���ʱ�Ѿ�����һ�㣬����ֵ����1
			++result;
		}
		return -1;
	}

	// ���һ���ڵ�İ˸���ѡ�ڽӽڵ�
	vector<string> getNeighbors(const string& node)
	{
		vector<string> result;
		for (int i = 0; i < 4; ++i)
		{
			string temp = node;
			temp[i] = (node[i] - '0' + 1) % 10 + '0';
			result.push_back(temp);
			temp[i] = (node[i] - '0' - 1 + 10) % 10 + '0';
			result.push_back(temp);
		}
		return result;
	}
};
