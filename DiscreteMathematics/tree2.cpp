#include<fstream>
#include<vector>
#include<stack>
#include<string.h>
#define root 0
using namespace std;

typedef struct Tree {
	int child; // 자식정점
	int weight; // 가중치
}Tree;

vector< vector<Tree> > tree;
bool check[100000]; // 방문여부체크
int root_length; // 루트로부터의 최대값
int result; // 결과값

int MAX_length(int V, int n) { // 해당정점으로부터 최대거리
	stack<int> Stack;
	stack<int> weight;
	int result = 0;
	int sum = 0;
	Stack.push(V); // 시작정점 push
	while (!Stack.empty()) { // stack이 공백이 될 때 까지
		for (int i = 0;  i < tree[V].size(); i++) { // 시작정점의 인접 정점을 검사
			if (!check[tree[V][i].child]) {
				check[tree[V][i].child] = true;
				Stack.push(tree[V][i].child); // 정점을 push
				sum += tree[V][i].weight;
				weight.push(tree[V][i].weight);
				V = tree[V][i].child; // 정점을 바꿈
				i = -1;
			}
		}
		if (sum > result)
			result = sum;
		Stack.pop(); // 인접정점을 다 돌았을 때 pop
		if (!Stack.empty()) {
			V = Stack.top(); // 다돌았을 때 top을 정점으로
			sum -= weight.top();
			weight.pop();
		}
	}
	memset(check, false, sizeof(bool) * n);
	return result;
}


void tree_update(int V, int length, int n) {
	if (tree[V].size() != 0) { // 리프노드가 아닐때
		for (int i = 0; i < tree[V].size(); i++) {
			int max_length = length + tree[V][i].weight + MAX_length(tree[V][i].child , n);
			tree[V][i].weight += root_length - max_length; // 그 간선의 최대 길이와 총 최대길이의 차이만큼 더해줌
			result += root_length - max_length; // 거기서 발생한 비용을 더해줌
			tree_update(tree[V][i].child, length + tree[V][i].weight, n); // child의 자식 노드 순회
		}
	}
}

int main() {
	ifstream inp("tree.inp");
	ofstream out("tree.out");
	int t, n;
	int parent, weight;
	inp >> t;
	while (t--) {
		inp >> n;
		tree.resize(n);
		for (int i = 1; i < n; i++) {
			inp >> parent >> weight;
			tree[parent].push_back({ i, weight });
		}
		root_length = MAX_length(root, n);
		tree_update(root, 0, n);
		out << result << '\n';
		result = 0; tree.clear();
	}
	inp.close();
	out.close();
	return 0;
}