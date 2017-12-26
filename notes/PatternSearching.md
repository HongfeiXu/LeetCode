```c++
/*

Pattern Searching

Given a text txt[0..n-1] and a pattern pat[0..m-1], 
write a function search(char pat[], char txt[]) that 
prints all occurrences of pat[] in txt[]. 
You may assume that n > m.

ref: https://www.geeksforgeeks.org/fundamentals-of-algorithms/#PatternSearching
ref: CLRS chapter 32

*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// Native Pattern Searching
// Slide the pattern over text one by one and check for a match. 
// If a match is found, then slides by 1 again to check for subsequent matches.

void search(const string& pat, const string& txt)
{
	for (size_t i = 0; i < txt.size(); ++i)
	{
		size_t j = 0;
		for (j = 0; j < pat.size(); ++j)
			if(pat[j] != txt[i+j])
				break;
		if (j == pat.size())
			cout << "Pattern found at index " << i << endl;
	}
}

//////////////////////////////////////////////////////////////////////////
// KMP Algorithm
// KMP algorithm does preproceses pat[] and constructs an auxiliary lps[] 
// of size m (same as size of pattern) which is used to skip characters while matching.

void computeLPSArray(const string& pat, vector<int>& lps)
{
	lps.assign(pat.size(), 0);
	lps[0] = 0;
	int len = 0;
	int i = 1;
	while (i < pat.size())
	{
		if (pat[i] == pat[len])
		{
			++len;
			lps[i] = len;
			++i;
		}
		else
		{
			if (len != 0)
			{
				len = lps[len - 1];
			}
			else
			{  
				lps[i] = 0;
				++i;
			}
		}
	}
}

void KMPSearch(const string& pat, const string& txt)
{
	vector<int> lps;
	computeLPSArray(pat, lps);

	int i = 0;	// index for txt
	int j = 0;	// index for pat
	while (i < txt.size())
	{
		if (txt[i] == pat[j])
		{
			++i;
			++j;
			if (j == pat.size())
			{
				cout << "Pattern found at index " << i - j << endl;
				j = lps[j - 1];
			}
		}
		else
		{
			if (j != 0)
				j = lps[j - 1];
			else
				++i;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Rabin-Karp Algorithm
// Like the Naive Algorithm, Rabin-Karp algorithm also slides the pattern one by one. 
// But unlike the Naive algorithm, Rabin Karp algorithm matches the hash value of the 
// pattern with the hash value of current substring of text, and if the hash values 
// match then only it starts matching individual characters. 
// So Rabin Karp algorithm needs to calculate hash values for following strings.

// 假设所有字符都是d进制
// q为一个素数，用来取模
void RKSearch(const string& pat, const string& txt, int d, int q)
{
	int m = pat.size();
	int n = txt.size();
	int h = 1;
	int pat_hash = 0;
	int txt_hash = 0;

	// h = d^(m-1) mod q
	for (int i = 0; i < m-1; ++i)
		h = (h * d) % q;

	// calculate the hash value of pattern and 
	// first window of text
	for (int i = 0; i < m; ++i)
	{
		pat_hash = (d * pat_hash + pat[i]) % q;
		txt_hash = (d * txt_hash + txt[i]) % q;
	}

	// slide the pattern over text one by one
	for (int i = 0; i <= n - m; ++i)
	{
		// Check the hash values of current window of text
		// and pattern. If the hash values match then only
		// check for characters on by one
		if (pat_hash == txt_hash)
		{
			int j = 0;
			for (j = 0; j < m; ++j)
			{
				if(pat[j] != txt[i+j])
					break;
			}
			if (j == m)
				cout << "Pattern found at index " << i << endl;
		}
		// calculate hash value for next window of text:
		// remove leading digit, add trailing digit
		if (i < n - m)
		{
			txt_hash = (d * (txt_hash - txt[i] * h) + txt[i + m]) % q;
			// txt_hash 可能为负值，转化为正值
			if (txt_hash < 0)
				txt_hash += q;
		}
	}
}

int main()
{
	string txt("GEEKS FOR GEEKS");
	string pat("GEEK");
	int d = 256;
	int q = 101;
	RKSearch(pat, txt, d, q);

	return 0;
}


```

