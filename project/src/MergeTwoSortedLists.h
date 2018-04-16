#pragma once

/*

21. Merge Two Sorted Lists

Merge two sorted linked lists and return it as a new list. 
The new list should be made by splicing together the nodes of the first two lists.

Example:

Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4

*/

#include <algorithm>
#include <iostream>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) { }
};

class Solution {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
	{
		if (l1 == nullptr)
			return l2;
		if (l2 == nullptr)
			return l1;

		// l1的首元素不大于l2的首元素
		if (l1->val > l2->val)
			swap(l1, l2);
		
		// 向l1中逐个插入l2中的元素
		ListNode* curr_l1 = l1;
		ListNode* curr_l2 = l2;
		ListNode* next_l2 = l2->next;
		while (curr_l2 != nullptr)
		{
			while (curr_l1->next != nullptr && curr_l1->next->val <= curr_l2->val)
			{
				curr_l1 = curr_l1->next;
			}
			// 如果 l1 中不存在比 curr_l2->val 大的元素，则直接把 l2 余下的元素连接到 l1 的末端
			if (curr_l1->next == nullptr)
			{
				curr_l1->next = curr_l2;
				return l1;
			}
			// 将 curr_l2 插入到 curr_l1 的后面
			curr_l2->next = curr_l1->next;
			curr_l1->next = curr_l2;
			// 更新 curr_l1, curr_l2, next_l2
			curr_l1 = curr_l1->next;
			curr_l2 = next_l2;
			next_l2 = curr_l2 == nullptr ? nullptr : curr_l2->next;
		}
		return l1;
	}
};

void driver()
{
	ListNode a(1);
	ListNode b(2);
	ListNode c(9);

	ListNode* l1 = &a;
	a.next = &b;
	b.next = &c;

	ListNode A(5);
	ListNode* l2 = &A;

	Solution solu;
	ListNode* l3 = solu.mergeTwoLists(l1, l2);
	for (ListNode* p = l3; p != nullptr; p = p->next)
	{
		cout << p->val << " ";
	}
	cout << endl;
}