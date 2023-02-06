#pragma once

/*

138. Copy List with Random Pointer

A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.

Approach:
Time: O(n)
额外空间: O(n)
这里需要注意的就是，每次需要拷贝一个节点时，若该节点已经存在，则直接拷贝其地址即可，若该节点还不存在，则需要新建该节点。
使用一个 unordered_map 来建立 原 list 和 新 list 中各个节点的联系。
并且可以根据 unordered_map 来判断节点是否已经在新 list 中存在。（类似于133. Clone Graph）

Approach v2:
Time: O(n)
额外空间: O(n)
递归求解，对于当前访问到的节点，如果在 新 list 中不存在，则新建之，并且递归设置 next 和 random 指针，然后返回当前节点。
若当前节点在 新 list 中存在，则直接返回之。

Approach v3:

在链表内拷贝节点，拷贝指针，然后分解链表为两个。速度较快。
额外空间占用 O(1)
Time: O(N)

Ref: https://leetcode.com/problems/copy-list-with-random-pointer/discuss/43491/A-solution-with-constant-space-complexity-O(1)-and-linear-time-complexity-O(N)

*/

#include <unordered_map>

using namespace std;

// Definition for singly-linked list with a random pointer.
struct RandomListNode {
	int label;
	RandomListNode *next, *random;
	RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {
public:
	RandomListNode *copyRandomList(RandomListNode *head)
	{
		if (head == nullptr)
			return nullptr;
		unordered_map<RandomListNode*, RandomListNode*> hash_table;
		RandomListNode* list_1 = head;
		RandomListNode* list_2 = new RandomListNode(head->label);
		hash_table[list_1] = list_2;
		while (list_1 != nullptr)
		{
			// 如果 list_1->next 在 list_2 中不存在，则需要新建该节点
			if (list_1->next != nullptr && hash_table.find(list_1->next) == hash_table.end())
				hash_table[list_1->next] = new RandomListNode(list_1->next->label);
			// 如果 list_1->random 在 list_2 中不存在，则需要新建该节点
			if (list_1->random != nullptr && hash_table.find(list_1->random) == hash_table.end())
				hash_table[list_1->random] = new RandomListNode(list_1->random->label);
			hash_table[list_1]->next = list_1->next == nullptr ? nullptr : hash_table[list_1->next];
			hash_table[list_1]->random = list_1->random == nullptr ? nullptr : hash_table[list_1->random];
			// 访问下一个节点
			list_1 = list_1->next;
		}
		return list_2;
	}
};

class Solution_v2 {
public:
	unordered_map<RandomListNode*, RandomListNode*> hash_table;

	RandomListNode *copyRandomList(RandomListNode *head)
	{
		// 递归退出条件
		if (head == nullptr)
			return nullptr;
		// 不存在，则新建，若存在则直接返回
		if (hash_table.find(head) == hash_table.end())
		{
			hash_table[head] = new RandomListNode(head->label);
			hash_table[head]->next = copyRandomList(head->next);
			hash_table[head]->random = copyRandomList(head->random);
 		}
		return hash_table[head];
	}
};

class Solution_v3 {
public:
	RandomListNode *copyRandomList(RandomListNode *head)
	{
		if (head == nullptr)
			return head;

		// 拷贝每个节点，并且插入在当前节点的下一个位置
		RandomListNode* p = head;
		while (p != nullptr)
		{
			RandomListNode* next = p->next;
			p->next = new RandomListNode(p->label);
			p->next->next = next;
			p = next;
		}

		// 拷贝 random 指针
		p = head;
		while (p != nullptr)
		{
			if (p->random != nullptr)
				p->next->random = p->random->next;
			p = p->next->next;
		}

		// 拆分 list
		RandomListNode* list_copy = head->next;
		RandomListNode* pre = head;
		RandomListNode* cur = head->next;
		while (cur->next != nullptr)
		{
			pre->next = cur->next;
			pre = pre->next;
			cur->next = cur->next->next;
			cur = cur->next;
		}
		pre->next = cur->next;
		return list_copy;
	}
};