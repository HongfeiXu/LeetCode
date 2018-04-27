#pragma once

/*

21. Merge Two Sorted Lists

Merge two sorted linked lists and return it as a new list. 
The new list should be made by splicing together the nodes of the first two lists.

Example:

Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4

============================================================
Approach1, 向 l1 中插入 l2 中的节点，主要任务在于找到插入位置

Time: O(n+m)
Space: O(1)

============================================================
Approach2, 递归法

把合并两个有序链表 l1，l2的过程看为，找到l1，l2的头结点node_1，然后在余下的节点链表 l1', l2' 中再找头结点node_2，链接到前面的node_1后面，如此递归

============================================================
Approach3, 迭代法

新建一个链表，用dummy为头结点，选择当前l1，l2中较小的节点，链接到dummy链表的末尾，更新l1，l2，直到两个链表中有一个为空，则把另一个链表添加到末尾。

发散：23. Merge k Sorted Lists

*/

#include <algorithm>
#include <iostream>

#include "MyList.h"

using namespace std;

// ====================Approach 1===========================
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
				return l1;
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

// ====================Approach 2===========================
class SolutionRecursive {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
	{
		if (l1 == nullptr)
			return l2;
		if (l2 == nullptr)
			return l1;
		// 若 l1 的第一个节点值较小，则该节点为当前 l1，l2的头结点，递归求解该头结点的下一个节点
		if (l1->val < l2->val)
		{
			l1->next = mergeTwoLists(l1->next, l2);
			return l1;
		}
		else
		{
			l2->next = mergeTwoLists(l1, l2->next);
			return l2;
		}
	}
};

// ====================Approach 3===========================
class SolutionIterative {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
	{
		ListNode* dummy = new ListNode(-1);
		ListNode* curr = dummy;
		while (l1 != nullptr && l2 != nullptr)
		{
			if (l1->val < l2->val)
			{
				curr->next = l1;
				l1 = l1->next;
			}
			else
			{
				curr->next = l2;
				l2 = l2->next;
			}
			curr = curr->next;
		}
		if (l1 == nullptr)
			curr->next = l2;
		else
			curr->next = l1;
		ListNode* result = dummy->next;
		delete dummy;
		return result;
	}
};

void driver()
{
	list<int> l1 = { 1,2,4 };
	list<int> l2 = { 1,3,4 };

	ListNode* ll1 = makeList(l1.begin(), l1.end());
	ListNode* ll2 = makeList(l2.begin(), l2.end());


	SolutionIterative solu;
	ListNode* l3 = solu.mergeTwoLists(ll1, ll2);
	for (ListNode* p = l3; p != nullptr; p = p->next)
	{
		cout << p->val << " ";
	}
	cout << endl;
}