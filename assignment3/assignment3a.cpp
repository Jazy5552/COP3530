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

	//Helper function
	void preorder();
	//Preorder: Print value and go down left child then right
	void preorder(Node *node);

	void inorder();
	//Inorder
	void inorder(Node *node);

	void postorder();
	void postorder(Node *node);
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
	bt.preorder();
	cout << endl;
	bt.inorder();
	cout << endl;
	bt.postorder();

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

//Preorder goes down the left children and prints before going down
void BTree::preorder() {
	//Helper function
	preorder(tree[0]);
}
void BTree::preorder(Node *node) {
	cout << node->val << ' ';
	if (node->left != NULL)
		preorder(node->left);
	if (node->right != NULL)
		preorder(node->right);
}

void BTree::inorder() {
	inorder(tree[0]);
}
void BTree::inorder(Node *node) {
	if (node->left != NULL)
		inorder(node->left);
	cout << node->val << ' ';
	if (node->right != NULL)
		inorder(node->right);
}

void BTree::postorder() {
	postorder(tree[0]);
}
void BTree::postorder(Node *node) {
	if (node->left != NULL)
		postorder(node->left);
	if (node->right != NULL)
		postorder(node->right);
	cout << node->val << ' ';
}

