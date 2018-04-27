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

		// l1����Ԫ�ز�����l2����Ԫ�أ����������еĵ�һ��Ԫ��һ���� *l1
		if (l1->val > l2->val)
			swap(l1, l2);
		
		// ��l1���������l2�е�Ԫ��
		ListNode* pre = nullptr;	// pre ָ�� curr ��ǰһ���ڵ�
		ListNode* curr = l1;		// curr ָ��ǰ�ϲ������������������һ���ڵ�
		ListNode* r_node = l2;
		while (r_node != nullptr)
		{
			// Ѱ�� r_node Ҫ���뵽 lhs �е�λ�ã���lhs����Ѱ��һ����r_node��Ľڵ�curr��
			while (curr != nullptr && r_node->val >= curr->val)
			{
				pre = curr;
				curr = curr->next;
			}

			// ����ǰ�ڵ�r_node��������lhs�����µĽڵ㣬��ֱ�ӽ�rhs�ӵ�lhs��β��
			if (curr == nullptr)
			{
				pre->next = r_node;
				break;
			}

			// ����ǰ�ڵ�r_node����pre���棬����preָ��
			pre->next = r_node;
			r_node = r_node->next;
			pre->next->next = curr;
			pre = pre->next;
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
	ListNode B(7);
	ListNode* l2 = &A;
	A.next = &B;

	Solution solu;
	ListNode* l3 = solu.mergeTwoLists(l1, l2);
	for (ListNode* p = l3; p != nullptr; p = p->next)
	{
		cout << p->val << " ";
	}
	cout << endl;
}