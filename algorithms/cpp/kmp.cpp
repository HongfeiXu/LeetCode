/*

KMP implementation with c++

Reference: http://www.ruanyifeng.com/blog/2013/05/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm.html
Reference: http://www.geeksforgeeks.org/searching-for-patterns-set-2-kmp-algorithm/

*/

#include <iostream>

using namespace std;

void computeLPSArray(const char *pat, int *lps);

void KMPSearch(const char *pat, const char *txt)
{
	int M = strlen(pat);
	int N = strlen(txt);

	int *lps = new int[M];
	memset(lps, 0, M * sizeof(int));
	computeLPSArray(pat,lps);

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
				cout << "Found Pattern at index " << i - j << endl;
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

int main()
{
	char *txt = "ABABDABACDABABCABAB";
	char *pat = "ABABCABAB";
	KMPSearch(pat, txt);

	return 0;
}