#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
	TrieNode* children[ALPHABET_SIZE];
	bool isEndOfWord;
};

// Return new trie node (initialized to nullptr)
TrieNode* getNode()
{
	TrieNode* pNode = new TrieNode;
	pNode->isEndOfWord = false;
	for (int i = 0; i < ALPHABET_SIZE; ++i)
		pNode->children[i] = nullptr;
	return pNode;
}

void insert(TrieNode* root, string key)
{
	TrieNode* pCrawl = root;
	for (int i = 0; i < key.length(); ++i)
	{
		int index = key[i] - 'a';
		// If not present, inserts key into trie
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();
		pCrawl = pCrawl->children[index];
	}
	// mark last node as end of word
	pCrawl->isEndOfWord = true;
}

// Returns true if key presents in trie, else false
bool search(TrieNode* root, string key)
{
	TrieNode* pCrawl = root;
	for (int i = 0; i < key.length(); ++i)
	{
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			return false;
		pCrawl = pCrawl->children[index];
	}
	return pCrawl->isEndOfWord;
}

void driver()
{
	vector<string> keys= { "the", "a", "there", "answer", "any", "by", "bye", "their" };
	TrieNode* root = getNode();
	for (int i = 0; i < keys.size(); ++i)
	{
		insert(root, keys[i]);
	}
	search(root, "the") ? cout << "Yes\n" : cout << "No\n";
	search(root, "these") ? cout << "Yes\n" : cout << "No\n";
	search(root, "any") ? cout << "Yes\n" : cout << "No\n";
	search(root, "by") ? cout << "Yes\n" : cout << "No\n";
	search(root, "thei") ? cout << "Yes\n" : cout << "No\n";
}