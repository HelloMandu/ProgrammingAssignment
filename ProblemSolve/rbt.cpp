#include<fstream>
#include<vector>
#include<string>
#include<cmath>
#define RED 0
#define BLACK 1
using namespace std;

struct Node {
	int key, color;
	Node *left, *right, *parent;
	Node(int key, int color, Node *leaf) : key(key), color(color), left(leaf), right(leaf), parent(NULL) {};
};

struct Tree {
	Node *root = NULL;
};

Node *leaf = new Node(-1, BLACK, NULL);
Tree *rbt = new Tree;

void leftRotate(Node *root) {
	Node *child = root->right;
	root->right = child->left;
	child->left = root;
	if (root == rbt->root) {
		rbt->root = child;
	}
	else if (root->parent->right == root) {
		root->parent->right = child;
	}
	else {
		root->parent->left = child;
	}
	child->parent = root->parent;
	root->parent = child;
	root->right->parent = root;
}

void rightRotate(Node *root) {
	Node *child = root->left;
	root->left = child->right;
	child->right = root;
	if (root == rbt->root) {
		rbt->root = child;
	}
	else if (root->parent->right == root) {
		root->parent->right = child;
	}
	else {
		root->parent->left = child;
	}
	child->parent = root->parent;
	root->parent = child;
	root->left->parent = root;
}

Node *createNode(int key) {
	return new Node(key, RED, leaf);
}

void insertNode(Tree *rbt, Node *x) {
	Node *parent = NULL;
	Node *child = rbt->root;
	while (child != leaf) {
		parent = child;
		if (x->key < child->key) {
			child = child->left;
		}
		else {
			child = child->right;
		}
	}
	x->parent = parent;
	if (rbt->root == leaf) {
		rbt->root = x;
	}
	else if (x->key < parent->key) {
		parent->left = x;
	}
	else {
		parent->right = x;
	}
}
/*
Case 1 : parent의 형제노드의 색이 RED인 경우
Case 2 : parent의 형제노드의 색이 BLCAK이면서, x가 parent의 오른쪽 child인 경우
Case 3 : parent의 형제노드의 색이 BLCAK이면서, x가 parent의 왼쪽 child인 경우
*/
void rbtInsertNode(Tree *rbt, int key) {
	Node *x = createNode(key);
	insertNode(rbt, x);
	while (x != NULL && x != rbt->root && x->parent->color == RED) {
		Node *y = NULL;
		if (x->parent == x->parent->parent->left) {
			y = x->parent->parent->right;
			if (y->color == RED) { // Case 1
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else {// y->color == BLACK
				if (x == x->parent->right) { // Case 2
					x = x->parent;
					leftRotate(x);
				}
				// Case 3
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				rightRotate(x->parent->parent);
			}
		}
		else {
			y = x->parent->parent->left;
			if (y->color == RED) { // Case 1
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else {// y->color == BLACK
				if (x == x->parent->left) { // Case 2
					x = x->parent;
					rightRotate(x);
				}
				// Case 3
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				leftRotate(x->parent->parent);
			}
		}
	}
	rbt->root->color = BLACK;
	rbt->root->parent = NULL;
}

Node *findNode(Tree *rbt, int key) {
	Node *node = rbt->root;
	while (node->key != key) {
		if (key < node->key) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	return node;
}

Node *treeMinimum(Node *x) {
	if (x != leaf) {
		while (x->left != leaf) {
			x = x->left;
		}
	}
	return x;
}

void rbtDeleteFixUp(Tree *rbt, Node *x) {
	while (x != rbt->root && x->color == BLACK) {
		rbt->root->parent == NULL;
		Node *w = NULL, *xParent = x->parent;
		if (x == xParent->left) {
			w = xParent->right;
			if (w->color == RED) {
				w->color = BLACK;
				xParent->color = RED;
				leftRotate(xParent);
				w = xParent->right;
			}
			if (w->left->color == BLACK
				&& w->right->color == BLACK) {
				w->color = RED;
				x = xParent;
			}
			else if (w->right->color == BLACK) {
				w->left->color = BLACK;
				w->color = RED;
				rightRotate(w);
				w = xParent->right;
			}
			if (w->right->color == RED) {
				w->color = xParent->color;
				xParent->color = BLACK;
				w->right->color = BLACK;
				leftRotate(xParent);
				x = rbt->root;
			}
		}
		else {
			w = xParent->left;
			if (w->color == RED) {
				w->color = BLACK;
				xParent->color = RED;
				rightRotate(xParent);
				w = xParent->left;
			}
			if (w->left->color == BLACK
				&& w->right->color == BLACK) {
				w->color = RED;
				x = xParent;
			}
			else if (w->left->color == BLACK) {
				w->right->color = BLACK;
				w->color = RED;
				leftRotate(w);
				w = xParent->left;
			}
			if (w->left->color == RED) {
				w->color = xParent->color;
				xParent->color = BLACK;
				w->left->color = BLACK;
				rightRotate(xParent);
				x = rbt->root;
			}
		}
		leaf->color = BLACK;
	}
	x->color = BLACK;
}

void rbtDeleteNode(Tree *rbt, int key) {
	Node *z = findNode(rbt, key);
	Node *x = leaf, *y = leaf;
	if (z->left == leaf || z->right == leaf) { // 자식 1개 또는 leaf
		y = z;
	}
	else { // 자식 2개
		y = treeMinimum(z->right);
	}

	if (y->left != leaf) {
		x = y->left;
	}
	else {
		x = y->right;
	}

	x->parent = y->parent;

	if (y->parent == NULL) {
		rbt->root = x;
	}
	else if (y == y->parent->left) {
		y->parent->left = x;
	}
	else {
		y->parent->right = x;
	}

	if (y != z) {
		z->key = y->key;
	}

	if (y->color == BLACK) {
		rbtDeleteFixUp(rbt, x);
	}
	delete y;
}

string getColor(Tree *rbt, int key) {
	Node *node = rbt->root;
	while (node->key != key) {
		if (key < node->key) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	return node->color == RED ? "RED" : "BLACK";
}

int main() {
	ifstream inp("rbt.inp");
	ofstream out("rbt.out");
	rbt->root = leaf;
	leaf->left = leaf;
	leaf->right = leaf;
	while (true) {
		char o; int k;
		inp >> o >> k;
		if (k == -1) {
			return 0;
		}
		switch (o) {
		case 'i':
			rbtInsertNode(rbt, k);
			break;
		case 'd':
			rbtDeleteNode(rbt, k);
			break;
		case 'c':
			out << "color(" << k << "): " << getColor(rbt, k) << '\n';
			break;
		}
	}
}
