#include <iostream>

using namespace std;

//Tree node
struct Node {
	int val;
	Node *left;
	Node *right;
	Node(int val) : val(val) {}
	int leftVal() {
		if (left == NULL)
			return -1;
		return left->val;
	}
	int rightVal() {
		if (right == NULL)
			return -1;
		return right->val;
	}
};

//Bootlegged Tree
class BTree {
private:
	//root is always tree[0]
	Node **tree; //Unordered!
	int size;
	int curr; //For iterating
public:
	BTree(int size);
	//Left and right are the index of the node in the tree array
	void insert(int val, int left, int right);
	//Traversals will just print out values
	void print(); //Iterate through []tree

	int getDepth();
	int getDepth(Node *node);

	void levelOrder();
	void levelOrder(Node *node, int depth);
};

int main() {

	//Read and store inputs
	int size;
	cin >> size;
	BTree bt(size);

	for (int i=0; i<size; i++) {
		int val, left, right;
		cin >> val;
		cin >> left;
		cin >> right;
		bt.insert(val, left, right);
	}

	//bt.print();
	//cout << "----------------------------------" << endl;
	//cout << bt.getDepth() << endl;
	bt.levelOrder();
	return 0;
}


//Bootlegged Tree
//root is always tree[0]
//Node** tree; //Unordered!
//int curr; //For iterating

BTree::BTree(int size) : size(size) {
	tree = new Node*[size];
	for (int i=0; i<size; i++) {
		Node *node = new Node(-1);
		tree[i] = node;
	}
	curr = 0;
}
//Left and right are the index of the node in the tree array
//WARNING: No array overflow check!
void BTree::insert(int val, int left, int right) {
	Node *node = tree[curr];
	//WARNING: May not update children later! FIXED
	node->val = val;
	if (left > 0)
		node->left = tree[left];
	if (right > 0)
		node->right = tree[right];
	curr++;
}
//Traversals will just print out values
//Iterate through []tree
void BTree::print() {
	for (int i=0; i<size; i++) {
		if (tree[i] != NULL)
			cout << i << ": " << tree[i]->val << " " << tree[i]->leftVal()
				<< " " << tree[i]->rightVal() << endl;
		else
			cout << i << ": " << "NULL" << endl;
	}
}

int BTree::getDepth() {
	return getDepth(tree[0]);
}

int BTree::getDepth(Node *node) {
	int left = 0;
	int right = 0;
	if (node->left != NULL)
		left = getDepth(node->left) + 1;
	if (node->right != NULL)
		right = getDepth(node->right) + 1;
	if (left == 0 && right == 0)
		return 0;
	return (left > right) ? left : right;
}

void BTree::levelOrder() {
	int depth = getDepth();
	for (int i=0; i<=depth; i++) {
		levelOrder(tree[0], i);
	}
}
void BTree::levelOrder(Node *node, int depth) {
	if (depth == 0) {
		cout << node->val << ' ';
	} else {
		depth--;
		if (node->left != NULL)
			levelOrder(node->left, depth);
		if (node->right != NULL)
			levelOrder(node->right, depth);
	}
}
