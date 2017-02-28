#include <iostream>
#include <vector>

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
	Node *tree; //Unordered!
	//root is always tree[0]
	//int size;
	//Node *root;
	//int curr; //For iterating
public:
	BTree(Node *tree);
	//Left and right are the index of the node in the tree array
	//void insert(int val, int left, int right);
	//void setRoot(int index);
	//Traversals will just print out values
	//void print(); //Iterate through []tree

  //Helper function
  void preorder();
  //Preorder: Print value and go down left child then right
  void preorder(Node *node);

  void inorder();
  //Inorder
  void inorder(Node *node);

  void postorder();
  void postorder(Node *node);

	int getDepth();
	int getDepth(Node *node);

	void levelOrder();
	void levelOrder(Node *node, int depth);
};

Node *constructTree(vector<int> post, vector<int> in);
int getIndex(vector<int> arr, int ele);

int main() {
	//Read and store inputs
	int size;
	cin >> size;
	vector<int> post;
	vector<int> in;

	for (int i=0; i<size; i++) {
		//Create nodes
		int val;
		cin >> val;
		post.push_back(val);
	}
	
	for (int i=0; i<size; i++) {
		int val;
		cin >> val;
		in.push_back(val);
	}

	//Create the tree with it's proper root
	Node *tree = constructTree(post, in);
	BTree bt(tree);
	//bt.preorder();
	//cout << "\n----------------------------------" << endl;
	//bt.postorder();
	//cout << "\n----------------------------------" << endl;
	//bt.inorder();
	//cout << "\n----------------------------------" << endl;
	//bt.print();
	//bt.print();
	//cout << "----------------------------------" << endl;
	//cout << bt.getDepth() << endl;
	bt.levelOrder();
	//cout << "\n----------------------------------" << endl;
	return 0;
}

Node *constructTree(vector<int> post, vector<int> in) {
	int size = post.size();
	int root = post[size-1];
	Node *node = new Node(root);
	int i = getIndex(in, root);

	//Everything <i is left subtree, >i is right subtree
	vector<int> leftPost;
	vector<int> leftIn;
	for (int j=0; j<i; j++) {
		leftPost.push_back(post[j]);
		leftIn.push_back(in[j]);
		//cout << "Pushed left " << post[j-1] << endl;
	}

	vector<int> rightPost;
	vector<int> rightIn;
	for (int j=i+1; j<size; j++) {
		rightPost.push_back(post[j-1]);
		rightIn.push_back(in[j]);
		//cout << "Pushed right " << post[j-1] << endl;
	}
	
	if (leftPost.size() == 0) {
		//No left child
		//cout << "left end" << endl;
		node->left = NULL;
	} else {
		node->left = constructTree(leftPost, leftIn);
	}

	if (rightPost.size() == 0) {
		//No right child
		//cout << "right end" << endl;
		node->right = NULL;
	} else {
		node->right = constructTree(rightPost, rightIn);
	}
	return node;
}

int getIndex(vector<int> arr, int ele) {
	int size = arr.size();
	for (int i=0; i<size; i++) {
		if (arr[i] == ele) {
			return i;
		}
	}
	return -1;
}

//Bootlegged Tree
//root is always tree[0]
//Node** tree; //Unordered!
//int curr; //For iterating

BTree::BTree(Node *tree) : tree(tree) {}

//Left and right are the index of the node in the tree array
//WARNING: No array overflow check!
/*void BTree::insert(int val, int left, int right) {
	Node *node = tree[curr];
	//WARNING: May not update children later! FIXED
	node->val = val;
	if (left > 0)
		node->left = tree[left];
	if (right > 0)
		node->right = tree[right];
	curr++;
}*/
//Traversals will just print out values
//Iterate through []tree
/*void BTree::print() {
	for (int i=0; i<size; i++) {
		if (tree[i] != NULL)
			cout << i << ": " << tree[i]->val << " " << tree[i]->leftVal()
				<< " " << tree[i]->rightVal() << endl;
		else
			cout << i << ": " << "NULL" << endl;
	}
}*/

int BTree::getDepth() {
	return getDepth(tree);
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
		levelOrder(tree, i);
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

//Preorder goes down the left children and prints before going down
void BTree::preorder() {
  //Helper function
  preorder(tree);
}
void BTree::preorder(Node *node) {
  cout << node->val << ' ';
  if (node->left != NULL)
    preorder(node->left);
  if (node->right != NULL)
    preorder(node->right);
}

void BTree::inorder() {
  inorder(tree);
}
void BTree::inorder(Node *node) {
  if (node->left != NULL)
    inorder(node->left);
  cout << node->val << ' ';
  if (node->right != NULL)
    inorder(node->right);
}

void BTree::postorder() {
  postorder(tree);
}
void BTree::postorder(Node *node) {
  if (node->left != NULL)
    postorder(node->left);
  if (node->right != NULL)
    postorder(node->right);
  cout << node->val << ' ';
}


/*void BTree::setRoot(int index) {
	root = tree[index];
}*/
