# KMP Algorithm (Searching for Patterns)

## Problem

Given a text txt[0..n-1] and a pattern pat[0..m-1], write a function search(char pat[], char txt[]) that prints all occurrences of pat[] in txt[]. You may assume that n > m.

Examples

```
Input:  txt[] = "THIS IS A TEST TEXT"
        pat[] = "TEST"
Output: Pattern found at index 10

Input:  txt[] =  "AABAACAADAABAABA"
        pat[] =  "AABA"
Output: Pattern found at index 0
        Pattern found at index 9
        Pattern found at index 12
```

![string matching](https://github.com/HongfeiXu/LeetCode/blob/master/images/Pattern-Searching-2.png?raw=true)


## Naive Pattern Searching:
Slide the pattern over text one by one and check for a match. If a match is found, then slides by 1 again to check for subsequent matches.

## KMP (Knuth Morris Pratt) Pattern Searching

The KMP matching algorithm uses degenerating property (pattern having same sub-patterns appearing more than once in the pattern) of the pattern and improves the worst case complexity to O(n). **The basic idea behind KMP’s algorithm is: whenever we detect a mismatch (after some matches), we already know some of the characters in the text of next window. We take advantage of this information to avoid matching the characters that we know will anyway match.** Let us consider below example to understand this.

```
Matching Overview
txt = "AAAAABAAABA" 
pat = "AAAA"

We compare first window of txt with pat
txt = "AAAAABAAABA" 
pat = "AAAA"  [Initial position]
We find a match. This is same as Naive String Matching.

In the next step, we compare next window of txt with pat.
txt = "AAAAABAAABA" 
pat =  "AAAA" [Pattern shifted one position]
This is where KMP does optimization over Naive. In this 
second window, we only compare fourth A of pattern
with fourth character of current window of text to decide 
whether current window matches or not. Since we know 
first three characters will anyway match, we skipped 
matching first three characters. 

Need of Preprocessing?
An important question arises from above explanation, 
how to know how many characters to be skipped. To know 
this, we pre-process pattern and prepare an integer array 
lps[] that tells us count of characters to be skipped. 
```

## Preprocessing Overview:

- KMP algorithm does preproceses pat[] and constructs an auxiliary lps[] of size m (same as size of pattern) which is used to skip characters while matching.
- name **lps** indicates **longest proper prefix which is also suffix**. A proper prefix is prefix with whole string not allowed. For example, prefixes of “ABC” are “”, “A”, “AB” and “ABC”. Proper prefixes are “”, “A” and “AB”. Suffixes of the string are “”, “C”, “BC” and “ABC”.
- For each sub-pattern pat[0..i] where i = 0 to m-1, lps[i] stores length of the maximum matching proper prefix which is also a suffix of the sub-pattern pat[0..i].

```
   lps[i] = the longest proper prefix of pat[0..i] 
              which is also a suffix of pat[0..i].
```

```
Examples of lps[] construction:
For the pattern “AAAA”, 
lps[] is [0, 1, 2, 3]

For the pattern “ABCDE”, 
lps[] is [0, 0, 0, 0, 0]

For the pattern “AAACAAAAAC”, 
lps[] is [0, 1, 2, 0, 1, 2, 3, 3, 3, 4] 
```

## Searching Algorithm

Unlike Naive algorithm, where we slide the pattern by one and compare all characters at each shift, we use a value from lps[] to decide the next characters to be matched. The idea is to not match character that we know will anyway match.

How to use lps[] to decide next positions (or to know number of characters to be skipped)?

- We start comparison of pat[j] with j = 0 with characters of current window of text.
- We keep matching characters txt[i] and pat[j] and keep incrementing i and j while pat[j] and txt[i] keep matching.
- **When we see a mismatch**
  - We know that characters pat[0..j-1] match with txt[i-j+1…i-1] (Note that j starts with 0 and increment it only when there is a match).
  - We also know (from above definition) that lps[j-1] is count of characters of pat[0…j-1] that are both proper prefix and suffix.
  - From above two points, we can conclude that we do not need to match these lps[j-1] characters with txt[i-j…i-1] because we know that these characters will anyway match. Let us consider above example to understand this.

```
txt[] = "AAAAABAAABA" 
pat[] = "AAAA"
lps[] = {0, 1, 2, 3} 

i = 0, j = 0
txt[] = "AAAAABAAABA" 
pat[] = "AAAA"
txt[i] and pat[j[ match, do i++, j++

i = 1, j = 1
txt[] = "AAAAABAAABA" 
pat[] = "AAAA"
txt[i] and pat[j[ match, do i++, j++

i = 2, j = 2
txt[] = "AAAAABAAABA" 
pat[] = "AAAA"
pat[i] and pat[j[ match, do i++, j++

i = 3, j = 3
txt[] = "AAAAABAAABA" 
pat[] = "AAAA"
txt[i] and pat[j[ match, do i++, j++

i = 4, j = 4
Since j == M, print pattern found and resset j,
j = lps[j-1] = lps[3] = 3

Here unlike Naive algorithm, we do not match first three 
characters of this window. Value of lps[j-1] (in above 
step) gave us index of next character to match.
i = 4, j = 3
txt[] = "AAAAABAAABA" 
pat[] =  "AAAA"
txt[i] and pat[j[ match, do i++, j++

i = 5, j = 4
Since j == M, print pattern found and reset j,
j = lps[j-1] = lps[3] = 3

Again unlike Naive algorithm, we do not match first three 
characters of this window. Value of lps[j-1] (in above 
step) gave us index of next character to match.
i = 5, j = 3
txt[] = "AAAAABAAABA" 
pat[] =   "AAAA"
txt[i] and pat[j] do NOT match and j > 0, change only j
j = lps[j-1] = lps[2] = 2

i = 5, j = 2
txt[] = "AAAAABAAABA" 
pat[] =    "AAAA"
txt[i] and pat[j] do NOT match and j > 0, change only j
j = lps[j-1] = lps[1] = 1 

i = 5, j = 1
txt[] = "AAAAABAAABA" 
pat[] =     "AAAA"
txt[i] and pat[j] do NOT match and j > 0, change only j
j = lps[j-1] = lps[0] = 0

i = 5, j = 0
txt[] = "AAAAABAAABA" 
pat[] =      "AAAA"
txt[i] and pat[j] do NOT match and j is 0, we do i++.

i = 6, j = 0
txt[] = "AAAAABAAABA" 
pat[] =       "AAAA"
txt[i] and pat[j] match, do i++ and j++

i = 7, j = 1
txt[] = "AAAAABAAABA" 
pat[] =       "AAAA"
txt[i] and pat[j] match, do i++ and j++

We continue this way...
```

```c++
#include <iostream>

using namespace std;

void computeLPSArray(const char *pat, int *lps);

void KMPSearch(const char *txt, const char *pat)
{
	int M = strlen(txt);
	int N = strlen(pat);

	int *lps = new int[N];
	memset(lps, 0, N * sizeof(int));
	computeLPSArray(pat,lps);

	int i = 0;	// index for txt[]
	int j = 0;	// index for pat[]
	while (i < M)
	{
		if (pat[j] == txt[i])
		{
			j++;
			i++;
			if (j == N)
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
	KMPSearch(txt, pat);

	return 0;
}
```

```
Found Pattern at index 10
请按任意键继续. . .
```
[KMP Code](https://github.com/HongfeiXu/LeetCode/blob/master/algorithms/cpp/kmp.cpp)

## Reference

[Searching for Patterns | Set 2 (KMP Algorithm)](http://www.geeksforgeeks.org/searching-for-patterns-set-2-kmp-algorithm/)  
[字符串匹配的KMP算法](http://www.ruanyifeng.com/blog/2013/05/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm.html)  



