#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#pragma warning(disable :4996)


/*트리의 노드를 구성*/
typedef struct TreeNode {
	int key;
	struct TreeNode *left;
	struct TreeNode *right;
}TreeNode;


/*트리 root노드를 구성*/
typedef struct Tree {
	TreeNode *root;
	int arr[100001];
	int size;
}Tree;

/*새로운 트리를 구성*/
Tree *makeTree() {
	Tree *newTree = (Tree*)malloc(sizeof(Tree));
	newTree->root = NULL;
	newTree->size = 0;
	memset(newTree->arr, -1, sizeof(newTree->arr));
	return newTree;
}

/*새로운 TreeNode를 동적할당*/
TreeNode *CreateNode(int key) {
	TreeNode *newnode = (TreeNode*)malloc(sizeof(TreeNode));
	newnode->key = key;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}

/*이진트리에 노드를 삽입*/
void InsertNode(Tree *tree, int key) {
	int root = 1;
	TreeNode *child = tree->root;
	TreeNode *parent = NULL;
	while (child != NULL) {
		if (key == child->key) {
			return;
		}
		parent = child;
		if (key < child->key) {
			child = child->left;
			root = root * 2;
		}
		else {
			child = child->right;
			root = root * 2 + 1;
		}
	}
	TreeNode *newnode = CreateNode(key);
	tree->arr[root] = key;
	tree->size++;
	if (tree->root == NULL) {
		tree->root = newnode;
	}
	else if (key < parent->key) {
		parent->left = newnode;
	}
	else {
		parent->right = newnode;
	}
}


/*이진트리에 노드를 삭제, 삭제할 노드가 없을 경우 삭제하지 않음*/
void DeleteNode(Tree *tree, int key) {
	TreeNode *parent = NULL, *child, *p, *succ, *succ_parent;
	p = tree->root;
	int root = 1;
	while ((p != NULL) && (p->key != key)) {  //삭제할 노드의 위치 탐색 
		parent = p;
		if (key < p->key) {
			p = p->left;
			root = root * 2;
		}
		else {
			p = p->right;
			root = root * 2 + 1;
		}
	}

	/*삭제할 노드가 없는 경우 */
	if (p == NULL) return;

	/*삭제할 노드가 단말노드인 경우*/
	if ((p->left == NULL) && (p->right == NULL)) {
		if (parent != NULL) {
			if (parent->left == p) {
				parent->left = NULL;
			}
			else {
				parent->right = NULL;
			}
		}
		else {
			tree->root = NULL;
		}
	}
	/*삭제할 노드가 한 개의 자식노드를 가진 경우*/
	else if ((p->left == NULL) || (p->right == NULL)) {
		if (p->left != NULL) {
			child = p->left;
		}
		else {
			child = p->right;
		}
		if (parent != NULL) {
			if (parent->left == p) {
				parent->left = child;
			}
			else {
				parent->right = child;
			}
		}
		else {
			tree->root = child;
		}
	}
	/*삭제할 노드가 두 개의 자식노드를 가진 경우*/
	else {
		succ_parent = p; succ = p->right;
		while (succ->left != NULL) {
			succ_parent = succ;
			succ = succ->left;
		}
		if (succ_parent->left == succ) {
			succ_parent->left = succ->right;
		}
		else {
			succ_parent->right = succ->right;
		}
		p->key = succ->key;
		p = succ;
	}
	free(p);
	tree->arr[root] = -1;
	tree->size--;
}

/*트리의 높이를 계산하여 반환*/
int GetHeight(TreeNode *root) {
	if (root == NULL) {
		return 0;
	}
	int leftH = GetHeight(root->left); // 왼쪽 서브 트리 높이 계산
	int rightH = GetHeight(root->right); // 오른쪽 서브 트리 높이 계산
	return leftH > rightH ? leftH + 1 : rightH + 1; // 큰 값의 높이를 반환
}

/*두 서브 트리의 높이의 차를 반환*/
int Getbalance(TreeNode *root) {
	if (root == NULL) {
		return 0;
	}
	return GetHeight(root->left) - GetHeight(root->right); // leftHeight - rightHeight
}

/*트리가 균형잡혀있는 상태인지 확인*/
int isBalanced(TreeNode *root) {
	if (root == NULL) {
		return 1;
	}
	int BF = Getbalance(root); // 균형인수를 계산
	if (BF > 1) { // 균형인수가 1보다 큰 경우
		return 0;
	}
	else if (BF < -1) { // 균형인수가 1보다 작은 경우
		return 0;
	}
	return isBalanced(root->left) && isBalanced(root->right);
}

/*완전이진트리인지 확인*/
int is_complete_binary_tree(Tree *tree) {
	/*트리의 노드가 연속으로 되어있지 않은 경우 완전이진트리가 될 수 없음*/
	for (int i = 1; i <= tree->size; i++) {
		if (tree->arr[i] == -1) {
			return 0;
		}
	}
	return 1;
}

/*지정한 키값을 가진 노드의 높이를 반환*/
int level(TreeNode *root, int key, int height) {
	/*지정한 키값을 가진 노드가 없는 경우 0을 반환*/
	if (root == NULL) {
		return 0;
	}
	/*지정한 키값을 찾은 경우 높이를 반환*/
	else if (root->key == key) {
		return height;
	}
	/*왼쪽자식 노드를 통해 키값을 탐색*/
	else if (root->key > key) {
		return level(root->left, key, height + 1);
	}
	/*오른쪽자식 노드를 통해 키값을 탐색*/
	else {
		return level(root->right, key, height + 1);
	}
}

/*루트에서부터 모든 자식노드까지의 경로의 길이의 합을 반환*/
int path_length(TreeNode *root, int height) {
	/*노드가 NULL인 경우 0을 반환*/
	if (root == NULL) {
		return 0;
	}
	/*현재 노드의 높이와 자식노드들의 높이를 합하여 반환*/
	return height + path_length(root->left, height + 1) + path_length(root->right, height + 1);
}

/*이진트리를 좌우대칭*/
void reverse(TreeNode *root) {
	/*해당노드가 NULL인 경우 반환*/
	if (root == NULL) {
		return;
	}
	/*왼쪽자식과 오른쪽자식을 swap*/
	TreeNode *temp;
	temp = root->right;
	root->right = root->left;
	root->left = temp;
	/*왼쪽자식을 reverse*/
	reverse(root->left);
	/*오른쪽자식을 reverse*/
	reverse(root->right);
}

/*트리를 전위순회하여 결과를 보여줌*/
void preorder(TreeNode *root) {
	TreeNode *p = root;
	if (p != NULL) {
		printf("%d ", p->key);
		preorder(p->left);
		preorder(p->right);
	}
}

int main() {
	/*트리생성*/
	Tree *tree = makeTree();
	/*트리에 노드 삽입*/
	InsertNode(tree, 5);
	InsertNode(tree, 2);
	InsertNode(tree, 7);
	InsertNode(tree, 1);
	InsertNode(tree, 3);
	InsertNode(tree, 6);
	InsertNode(tree, 8);

	/*구성한 트리의 결과를 전위순회하여 결과 출력*/
	printf("현재까지 구성된 트리의 결과(전위순회) : ");
	preorder(tree->root);
	printf("\n\n-------------------------------------------------------------------\n\n");

	printf("현재 트리는 완전이진 트리인가? : %c\n", is_complete_binary_tree(tree) ? 'O' : 'X');
	printf("\n-------------------------------------------------------------------\n\n");


	printf("key 값 0 삽입\n");
	InsertNode(tree, 0);
	printf("현재 트리는 완전이진 트리인가? : %c\n", is_complete_binary_tree(tree) ? 'O' : 'X');
	printf("\n-------------------------------------------------------------------\n\n");


	printf("key 값 9 삽입\n");
	InsertNode(tree, 9);
	printf("현재 트리는 완전이진 트리인가? : %c\n", is_complete_binary_tree(tree) ? 'O' : 'X');
	printf("\n-------------------------------------------------------------------\n\n");

	printf("키 값 5의 level : %d\n", level(tree->root, 5, 0));
	printf("키 값 3의 level : %d\n", level(tree->root, 3, 0));
	printf("키 값 9의 level : %d\n", level(tree->root, 9, 0));
	printf("\n-------------------------------------------------------------------\n\n");

	printf("현재 트리는 균형 이진 트리인가? : %c\n", isBalanced(tree->root) ? 'O' : 'X');
	printf("\n-------------------------------------------------------------------\n\n");

	printf("key 값 10 삽입\n");
	InsertNode(tree, 10);
	printf("현재 트리는 완전이진 트리인가? : %c\n", is_complete_binary_tree(tree) ? 'O' : 'X');
	printf("\n-------------------------------------------------------------------\n\n");
	
	printf("모든 자식노드까지의 경로의 길이 : %d\n", path_length(tree->root, 0));
	printf("\n-------------------------------------------------------------------\n\n");

	printf("key 값 10 삭제\n");
	DeleteNode(tree, 10);
	printf("모든 자식노드까지의 경로의 길이 : %d\n", path_length(tree->root, 0));
	printf("\n-------------------------------------------------------------------\n\n");

	reverse(tree->root);
	printf("좌우 대칭된 트리의 전위순회 결과 : ");
	preorder(tree->root);
	printf("\n\n");

	return 0;
}