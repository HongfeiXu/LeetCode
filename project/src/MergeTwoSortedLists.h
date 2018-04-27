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

		// l1的首元素不大于l2的首元素，则新链表中的第一个元素一定是 *l1
		if (l1->val > l2->val)
			swap(l1, l2);
		
		// 向l1中逐个插入l2中的元素
		ListNode* pre = nullptr;	// pre 指向 curr 的前一个节点
		ListNode* curr = l1;		// curr 指向当前合并后有序的新链表的最后一个节点
		ListNode* r_node = l2;
		while (r_node != nullptr)
		{
			// 寻找 r_node 要插入到 lhs 中的位置（在lhs中找寻第一个比r_node大的节点curr）
			while (curr != nullptr && r_node->val >= curr->val)
			{
				pre = curr;
				curr = curr->next;
			}

			// 若当前节点r_node大于所有lhs中余下的节点，则直接将rhs接到lhs的尾部
			if (curr == nullptr)
			{
				pre->next = r_node;
				break;
			}

			// 将当前节点r_node插入pre后面，更新pre指针
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