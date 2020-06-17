#include<fstream>
#include<stack>
using namespace std;
#pragma warning(disable:4996)

FILE *inp = fopen("transform.inp", "r");
FILE *out = fopen("transform.out", "w");

int n, k;
int inorder[20001];
int preorder[20001];
char bracket[40002];

void makeTree(int preRoot, int begin, int end) {
	if (begin <= end) {
		fprintf(out, "(");
		int inoRoot = preorder[preRoot];
		int leftSize = inoRoot - begin, rightSize = end - inoRoot;
		if (leftSize > 0) {
			makeTree(preRoot + 1, begin, inoRoot - 1);
		}
		fprintf(out, ")");
		if (rightSize > 0) {
			makeTree(preRoot + leftSize + 1, inoRoot + 1, end);
		}
	}
}

int main() {
	int testcase;
	fscanf(inp, "%d", &testcase);
	while (testcase--) {
		fscanf(inp, "%d %d\n", &n, &k);
		fprintf(out, "%d ", n);
		if (!k) {
			for (int i = 0; i < n; i++) {
				fscanf(inp, "%d", &inorder[i]);
				preorder[inorder[i]] = i;
			}
			makeTree(1, 0, n - 1);
		}
		else {
			int root = 1;;
			stack<int> Stack;
			fscanf(inp, "%s\n", bracket);
			for (int i = 0; i < 2 * n; i++) {
				if (bracket[i] == '(') {
					Stack.push(root++);
				}
				else {
					fprintf(out, "%d ", Stack.top());
					Stack.pop();
				}
			}
		}
		fprintf(out, "\n");
	}
	return 0;
}