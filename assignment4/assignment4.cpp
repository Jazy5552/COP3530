// C implementation of search and insert operations
// on Trie
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdbool.h>
#include <iostream>

//TODO Refactor

#define ALPHABET_SIZE (26)

//Useful utility functions
#define ARRAY_SIZE(a) (int)(sizeof(a)/sizeof(a[0]))
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

using namespace std;

struct TrieNode {
	struct TrieNode *children[ALPHABET_SIZE];
	
	//Count will be the number of times that the word is in the trie
	int count;
};

//Returns a new TrieNode with count as 0 and children as NULL
struct TrieNode *getNode(void) {
	struct TrieNode *node = new TrieNode();
	node->count = 0;
	
	//Set the children to null
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		node->children[i] = NULL;
	}

	return node;
}

//If not present, insert key into trie
//If the key is a prefix of the trie node, just increment count
void increment(struct TrieNode *root, string key) {
	int length = key.length();

	struct TrieNode *iter = root;

	for (int level = 0; level < length; level++) {
		//Get the index for the current children node
		int index = CHAR_TO_INDEX(key[level]);
		if (iter->children[index] == NULL) //!NULL
			iter->children[index] = getNode();

		iter = iter->children[index];
	}

	//Increment the last node
	iter->count++;
}

//If not present, does nothing
//If the key is a prefix of the trie node, just decrement
void decrement(struct TrieNode *root, string key) {
	int length = key.length();

	struct TrieNode *iter = root;

	for (int level = 0; level < length; level++) {
		//Get the index for the current children node
		int index = CHAR_TO_INDEX(key[level]);
		if (iter->children[index] == NULL) //!NULL
			iter->children[index] = getNode();

		iter = iter->children[index];
	}

	//Increment the last node
	iter->count--;
}

//Returns the number of times the key has been entered into the trie
int search(struct TrieNode *root, string key) {
	int length = key.length();
	struct TrieNode *iter = root;

	for (int level = 0; level < length; level++) {
		int index = CHAR_TO_INDEX(key[level]);
		
		//If the prefix for the key doesn't exist then don't bother continuing
		if (iter->children[index] == NULL)
			return 0;

		iter = iter->children[index];
	}

	if (iter == NULL)
		return 0;
	else
		return iter->count;
}

//Prints out the tree in post order traversal
void print(struct TrieNode *root, string curWord) {
	struct TrieNode *iter = root;

	//Loop through the whole array TODO Optimize using vector/map
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (iter->children[i] != NULL) 
			print(iter->children[i], curWord + char('a' + i));
	}
	
	if (iter != NULL && iter->count > 0)
		cout << curWord << ": " << iter->count << endl;

}

int main() {
	TrieNode *root = getNode();
	string inc, dec;
	getline(cin, inc);
	getline(cin, dec);

	//Get keys ew code incoming
	string key = "";
	for (int i=0; i<inc.length(); i++) {
		if (inc[i] == ' ') {
			increment(root, key);
			key = "";
		} else {
			key = key + inc[i];
		}
	}
	increment(root, key);
	//Get keys ew code incoming
	key = "";
	for (int i=0; i<dec.length(); i++) {
		if (dec[i] == ' ') {
			decrement(root, key);
			key = "";
		} else {
			key = key + dec[i];
		}
	}
	decrement(root, key);
	
	print(root, "");

	return 0;
}
