/*
 * Assignment 2 made by Jazy
 */
#include <iostream>

using namespace std;

//HashNode will be the key value pairs (LinkedListy)
struct HashNode {
	int key, value;
	HashNode *next;
	HashNode(int key, int value)
		:key(key), value(value), next(NULL) {};
};

//Hashmap will use ints for keys and values
//Collisions will just form a linklisty structure at each key
class HashMap {
private:
	const int SIZE; //No refactoring
	HashNode **map;
	//Returns the hash from the given key
	int hashFunc(int key) {
		return key % SIZE;
	}

public:
	HashMap(int size) : SIZE(size) {
		map = new HashNode*[SIZE]();
	}

	//~HashMap();

	void insert(int key, int value) {
		int hash = hashFunc(key);
		HashNode *prev = NULL;
		HashNode *curr = map[hash];
		
		//Collisions
		while (curr != NULL && curr->key != key) {
			//Advance to the next one
			prev = curr;
			curr = curr->next;
		}

		if (curr == NULL) {
			HashNode *n = new HashNode(key, value);
			if (prev == NULL) {
				//Empty bucket
				map[hash] = n;
			} else {
				//Place at the end of this bucket
				prev->next = n;
			}
		} else {
			//Found key, so just update it
			curr->value = value;
		}
	}

	int operator[](int key) {
		return get(key);
	}

	int get(int key) {
		int hash = hashFunc(key);
		//HashNode *prev = NULL;
		HashNode *curr = map[hash];
		
		//Collisions
		while (curr != NULL && curr->key != key) {
			//Advance to the next one
			//prev = curr;
			curr = curr->next;
		}
		
		if (curr == NULL) {
			//Not found
			return -1;
		} else {
			return curr->value;
		}
	}

	HashNode** getMap() {
		//WARNING NOT INTENDED!
		return map;
	}

	int getSize() {
		//WARNING NOT INTENDED!
		return SIZE;
	}

	void remove(int key) {
		int hash = hashFunc(key);
		HashNode *prev = NULL;
		HashNode *curr = map[hash];
		
		//Collisions
		while (curr != NULL && curr->key != key) {
			//Advance to the next one
			prev = curr;
			curr = curr->next;
		}

		if (curr == NULL) {
			//Not found
			//return;
		} else {
			if (prev == NULL) {
				//Only one in bucket
				map[hash] = NULL;
			} else {
				prev->next = curr->next;
			}
			delete curr;
		}
	}
};

int main() {
	//cout << "Hello World" << endl;
	int size;
	int num;
	cin >> size;

	HashMap h(size*3/2);
	int arr[size];

	for (int i=0; i<size; i++) {
		cin >> num;
		if (num < 1) {
			//Bad input!
			cout << -1;
			return 0;
		}
		arr[i] = num;
		h.insert(num, num); //Make use of value?
	}

	//Find max product
	int max = -1;
	for (int i=0; i<size; i++) {
		for (int j=i+1; j<size; j++) {
			int prod = arr[i] * arr[j];
			if (h[prod] > 0) {
				max = (max < prod) ? prod : max;
			}
		}
	}

	cout << max;

	/*h.insert(1, 11);
	h.insert(2, 22);
	h.insert(3, 33);
	h.insert(9, 44);
	h.insert(10, 55);
	h.insert(11, 111);*/
  /*
	for (int i=0; i<20; i++) {
		cout << i << ' ' << h[i] << endl;
	}
	
	//DEBUG PRINT OUT MAP
	HashNode **map = h.getMap();
	cout << "Size: " << h.getSize() << endl;
	for (int i=0; i<h.getSize(); i++) {
		HashNode *curr = map[i];
		cout << i << ") ";
		while (curr != NULL) {
			cout << curr->key << ':' << curr->value << ", ";
			curr = curr->next;
		}
		cout << endl;
	}
	*/
	return 0;
}

