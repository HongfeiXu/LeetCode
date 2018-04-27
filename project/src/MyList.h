#pragma once

/*

�Զ������� ListNode���������쵥����

*/

#include <list>
#include <vector>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) { }
};

// ʹ�� std::list �����Զ��������
ListNode* makeList(list<int>::const_iterator b, list<int>::const_iterator e);

// ʹ�� std::vector �����Զ��������
ListNode* vectorToMyList(vector<int>::const_iterator b, vector<int>::const_iterator e);

// �ͷŵ�����ڵ��ڴ�
void destroyList(ListNode* head);

// ����Զ�������
void printList(ListNode* head);
