#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct TreeNode {
	int key;
	struct TreeNode *left;
	struct TreeNode *right;
}TreeNode;

TreeNode *LL_rotate(TreeNode *root) { // LL회전
	TreeNode *child = root->left;
	root->left = child->right;
	child->right = root;
	return child;
}

TreeNode *RR_rotate(TreeNode *root) { // RR회전
	TreeNode *child = root->right;
	root->right = child->left;
	child->left = root;
	return child;
}

TreeNode *LR_rotate(TreeNode *root) { // LR회전
	TreeNode *child = root->left;
	root->left = RR_rotate(child);
	return LL_rotate(root);
}

TreeNode *RL_rotate(TreeNode *root) { // RL회전
	TreeNode *child = root->right;
	root->right = LL_rotate(child);
	return RR_rotate(root);
}

int GetHeight(TreeNode *root) { // 트리의 높이를 계산하여 반환
	if (root == NULL)
		return 0;
	int leftH = GetHeight(root->left); // 왼쪽 서브 트리 높이 계산
	int rightH = GetHeight(root->right); // 오른쪽 서브 트리 높이 계산
	return leftH > rightH ? leftH + 1 : rightH + 1; // 큰 값의 높이를 반환
}

int Getbalance(TreeNode *root) { // 두 서브 트리의 높이의 차를 반환 
	if (root == NULL)
		return 0;
	return GetHeight(root->left) - GetHeight(root->right); // leftHeight - rightHeight
}

TreeNode *rebalance(TreeNode *root) {
	int BF = Getbalance(root); // 균형인수를 계산
	if (BF > 1) { // 균형인수가 1보다 큰 경우
		if (Getbalance(root->left) > 0) // 왼쪽자식 균형인수가 양수이면 LL
			root = LL_rotate(root);
		else // 왼쪽자식 균형인수가 음수이면 LR
			root = LR_rotate(root);
	}
	else if (BF < -1) { // 균형인수가 1보다 작은 경우
		if (Getbalance(root->right) < 0) // 오른쪽자식 균형인수가 음수이면 RR
			root = RR_rotate(root);
		else // 오른쪽자식 균형인수가 양수이면 RL
			root = RL_rotate(root);
	}
	return root;
}

TreeNode *insert_AVL_Node(TreeNode *root, int key) { // AVL노드 삽입
	if (root == NULL) { // 루트가 없을 때
		root = (TreeNode*)malloc(sizeof(TreeNode));
		root->key = key;
		root->left = NULL;
		root->right = NULL;
	}
	else if (key < root->key) { // 키값이 루트보다 작을 떄
		root->left = insert_AVL_Node(root->left, key);
		root = rebalance(root);
	}
	else if (key > root->key) {  // 키값이 루트보다 클 떄
		root->right = insert_AVL_Node(root->right, key);
		root = rebalance(root);
	}
	return root;
}

TreeNode *delete_AVL_Node(TreeNode *root, int key) { // AVL노드 삭제
	if (root == NULL) // 삭제할 노드가 없는 경우
		return root;
	else if (key < root->key) // 키값이 작을 경우
		root->left = delete_AVL_Node(root->left, key);
	else if (key > root->key)// 키값이 클 경우
		root->right = delete_AVL_Node(root->right, key);
	else { // 키 값을 찾은 경우
		if (root->left == NULL && root->right == NULL) { // 삭제할 노드가 단말노드인 경우
			free(root); // 단말노드 삭제
			return NULL; // NULL을 반환
		}
		else if (root->left == NULL || root->right == NULL) { // 삭제할 노드가 자식 노드를 한 개 가진 경우
			TreeNode *child;
			if (root->left != NULL)
				child = root->left;
			else
				child = root->right;
			free(root);
			return child;
		}
		else { // 삭제할 노드가 자식 노드를 두 개 가진 경우
			TreeNode *succ_parent = root, *succ = root->left;
			while (succ->right != NULL) { // 왼쪽 서브트리에서 후계자 찾기
				succ_parent = succ;
				succ = succ->right;
			}
			if (succ_parent->left == succ)
				succ_parent->left = succ->left;
			else
				succ_parent->right = succ->left;
			root->key = succ->key;
			free(succ);
		}
	}
	return rebalance(root);
}

void preorder(TreeNode *root, FILE *out) { // 전위순회
	if (root) {
		fprintf(out, "%d ", root->key);
		preorder(root->left, out);
		preorder(root->right, out);
	}
}

int main() {
	FILE *inp = fopen("hw4.inp", "r");
	FILE *out = fopen("hw4.out", "w");
	if (inp == NULL) fprintf(stderr, "can't open %s\n", "hw4.inp");
	if (out == NULL) fprintf(stderr, "can't open %s\n", "hw4.out");
	TreeNode *root = NULL; // 트리의 루트노드 생성
	int key; // 키값
	char enter = ' '; // 공백
	while (enter != '\n') { // 노드 삽입
		fscanf(inp, "%d%c", &key, &enter);
		root = insert_AVL_Node(root, key);
	}
	preorder(root, out); fprintf(out, "\n"); // 전위 순회
	while (enter != '\n') { // 노드 삭제
		fscanf(inp, "%d%c", &key, &enter);
		root = delete_AVL_Node(root, key);
	}
	preorder(root, out); fprintf(out, "\n*"); // 전위 순회
	fclose(inp); fclose(out);
	return 0;
}