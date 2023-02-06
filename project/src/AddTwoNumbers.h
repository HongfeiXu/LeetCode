#pragma once

/*

2. Add Two Numbers

You are given two non-empty linked lists representing two non-negative integers. 
The digits are stored in reverse order and each of their nodes contain a single digit. 
Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.

Approach_my:

Not Concise.

Approach_v2:

第一种解法太繁琐

我们发现，对于结果的每一位，只要 l1,l2,carry 中存在一个就可以进行计算，因此可以放在一个 while 循环中考虑之。不需要想法一中分段考虑情况。

Concise and Clear.

*/

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) { }
};

class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
	{
		auto p1 = l1;
		auto p2 = l2;
		auto pre1 = p1;
		auto pre2 = p2;

		int full = 0;		// 记录是否需要进位
		while (p1 != nullptr && p2 != nullptr)
		{
			int curr_sum = p1->val + p2->val + full;
			if (curr_sum > 9)
			{
				full = 1;
				p1->val = curr_sum - 10;
				p2->val = curr_sum - 10;
			}
			else
			{
				full = 0;
				p1->val = curr_sum;
				p2->val = curr_sum;
			}
			pre1 = p1;
			pre2 = p2;
			p1 = p1->next;
			p2 = p2->next;
		}

		if (p1 == nullptr && p2 == nullptr)
		{
			if (full == 1)
				pre1->next = new ListNode(1);
			return l1;
		}
		else if (p1 != nullptr)
		{
			while (p1 != nullptr)
			{
				int curr_sum = p1->val + full;
				if (curr_sum > 9)
				{
					full = 1;
					p1->val = curr_sum - 10;
				}
				else
				{
					full = 0;
					p1->val = curr_sum;
				}
				pre1 = p1;
				p1 = p1->next;
			}
			if (full == 1)
				pre1->next = new ListNode(1);
			return l1;
		}
		else
		{
			while (p2 != nullptr)
			{
				int curr_sum = p2->val + full;
				if (curr_sum > 9)
				{
					full = 1;
					p2->val = curr_sum - 10;
				}
				else
				{
					full = 0;
					p2->val = curr_sum;
				}
				pre2 = p2;
				p2 = p2->next;
			}
			if (full == 1)
				pre2->next = new ListNode(1);
			return l2;
		}
	}
};

class Solution_v2 {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
	{
		ListNode* head = new ListNode(0);		// 带头结点的链表
		ListNode* tail = head;
		int carry = 0;	// 进位
		while (l1 || l2 || carry)
		{
			int curr_sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
			tail->next = new ListNode(curr_sum % 10);
			carry = curr_sum / 10;
			tail = tail->next;
			l1 = l1 ? l1->next : nullptr;
			l2 = l2 ? l2->next : nullptr;
		}
		return head->next;
	}
};