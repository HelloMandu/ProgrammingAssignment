#include<fstream>
#include<algorithm>
#include<vector>
#include<cstring>
#define MAX 100002
#define INF -987654321
using namespace std;

struct Node {
	int weight, left, right;
};

int preorder[MAX], n;
Node tree[MAX];

void makeTree(int preRoot, int begin, int end) {
	if (begin <= end) {
		int inoRoot = preorder[preRoot];
		int leftSize = preorder[preRoot] - begin,
			rightsize = end - preorder[preRoot];
		if (leftSize > 0) {
			tree[inoRoot].left = preorder[preRoot + 1];
			makeTree(preRoot + 1, begin, inoRoot - 1);
		}
		if (rightsize > 0) {
			tree[inoRoot].right = preorder[preRoot + leftSize + 1];
			makeTree(preRoot + leftSize + 1, inoRoot + 1, end);
		}
	}
}

void init(ifstream &inp) {
	inp >> n;
	memset(tree, -1, sizeof(Node) * n);
	for (int i = 0; i < n; i++) {
		inp >> tree[i].weight;
	}
	for (int i = 0; i < n; i++) {
		inp >> preorder[i];
	}
}

int maxFath(int root, int &result) {
	if (root == -1) { return INF; }
	Node &node = tree[root];
	if (node.left == -1 && node.right == -1) {
		result = max(result, node.weight);
		return node.weight;
	}
	int leftSum = maxFath(node.left, result),
		rightSum = maxFath(node.right, result);
	if (node.left != -1 && node.right != -1) {
		result = max(result, leftSum + rightSum + node.weight);
	}
	return max(leftSum, rightSum) + node.weight;
}

int main() {
	ifstream inp("path.inp");
	ofstream out("path.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		int result = INF;
		init(inp);
		makeTree(0, 0, n - 1);
		maxFath(preorder[0], result);
		out << result << '\n';
	}
	return 0;
}