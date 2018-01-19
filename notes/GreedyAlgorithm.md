# Greedy Algorithm

## 什么是贪心算法
>Ref: CLRS Chapter 16
>Ref: https://www.geeksforgeeks.org/greedy-algorithms-set-1-activity-selection-problem/

贪心算法就是这样的算法，它在每一步都做出当时看起来最佳的选择。也就是说，它总是做出局部最优的选择，寄希望这样的选择能导致全局最优解。这种启发式策略并不保证总能找到最优解，但对有些问题确实有效。

一般，我们可以按如下步骤设计贪心算法：
1. 将最优化问题转化为这样的形式：对其做出一次选择后，只剩下一个子问题需要求解。
2. 证明做出贪心选择后，原问题总是存在最优解，即贪心选择总是安全的。
3. 证明做出贪心选择后，剩余的子问题满足性质：其最优解与贪心选择组合即可得到原问题的最优解，这样就得到了最优子结构。

如何证明一个贪心算法能够解一个最优化问题呢？并没有适合所有情况的方法，但**贪心选择性质**和**最优子结构**是两个关键要素。

- 贪心选择性质

**我们可以通过做出局部最优选择来构造全局最优解**。这也是贪心算法与动态规划的不同之处。在动态规划方法中，每个步骤都要进行一次选择，但选择通常依赖于子问题的解。因此，我们通常以一种自底向上的方式求解动态规划问题，先求解较小的子问题，然后是较大的子问题。在贪心算法中，我们总是做出当时看起来最佳的选择，然后求解剩下的的唯一的子问题。贪心算法进行选择时可能依赖之前做出的选择，但不依赖任何将来的选择或是子问题的解。因此，与动态规划先求解子问题，才能进行第一次选择不同，贪心算法在进行第一次选择之前不求解任何子问题。**一个动态规划算法是自底向上进行的，而一个贪心算法通常是自顶向下的，进行一次又一次选择，将给定问题实例变得更小。**

注：如果进行贪心选择时我们不得不考虑众多选择，通常意味着可以改进贪心选择，使其更为高效。例如，活动选择问题中，将活动按结束时间单调递增排序。通过对输入进行预处理或者使用更合适的数据结构（**通常是优先队列**），可以使贪心选择更快速，从而得到更高效的方法。

- 最优子结构

如果一个问题的最优解包含其子问题的最优解，则称此问题具有最优子结构。此性质是能否应用动态规划和贪心算法的关键因素。

**贪心 vs 动态规划**

分数背包问题（可以使用贪心算法），0-1 背包问题（不能使用贪心算法）。

## 活动选择问题

### Activity Selection Problem Statement

You are given n activities with their start and finish times. Select the maximum number of activities that can be performed by a single person, assuming that a person can only work on a single activity at a time.

**Example**
```
Example 1 : Consider the following 3 activities sorted by
by finish time.
     start[]  =  {10, 12, 20};
     finish[] =  {20, 25, 30};
A person can perform at most two activities. The 
maximum set of activities that can be executed 
is {0, 2} [ These are indexes in start[] and 
finish[] ]

Example 2 : Consider the following 6 activities 
sorted by by finish time.
     start[]  =  {1, 3, 0, 5, 8, 5};
     finish[] =  {2, 4, 6, 7, 9, 9};
A person can perform at most four activities. The 
maximum set of activities that can be executed 
is {0, 1, 3, 4} [ These are indexes in start[] and 
finish[] ]
```

### Approach 

The greedy choice is to always pick the next activity whose finish time is least among the remaining activities and the start time is more than or equal to the finish time of previously selected activity. We can sort the activities according to their finishing time so that we always consider the next activity as minimum finishing time activity.

**How does Greedy Choice work for Activities sorted according to finish time?**

Let the give set of activities be S = {1, 2, 3, ..n} and activities be sorted by finish time. The greedy choice is to always pick activity 1. How come the activity 1 always provides one of the optimal solutions. We can prove it by showing that if there is another solution B with first activity other than 1, then there is also a solution A of same size with activity 1 as first activity. Let the first activity selected by B be k, then there always exist A = {B – {k}} U {1}.(Note that the activities in B are independent and k has smallest finishing time among all. Since k is not 1, finish(k) >= finish(1)).

**Implementation**

```c++

#include <vector>
#include <algorithm>
#include <iostream>
#incldue <iterator>

using namespace std;

struct Info {
	int id;
	int start;
	int finish;
};

bool compare(const Info& lhs, const Info& rhs)
{
	return lhs.finish < rhs.finish;
}

vector<int> ASP(vector<int> start, vector<int> finish)
{
	vector<int> result;

	if (start.empty())
		return result;

	// 构造活动信息，对每一个活动封装为结构体 Info
	// 按结束时间对活动排序
	vector<Info> activities;
	for (int i = 0; i < start.size(); ++i)
		activities.push_back({ i + 1, start[i], finish[i] });
	sort(activities.begin(), activities.end(), compare);

	// 贪婪算法
	// The first activity always gets selected
	result.push_back(activities[0].id);
	int pre = 0;
	// Consider rest of the activities
	for (int i = 1; i < activities.size(); ++i)
	{
		if (activities[i].start >= activities[pre].finish)
		{
			pre = i;
			result.push_back(activities[i].id);
		}
	}

	return result;
}

/*

int main()
{
	vector<int> start { 75250, 50074, 43659, 8931, 11273, 27545, 50879, 77924 };
	vector<int> finish { 112960, 114515, 81825, 93424, 54316, 35533, 73383, 160252 };

	auto result = ASP(start, finish);
	copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	return 0;
}

*/

```

## 赫夫曼编码

### Huffman Coding Problem Statement

Huffman coding is a lossless data compression algorithm. The idea is to assign variable-length codes to input characters, lengths of the assigned codes are based on the frequencies of corresponding characters. The most frequent character gets the smallest code and the least frequent character gets the largest code.

### Approach 

There are mainly two major parts in Huffman Coding

1. Build a Huffman Tree from input characters.
2. Traverse the Huffman Tree and assign codes to characters.

**Implementation**

>Ref: CLRS chapter 16
>Ref: https://www.geeksforgeeks.org/greedy-algorithms-set-3-huffman-coding/

```c++
#pragma once

#include <string>
#include <vector>
#include <utility>
#include <queue>
#include <unordered_map>
#include <iostream>

using namespace std;

struct HuffmanNode {
	char data;
	unsigned freq;

	HuffmanNode *left, *right;

	HuffmanNode(char data_, unsigned freq_, HuffmanNode* left_ = nullptr, HuffmanNode* right_ = nullptr) 
		: data(data_), freq(freq_), left(left_), right(right_) { }

	// 为了构造最小优先队列，这里将 < 重载如下（因为C++默认构造大顶堆，所以内部为 freq > rhs.freq）
	bool operator< (const HuffmanNode& rhs) const
	{
		return freq > rhs.freq;
	}
};

// 递归访问 Huffman Tree，输出每个字符的编码
void PrintCodes(const HuffmanNode* root, string str)
{
	if (root == nullptr)
		return;
	if (root->data != '$')
		cout << root->data << ": " << str << endl;
	else
	{
		if (root->left != nullptr)
			PrintCodes(root->left, str + "0");
		if (root->right != nullptr)
			PrintCodes(root->right, str + "1");
	}
}

// 递归访问 Huffman Tree，保存每个字符的编码
void GetHuffmanCodes(const HuffmanNode* root, string str, unordered_map<char, string>& code_results)
{
	if (root == nullptr)
		return;
	if (root->data != '$')
		code_results[root->data] = str;
	else
	{
		if (root->left != nullptr)
			GetHuffmanCodes(root->left, str + "0", code_results);
		if (root->right != nullptr)
			GetHuffmanCodes(root->right, str + "1", code_results);
	}
}

// 输入为待编码的字符以及频率，输出为每个字符以及编码结果
unordered_map<char, string> HuffmanCodes(vector<char> data, vector<unsigned> freq)
{
	unordered_map<char, string> ret;

	// 构造最小优先队列
	priority_queue<HuffmanNode> Q;
	for (int i = 0; i < data.size(); ++i)
	{
		HuffmanNode node(data[i], freq[i]);
		Q.push(node);
	}

	// 构造 Huffman Tree，Tree 的根节点位优先级队列的最后一个元素
	while (Q.size() != 1)
	{
		HuffmanNode *lchild = new HuffmanNode(Q.top());
		Q.pop();
		HuffmanNode *rchild = new HuffmanNode(Q.top());
		Q.pop();

		// 用 '$' 标记中间节点
		Q.push(HuffmanNode('$', lchild->freq + rchild->freq, lchild, rchild));
	}

	// 访问 Huffman Tree，输出每个字符的编码
	//PrintCodes(&Q.top(), "");

	// 访问 Huffman Tree，得到每个字符的编码，TODO
	GetHuffmanCodes(&Q.top(), "", ret);

	return ret;
}

void Test()
{
	vector<char> arr = { 'a', 'b', 'c', 'd', 'e', 'f' };
	vector<unsigned> freq = { 5, 9, 12, 13, 16, 45 };

	auto result = HuffmanCodes(arr, freq);
	for (auto it = result.begin(); it != result.end(); ++it)
		cout << it->first << ": " << it->second << endl;
}
```

