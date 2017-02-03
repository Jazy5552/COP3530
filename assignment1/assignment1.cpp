#include <iostream>
#include <ctime>

using namespace std;

//Holy fucked logic batman, this source code is really bad
//and I feel really bad...

struct Node {
	Node *next;
	int data;
};

//Linkedlist will be a looped list
class LinkedList {
private:
public:
	Node *firstNode;
	Node *lastNode;
	void add(int data); //Append new node with data to the list
	LinkedList(); //Create linkedlist
	~LinkedList(); //Delete all nodes
};

class Iterator {
private:
	Node *currentNode;
	Node *prevNode;
	LinkedList *list;
public:
	Iterator(LinkedList *list);
	const Node* getCurrentNode(); //Current node for reference
	void next(); //Moves currentNode forward by 1
	//No backwards!
	void remove(); //Removes currentNode from the list
	int get(); //Returns the data of the currentNode
	void reset(); //Restart currentNode to start of the linkedlist
};

int main() {
	//WARNING Empty list breaks this
	//clock_t begin = clock();
	//double elap;
	LinkedList list;
	int length;
	cin >> length;
	//length = 10;
	for (int i=0; i<length; i++) {
		int num;
		cin >> num;
		//num = i*2;
		list.add(num);
	}
	cin >> length; //# of deletions
	//length = 1;
	for (int i=0; i<length; i++) {
		int d[3];
		cin >> d[0]; //a
		cin >> d[1]; //b
		cin >> d[2]; //S
		//d[0] = 2;
		//d[1] = 7;
		//d[2] = 1;

		if (list.firstNode != NULL && d[0] == d[1]) {
			Iterator it(&list);
			const Node *start = it.getCurrentNode();
			int count = 0;
			do {
				//count a(b)
				if (it.get() == d[0])
					count++;
				it.next();
			} while (it.getCurrentNode() != start &&
					it.getCurrentNode() != NULL);
			if (count > 1) {
				//cout << "More than one" << endl;
				it.reset();
				start = it.getCurrentNode();
				do {
					//find a
					if (it.get() == d[0])
						break;
					it.next();
				} while (it.getCurrentNode() != start &&
						it.getCurrentNode() != NULL);
				if (it.get() == d[0]) {
					start = it.getCurrentNode();
					bool brk = false;
					do {
						//Perform deletions till b
						for (int i=0; i<d[2]-1; i++) {
							//Break if skipped over b
							if (it.get() == d[1] &&
								it.getCurrentNode() != start) brk = true;
							it.next();
						}
						//TODO Break if skipped b
						if (brk) break;
						if (it.get() == d[1] &&
								it.getCurrentNode() != start) brk = true; //Break if on b
						//delete the one we landed on
						it.remove();
					} while (it.getCurrentNode() != start &&
							it.getCurrentNode() != NULL &&
							!brk);
				}
			}
		} else if (list.firstNode != NULL) { //Check empty...
			Iterator it(&list);
			const Node *start = it.getCurrentNode();
			bool brk = false;
			do {
				//find a
				if (it.get() == d[0])
					break;
				it.next();
			} while (it.getCurrentNode() != start &&
					it.getCurrentNode() != NULL);
			if (it.get() == d[0]) {
				//Found a
				start = it.getCurrentNode(); //Set start to where ever a is
				//Find b...
				Iterator tmp(&list);
				const Node *tmpStart = tmp.getCurrentNode(); //wtf...
				do {
					if (tmp.get() == d[1])
						break;
					tmp.next();
				} while (tmpStart != tmp.getCurrentNode());
				if (tmp.get() == d[1]) {
					//Found b... this is rediculous
					start = it.getCurrentNode();
					do {
						//Perform deletions till b
						for (int i=0; i<d[2]-1; i++) {
							//Break if skipped over b
							if (it.get() == d[1] &&
								it.getCurrentNode() != start) brk = true;
							it.next();
						}
						//TODO Break if skipped b
						if (brk) break;
						if (it.get() == d[1]) brk = true; //Break if on b
						//delete the one we landed on
						it.remove();
					} while (it.getCurrentNode() != start &&
							it.getCurrentNode() != NULL &&
							!brk);
				}
			}
		}
	}

	//cout << "OUT" << endl;
	//Print the list
	if (list.firstNode != NULL) { //Check if empty... not proud of all this
		Iterator it(&list);
		const Node *start = it.getCurrentNode();
		do {
			cout << it.get() << " ";
			it.next();
		} while (it.getCurrentNode() != start);
	}
	
	//elap = double( clock() - begin ) / CLOCKS_PER_SEC;
	//cout << "Elap: " <<  elap << endl;
	return 0;
}



//CLASS DEFINITIONS
//Linkedlist will be a looped list
//Append new node with data to the list
void LinkedList::add(int data) {
	Node* node = new Node();
	node->data = data;
	if (firstNode == NULL) { //Empty
		firstNode = node; //First element
		lastNode = node;
	}
	node->next = firstNode; //Going to end
	lastNode->next = node;
	lastNode = node;
}
//Create linkedlist of size 1 with data
LinkedList::LinkedList() {
	//Node* node = new Node(); //Dummy node
	//node->data = -1;
	//node->next = NULL; //Going to end
	firstNode = NULL;
	lastNode = NULL;
}
//Delete all nodes
LinkedList::~LinkedList() {
	return; //yolo
	//Use iterator
	Iterator it(this);
	while (firstNode != lastNode) {
		//cout << "Deleteing: " << it.get() << endl;
		it.remove();
	}
	if (firstNode != NULL) {
		//cout << "Deleteing : " << it.get() << endl;
		it.remove();
	}
}

//Iterator definition 
Iterator::Iterator(LinkedList *list) {
	this->list = list;
	reset();
}
//Current node for reference
const Node* Iterator::getCurrentNode() {
	return currentNode;
}
//Moves currentNode forward by 1 and returns the new data
void Iterator::next() {
	//TODO WARNING Dont use an empty list!
	prevNode = currentNode; // = prevNode->next
	currentNode = currentNode->next;
}
//No backwards!
//Removes currentNode from the list
void Iterator::remove() {
	//Make sure LikedList first and last node remain correct
	if (list->lastNode == list->firstNode) {
		//cout << "delete last" << endl; //Removeing last element
		list->firstNode = NULL;
		list->lastNode = NULL;
		delete(currentNode); 
		reset();
	} else {
		if (list->firstNode == currentNode)
			list->firstNode = currentNode->next;

		if (list->lastNode == currentNode)
			list->lastNode = prevNode;

		prevNode->next = currentNode->next;
		delete(currentNode); 

		currentNode = prevNode->next;
	}
}
//Returns the data of the currentNode	
int Iterator::get() {
	return currentNode->data;
}
//Restart currentNode to start of the linkedlist
void Iterator::reset() {
	currentNode = list->firstNode;
	prevNode = list->lastNode;
}
