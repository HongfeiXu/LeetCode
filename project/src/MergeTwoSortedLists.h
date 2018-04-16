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

		// l1����Ԫ�ز�����l2����Ԫ��
		if (l1->val > l2->val)
			swap(l1, l2);
		
		// ��l1���������l2�е�Ԫ��
		ListNode* curr_l1 = l1;
		ListNode* curr_l2 = l2;
		ListNode* next_l2 = l2->next;
		while (curr_l2 != nullptr)
		{
			while (curr_l1->next != nullptr && curr_l1->next->val <= curr_l2->val)
			{
				curr_l1 = curr_l1->next;
			}
			// ��� l1 �в����ڱ� curr_l2->val ���Ԫ�أ���ֱ�Ӱ� l2 ���µ�Ԫ�����ӵ� l1 ��ĩ��
			if (curr_l1->next == nullptr)
			{
				curr_l1->next = curr_l2;
				return l1;
			}
			// �� curr_l2 ���뵽 curr_l1 �ĺ���
			curr_l2->next = curr_l1->next;
			curr_l1->next = curr_l2;
			// ���� curr_l1, curr_l2, next_l2
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