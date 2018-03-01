#pragma once

/*

138. Copy List with Random Pointer

A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.

Approach:
Time: O(n)
����ռ�: O(n)
������Ҫע��ľ��ǣ�ÿ����Ҫ����һ���ڵ�ʱ�����ýڵ��Ѿ����ڣ���ֱ�ӿ������ַ���ɣ����ýڵ㻹�����ڣ�����Ҫ�½��ýڵ㡣
ʹ��һ�� unordered_map ������ ԭ list �� �� list �и����ڵ����ϵ��
���ҿ��Ը��� unordered_map ���жϽڵ��Ƿ��Ѿ����� list �д��ڡ���������133. Clone Graph��

Approach v2:
Time: O(n)
����ռ�: O(n)
�ݹ���⣬���ڵ�ǰ���ʵ��Ľڵ㣬����� �� list �в����ڣ����½�֮�����ҵݹ����� next �� random ָ�룬Ȼ�󷵻ص�ǰ�ڵ㡣
����ǰ�ڵ��� �� list �д��ڣ���ֱ�ӷ���֮��

Approach v3:

�������ڿ����ڵ㣬����ָ�룬Ȼ��ֽ�����Ϊ�������ٶȽϿ졣
����ռ�ռ�� O(1)
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
			// ��� list_1->next �� list_2 �в����ڣ�����Ҫ�½��ýڵ�
			if (list_1->next != nullptr && hash_table.find(list_1->next) == hash_table.end())
				hash_table[list_1->next] = new RandomListNode(list_1->next->label);
			// ��� list_1->random �� list_2 �в����ڣ�����Ҫ�½��ýڵ�
			if (list_1->random != nullptr && hash_table.find(list_1->random) == hash_table.end())
				hash_table[list_1->random] = new RandomListNode(list_1->random->label);
			hash_table[list_1]->next = list_1->next == nullptr ? nullptr : hash_table[list_1->next];
			hash_table[list_1]->random = list_1->random == nullptr ? nullptr : hash_table[list_1->random];
			// ������һ���ڵ�
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
		// �ݹ��˳�����
		if (head == nullptr)
			return nullptr;
		// �����ڣ����½�����������ֱ�ӷ���
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

		// ����ÿ���ڵ㣬���Ҳ����ڵ�ǰ�ڵ����һ��λ��
		RandomListNode* p = head;
		while (p != nullptr)
		{
			RandomListNode* next = p->next;
			p->next = new RandomListNode(p->label);
			p->next->next = next;
			p = next;
		}

		// ���� random ָ��
		p = head;
		while (p != nullptr)
		{
			if (p->random != nullptr)
				p->next->random = p->random->next;
			p = p->next->next;
		}

		// ��� list
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