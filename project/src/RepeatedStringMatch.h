#pragma once

/*

686. Repeated String Match

Given two strings A and B, find the minimum number of times A has to be repeated such that B is a substring of it. If no such solution, return -1.

For example, with A = "abcd" and B = "cdabcdab".

Return 3, because by repeating A three times (¡°abcdabcdabcd¡±), B is a substring of it; and B is not a substring of A repeated two times ("abcdabcd").

Note:
The length of A and B will be between 1 and 10000.

A: abcd
B: cdabcdab

A: abababaaba
B: aabaaba

Approach 1:

Reference: https://leetcode.com/problems/repeated-string-match/solution/

Intuition: The question can be summarized as "What is the smallest	k for which B is a substring of A*k?"
We can just try every k.

Algorithm:
Now, suppose q is the least number for which len(B) <= len(A * q). We only need to check whether B is a substring of A * q or A * (q+1).

The key to speed up is to use KMP string matching method.

repeatedStringMatch: use NaiveStringMatching, and need extra memory to append A multiple times.

Time O(m*n)
Space O(m+n)

repeatedStringMatch_v2: 
This is basically a modified version of string find, which does not stop at the end of A, but continue matching by looping through A.

Time O(m*n)
Space O(1)

repeatedStringMatch_v3:
use kmp to do the string matching work, muck quicker than the first solution.

*/

#include <string>

using namespace std;

class Solution {
private:
	int NaiveStringMatching(const string& T, const string& P)
	{
		for (int i = 0; i <= T.size() - P.size(); i++)
		{
			int j;
			for (j = 0; j < P.size() && T[i + j] == P[j]; j++);
			if (j == P.size())
				return i;
		}
		return -1;
	}

	int KMPSearch(const char *pat, const char *txt)
	{
		int M = strlen(pat);
		int N = strlen(txt);

		int *lps = new int[M];
		memset(lps, 0, M * sizeof(int));
		computeLPSArray(pat, lps);

		int i = 0;	// index for txt[]
		int j = 0;	// index for pat[]
		while (i < N)
		{
			if (pat[j] == txt[i])
			{
				j++;
				i++;
				if (j == M)
				{
					return i - j;
					j = lps[j - 1];
				}
			}
			else
			{
				if (j > 0)
					j = lps[j - 1];
				else
					i++;
			}
		}
		return -1;
	}

	// Fills lps[] for given patttern pat[0..M-1]
	void computeLPSArray(const char *pat, int *lps)
	{
		// length of the previous longest prefix suffix
		int len = 0;
		int M = strlen(pat);
		lps[0] = 0;		// lps[0] is always 0

						// the loop calculate lps[i] from 0 to M-1
		int i = 1;
		while (i < M)
		{
			if (pat[i] == pat[len])
			{
				len++;
				lps[i] = len;
				i++;
			}
			else // (pat[i] != pat[len])
			{
				// This is tricky. Consider the example.
				// AAACAAAA and i = 7. The idea is similar 
				// to search step.
				if (len != 0)
				{
					len = lps[len - 1];
					// Also, note that we do not increment
					// i here
				}
				else
				{
					lps[i] = 0;
					i++;
				}
			}
		}
	}


public:
	int repeatedStringMatch(string A, string B)
	{
		string S("");
		int q = 0;
		for (; S.length() < B.length(); ++q, S.append(A));
		if (NaiveStringMatching(S, B) != -1)
			return q;
		if (NaiveStringMatching(S.append(A), B) != -1)
			return q + 1;

		return -1;
	}

	int repeatedStringMatch_v2(string A, string B)
	{
		for (int i = 0, j = 0; i < A.size(); i++)
		{
			for (j = 0; j < B.size() && A[(i + j) % A.size()] == B[j]; j++);
			if (j == B.size()) return (i + j) / A.size() + ((i + j) % A.size() != 0 ? 1 : 0);
		}

		return -1;
	}

	int repeatedStringMatch_v3(string A, string B)
	{
		string S("");
		int q = 0;
		for (; S.length() < B.length(); ++q, S.append(A));
		if (KMPSearch(B.c_str(), S.c_str()) != -1)
			return q;
		if (KMPSearch(B.c_str(), (S.append(A)).c_str()) != -1)
			return q + 1;

		return -1;
	}
};