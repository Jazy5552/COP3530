#include <iostream>
#include <vector>

//This is c++, lose your old ways fool!
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define ALPHABET_SIZE (26)

#define debug false //Set to true for more information

using namespace std; //savage

//TODO Would be nice if you made some prototypes you heathen

//-----------------------------------------------------------------
//----------------------TRIE STUFF---------------------------------
//-----------------------------------------------------------------

//**Reason for not makeing a class like a normal c++ programmer**

//TrieNode struct (Should prob make this a class)
//Will be used to store suffixes
struct TrieNode {
	TrieNode *children[ALPHABET_SIZE];
	
	//A vector containing the indexes of the suffix that land on this node
	vector<int> indexes;
};
//Returns a new TrieNode with count as 0 and children as NULL
TrieNode *getNode(void) {
	struct TrieNode *node = new TrieNode();
	
	//Set the children to null
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		node->children[i] = NULL;
	}

	return node;
}
//If not present, insert key into trie
void add(TrieNode *root, string key, int index) {
	int length = key.length();
	TrieNode *iter = root;
	for (int level = 0; level < length; level++) {
		//Get the index for the current children node
		//NOTE: level = 0 is the root node so we dont add the index to it
		int i = CHAR_TO_INDEX(key[level]);
		if (iter->children[i] == NULL) //!NULL
			iter->children[i] = getNode();
		iter = iter->children[i];

		//Add the index
		iter->indexes.push_back(index);
	}
}
//Searches for key and returns the vector of indexes
//The search is performed iteratively (Instead of recursively...)
vector<int> *search(struct TrieNode *root, string key) {
	int length = key.length();
	struct TrieNode *iter = root;

	for (int level = 0; level < length; level++) {
		int index = CHAR_TO_INDEX(key[level]);
		
		//If the prefix for the key doesn't exist then don't bother continuing
		if (iter->children[index] == NULL)
			return NULL;

		iter = iter->children[index];
	}
	if (iter == NULL)
		return NULL;
	else
		return &iter->indexes;
}
//Prints out the tree in post order traversal
//NOTE: Mostly for debugging (even though I don't understand half the shit
//it prints...)
//Of course it doesn't make sense when it has an off by one error you dope!
void print(struct TrieNode *root, string curWord) {
	struct TrieNode *iter = root;

	//Loop through the whole array 
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (iter->children[i] != NULL) 
			print(iter->children[i], curWord + char('a' + i));
	}
	
	if (iter != NULL && iter->indexes.size() > 0) {
		for (int i = 0; i < (int)iter->indexes.size(); i++) {
			cout << curWord << " at position " << iter->indexes[i] << endl;
		}
	}
	cout << "------------------" << endl;
}
//-----------------------------------------------------------------
//--------------------END TRIE STUFF-------------------------------
//-----------------------------------------------------------------

//Create a suffix trie from the str string
TrieNode *createSuffixTrie(string str) {
	TrieNode *root = getNode();
	//Go through every possible suffix of str and add it to the trie
	for (int i=0; i<(int)str.length(); i++) {
		string strSuf = str.substr(i);
		//cout << strSuf << endl;
		add(root, strSuf, i);
	}
	return root;
}

//Utility function (Modified for vectors
vector<int> max(vector<int> x, vector<int> y) {
	if (x.size() > y.size()) 
		return x;
	return y;
}

//Function that magically returns the longestpalindrom in O(n^2)ish time
//...
vector<int> getLongestPalindrome(vector<int> vec) {
	int s = (int)vec.size();
	vector<int> dp[s][s]; //Hanzo main

	//  v  Learn to spell, idiot
	//Digonal will hold the individual string chars (Palindromes of 1)
	for (int i=0; i<s; i++)
		dp[i][i].push_back(vec[i]);
	
	//Traverse and fill out the 2d table starting in the bottom right and never crossing
	//the diagonal | lol k
	for (int i=s-2; i>=0; i--) { //-2 keeps it off the diagonal (Bottom right)
		//Don't calculate lower diagonal | Don't tell me what to do!
		for (int j=i+1; j<s; j++) { //+1 keeps it off the diagonal (j=i => diagonal)
			vector<int> result;
			if (vec[i] != vec[j]) {
				result = max(dp[i+1][j], dp[i][j-1]); //Killer time savings right here!
			} else if (i == j - 1 && vec[i] == vec[j-1]) {
				result.push_back(vec[i]);
				result.push_back(vec[j-1]);
			} else { //vec[i] == vec[j]
				//vec[i] goes first
				result.push_back(vec[i]); 
				vector<int> lps = dp[i+1][j-1]; //The time saves!!!
				//Then the longestPalindrome goes in the middle
				result.reserve(lps.size());
				result.insert(result.end(), lps.begin(), lps.end());
				//Then vec[j] goes at the end
				result.push_back(vec[j]); 
			}
			//Store the result for later
			dp[i][j] = result;
		}
	}

	//Get the answer out of that mess of a dp
	return dp[0][s-1]; //lps from index 0 to s-1
}

//TODO Toss this cpu murderer to the void, officer
//Returns a vector containing the largest palindrome from the given vector
//Disgusting Performance
/*
vector<int> getLongestPalindrome(vector<int> vec, int i, int j) {
	//WARNING No oob check! | yolo
	vector<int> result;

	if (vec[i] != vec[j]) {
		vector<int> lps = max(getLongestPalindrome(vec, i+1, j), getLongestPalindrome(vec, i, j-1));
		result.reserve(lps.size());
		result.insert(result.end(), lps.begin(), lps.end());
		//max(getLongestPalindrome(vec, i+1, j), getLongestPalindrome(vec, i, j-1));
	} else if (i == j) { //vec[i] = vec[j] which is a palindrome of 1
		result.push_back(vec[i]);
		//return 1;
	} else if (i == j - 1 && vec[i] == vec[j-1]) { //WARNING No oob checking!
		result.push_back(vec[i]);
		result.push_back(vec[j-1]);
		//return 2;
	} else { //vec[i] == vec[j]
		//vec[i] goes first
		result.push_back(vec[i]); 

		vector<int> lps = getLongestPalindrome(vec, i+1, j-1);
		//Then the longestPalindrome goes in the middle
		result.reserve(lps.size());
		result.insert(result.end(), lps.begin(), lps.end());

		//Then vec[j] goes at the end
		result.push_back(vec[j]); 
		//return (2 + getLongestPalindrome(vec, i+1, j-1));
	}

	return result;
}
*/

//Main driver
int main() {
	string in, pattern;
	getline(cin, in);
	//in = "helloowloorlod";
	
	//Create the suffix trie
	TrieNode *root = createSuffixTrie(in);
	
	getline(cin, pattern);
	//pattern = "lo";
	
	//Get the indexes of the pattern within the in string given above
	vector<int> *indexes = search(root, pattern);
	//Why is this a pointer?
	//I'm using NULL as a fail case... sry
	
	if (debug) {
		cout << "----PRINTING TRIE----" << endl;
		print(root, "");
		cout << "------END TRIE-------" << endl;
	}

	//Print out the indexes (For debugging)
	if (debug) {
		if (indexes == NULL) {
			cout << "Pattern not found" << endl;
		} else {
			for (int i=0; i<(int)indexes->size(); i++) {
				cout << "Pattern found at position " << indexes->at(i) << endl;
			}
		}
	}


	//Error checking?
	if (indexes == NULL || indexes->size() < 2)
		return 1;
	
	//Turn indexes into distance between indexes (Combination)
	vector<int> combo;
	for (int i=1; i<(int)indexes->size(); i++) {
		combo.push_back(indexes->at(i) - indexes->at(i-1)); //Negatives?
	}

	//Print the combination (Debugging)
	if (debug) {
		cout << "Combination: ";
		for (int i=0; i<(int)combo.size(); i++)
			cout << combo[i] << " ";
		cout << endl;
	}

	//Debug 
	/*
	int arr[] = {1,2,5,8,5,9,2,1};
	vector<int> tmp(arr, arr + sizeof(arr) / sizeof(arr[0]));
	for (int i=0; i<(int)tmp.size(); i++)
		cout << tmp[i] << ", ";
	cout << endl;
	//vector<int> tmpPali = getLongestPalindrome(tmp, 0, tmp.size());
	vector<int> tmpPali = getLongestPalindrome(tmp); //NEW AND IMPROVED
	for (int i=0; i<(int)tmpPali.size(); i++)
		cout << tmpPali[i] << ", ";
	cout << endl;
	*/

	//Get the lps of the combination
	//vector<int> finalComb = tmpPali;
	vector<int> finalComb = getLongestPalindrome(combo);

	//Print that shit
	for (int i=0; i<(int)finalComb.size(); i++) {
		cout << finalComb[i] << " ";
	}
	cout << endl;

	return 0;
}








/*/Rant//
Why the hell is this compiler complaining about converting from unsigned int to int in 
every for loop that I use vector.size(). We are in the year of our lord and savior 20
17! Has technology not come far enough for g++ to automatically convert something as 
simple as an unsigned integer to and in int, specially if used in a for loop. 
I swear to god if you expect me to write for(unsigned int i=0;;) every time then you 
have to go back to the 80s where you belong.
*/
//Stop using vim idiot
