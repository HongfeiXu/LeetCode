# Greedy Algorithm

## ʲô��̰���㷨
>Ref: CLRS Chapter 16
>Ref: https://www.geeksforgeeks.org/greedy-algorithms-set-1-activity-selection-problem/

̰���㷨�����������㷨������ÿһ����������ʱ��������ѵ�ѡ��Ҳ����˵�������������ֲ����ŵ�ѡ�񣬼�ϣ��������ѡ���ܵ���ȫ�����Ž⡣��������ʽ���Բ�����֤�����ҵ����Ž⣬������Щ����ȷʵ��Ч��

һ�㣬���ǿ��԰����²������̰���㷨��
1. �����Ż�����ת��Ϊ��������ʽ����������һ��ѡ���ֻʣ��һ����������Ҫ��⡣
2. ֤������̰��ѡ���ԭ�������Ǵ������Ž⣬��̰��ѡ�����ǰ�ȫ�ġ�
3. ֤������̰��ѡ���ʣ����������������ʣ������Ž���̰��ѡ����ϼ��ɵõ�ԭ��������Ž⣬�����͵õ��������ӽṹ��

���֤��һ��̰���㷨�ܹ���һ�����Ż������أ���û���ʺ���������ķ�������**̰��ѡ������**��**�����ӽṹ**�������ؼ�Ҫ�ء�

- ̰��ѡ������

**���ǿ���ͨ�������ֲ�����ѡ��������ȫ�����Ž�**����Ҳ��̰���㷨�붯̬�滮�Ĳ�֮ͬ�����ڶ�̬�滮�����У�ÿ�����趼Ҫ����һ��ѡ�񣬵�ѡ��ͨ��������������Ľ⡣��ˣ�����ͨ����һ���Ե����ϵķ�ʽ��⶯̬�滮���⣬������С�������⣬Ȼ���ǽϴ�������⡣��̰���㷨�У���������������ʱ��������ѵ�ѡ��Ȼ�����ʣ�µĵ�Ψһ�������⡣̰���㷨����ѡ��ʱ��������֮ǰ������ѡ�񣬵��������κν�����ѡ�����������Ľ⡣��ˣ��붯̬�滮����������⣬���ܽ��е�һ��ѡ��ͬ��̰���㷨�ڽ��е�һ��ѡ��֮ǰ������κ������⡣**һ����̬�滮�㷨���Ե����Ͻ��еģ���һ��̰���㷨ͨ�����Զ����µģ�����һ����һ��ѡ�񣬽���������ʵ����ø�С��**

ע���������̰��ѡ��ʱ���ǲ��ò������ڶ�ѡ��ͨ����ζ�ſ��ԸĽ�̰��ѡ��ʹ���Ϊ��Ч�����磬�ѡ�������У����������ʱ�䵥����������ͨ�����������Ԥ�������ʹ�ø����ʵ����ݽṹ��**ͨ�������ȶ���**��������ʹ̰��ѡ������٣��Ӷ��õ�����Ч�ķ�����

- �����ӽṹ

���һ����������Ž����������������Ž⣬��ƴ�������������ӽṹ�����������ܷ�Ӧ�ö�̬�滮��̰���㷨�Ĺؼ����ء�

**̰�� vs ��̬�滮**

�����������⣨����ʹ��̰���㷨����0-1 �������⣨����ʹ��̰���㷨����

## �ѡ������

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

Let the give set of activities be S = {1, 2, 3, ..n} and activities be sorted by finish time. The greedy choice is to always pick activity 1. How come the activity 1 always provides one of the optimal solutions. We can prove it by showing that if there is another solution B with first activity other than 1, then there is also a solution A of same size with activity 1 as first activity. Let the first activity selected by B be k, then there always exist A = {B �C {k}} U {1}.(Note that the activities in B are independent and k has smallest finishing time among all. Since k is not 1, finish(k) >= finish(1)).

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

	// ������Ϣ����ÿһ�����װΪ�ṹ�� Info
	// ������ʱ��Ի����
	vector<Info> activities;
	for (int i = 0; i < start.size(); ++i)
		activities.push_back({ i + 1, start[i], finish[i] });
	sort(activities.begin(), activities.end(), compare);

	// ̰���㷨
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

## �շ�������

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

	// Ϊ�˹�����С���ȶ��У����ｫ < �������£���ΪC++Ĭ�Ϲ���󶥶ѣ������ڲ�Ϊ freq > rhs.freq��
	bool operator< (const HuffmanNode& rhs) const
	{
		return freq > rhs.freq;
	}
};

// �ݹ���� Huffman Tree�����ÿ���ַ��ı���
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

// �ݹ���� Huffman Tree������ÿ���ַ��ı���
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

// ����Ϊ��������ַ��Լ�Ƶ�ʣ����Ϊÿ���ַ��Լ�������
unordered_map<char, string> HuffmanCodes(vector<char> data, vector<unsigned> freq)
{
	unordered_map<char, string> ret;

	// ������С���ȶ���
	priority_queue<HuffmanNode> Q;
	for (int i = 0; i < data.size(); ++i)
	{
		HuffmanNode node(data[i], freq[i]);
		Q.push(node);
	}

	// ���� Huffman Tree��Tree �ĸ��ڵ�λ���ȼ����е����һ��Ԫ��
	while (Q.size() != 1)
	{
		HuffmanNode *lchild = new HuffmanNode(Q.top());
		Q.pop();
		HuffmanNode *rchild = new HuffmanNode(Q.top());
		Q.pop();

		// �� '$' ����м�ڵ�
		Q.push(HuffmanNode('$', lchild->freq + rchild->freq, lchild, rchild));
	}

	// ���� Huffman Tree�����ÿ���ַ��ı���
	//PrintCodes(&Q.top(), "");

	// ���� Huffman Tree���õ�ÿ���ַ��ı��룬TODO
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

