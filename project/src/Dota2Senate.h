#pragma once

/*

649. Dota2 Senate

In the world of Dota2, there are two parties: the Radiant and the Dire.

The Dota2 senate consists of senators coming from two parties. 
Now the senate wants to make a decision about a change in the Dota2 game. 
The voting for this change is a round-based procedure. 
In each round, each senator can exercise one of the two rights:

1. Ban one senator's right:
	A senator can make another senator lose all his rights in this and all the following rounds.
2. Announce the victory:
	If this senator found the senators who still have rights to vote are all from the same party, 
	he can announce the victory and make the decision about the change in the game.

Given a string representing each senator's party belonging. 
The character 'R' and 'D' represent the Radiant party and the Dire party respectively. 
Then if there are n senators, the size of the given string will be n.

The round-based procedure starts from the first senator to the last senator in the given order. 
This procedure will last until the end of voting. All the senators who have lost their rights will be skipped during the procedure.

Suppose every senator is smart enough and will play the best strategy for his own party, 
you need to predict which party will finally announce the victory and make the change in the Dota2 game. 
The output should be Radiant or Dire.

Example 1:
Input: "RD"
Output: "Radiant"
Explanation: The first senator comes from Radiant and he can just ban the next senator's right in the round 1.
And the second senator can't exercise any rights any more since his right has been banned.
And in the round 2, the first senator can just announce the victory since he is the only guy in the senate who can vote.

Example 2:
Input: "RDD"
Output: "Dire"
Explanation:
The first senator comes from Radiant and he can just ban the next senator's right in the round 1.
And the second senator can't exercise any rights anymore since his right has been banned.
And the third senator comes from Dire and he can ban the first senator's right in the round 1.
And in the round 2, the third senator can just announce the victory since he is the only guy in the senate who can vote.

Note:
The length of the given string will in the range [1, 10,000].

Approach:

����ÿһ�ַ��ԣ����ڵ�ǰ����Ա a����Ϊ Radiant ��Ա���������� Dire �еĲ���Ա���з���Ȩ���� a ����ʹȨ��1��ban ��Dire ����һ��Ҫ���Եĳ�Ա��
����Dire �еĲ���Ա��û�з���Ȩ���� a �����ɹ�������ǰ����Ա a Ϊ Dire����������Ƶ�ѡ��

O(n^2)

Approach_v2:
COOLCOOLCOOL
Ref: https://discuss.leetcode.com/topic/97671/java-c-very-simple-greedy-solution-with-explanation

This is obliviously a greedy algorithm problem. 
Each senate R must ban its next closest senate D who is from another party, 
or else D will ban its next senate from R's party.

The idea is to use two queues to save the index of each senate from R's and D's parties, respectively. 
During each round, we delete the banned senate's index; and plus the remainning senate's index with n(the length of the input string senate), 
then move it to the back of its respective queue.���������ʹ�õ�ǰ���緢�Ե��Ǹ�����Ա���Դ��ڣ����Ҽ���n����ӵ�����ĩβ���ȴ���һ�ַ��ԣ�

�Զ��е�ʹ�ú����棬���ұȽϺ��n����ӵ�����ĩβ�ȴ���һ�ַ��Ե�˼·�ܿᡣ

*/

#include <string>
#include <queue>

using namespace std;

class Solution {
public:
	string predictPartyVictory(string senate)
	{
		int i = 0;
		int len = senate.size();
		while (1)
		{
			if (senate[i] == 'R')
			{
				int next_D = next(senate, 'D', i);	// ������һ�����Ե� R
				if (next_D == -1)	// �������ܹ����Ե� R
					return "Radiant";
				else                // �����ܹ����Ե�R
					senate[next_D] = 'X';			// ban �� R ��Ȩ��
			}
			else if (senate[i] == 'D')
			{
				int next_R = next(senate, 'R', i);
				if (next_R == -1)
					return "Dire";
				else
					senate[next_R] = 'X';
			}

			i = (i + 1) % len;
		}
	}

	// ������һ��Ҫ���Ե� target ��Ӫ�Ĳ���Ա
	int next(const string& senate, char target, int pos)
	{
		int len = senate.size();
		for (int i = (pos + 1) % len; i != pos; i = (i+1) % len)
		{
			if (senate[i] == target)
				return i;
		}
		// �����ڣ��򷵻�-1
		return -1;
	}
};

class Solution_v2 {
public:
	string predictPartyVictory(string senate)
	{
		int len = senate.length();

		queue<int> q_r, q_d;

		for (int i = 0; i < len; ++i)
			(senate[i] == 'R') ? q_r.push(i) : q_d.push(i);
		while (!q_r.empty() && !q_d.empty())
		{
			int r_index = q_r.front();
			int d_index = q_d.front();
			q_r.pop(), q_d.pop();
			(r_index < d_index) ? q_r.push(r_index + len) : q_d.push(d_index + len);
		}
		return (q_r.size() > q_d.size()) ? "Radiant" : "Dire";
	}
};
