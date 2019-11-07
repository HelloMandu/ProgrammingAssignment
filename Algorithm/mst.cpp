#include<fstream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

ifstream inp("mst.inp");
ofstream out("mst.out");

struct Node {
	int index, v, e, weight;
};

int n, m;
vector<vector<Node> > graph;
vector<int> result;

struct compare {
	bool operator()(Node &a, Node &b) {
		if (a.weight == b.weight) {
			return a.index > b.index;
		}
		return a.weight > b.weight;
	}
};

priority_queue<Node, vector<Node>, compare> heap;

void printResult(int weight) {
	out << weight << '\n';
	for (int i = 0; i < result.size(); i++) {
		out << result[i] << '\n';
	}
	result.clear();
}

int getParent(int parent[], int x) {
	if (parent[x] == x) { return x; }
	return parent[x] = getParent(parent, parent[x]);
}

void unionParent(int parent[], int a, int b) {
	a = getParent(parent, a);
	b = getParent(parent, b);
	if (a < b) { parent[b] = a; }
	else { parent[a] = b; }
}

bool findParent(int parent[], int a, int b) {
	a = getParent(parent, a);
	b = getParent(parent, b);
	if (a == b) { return true; }
	else { return false; }
}

void kruskal() {
	int allWeight = 0;
	int parent[10001] = { 0 };
	for (int i = 0; i < n; i++) {
		parent[i] = i;
	}
	while (!heap.empty()) {
		Node node = heap.top(); heap.pop();
		if (!findParent(parent, node.v, node.e)) {
			allWeight += node.weight;
			unionParent(parent, node.v, node.e);
			result.push_back(node.index);
		}
	}
	out << "Tree edges by Kruskal algorithm: ";
	printResult(allWeight);
}

void prim(int start) {
	int allWeight = 0;
	bool isVisit[10001] = { 0 };
	isVisit[start] = true;
	for (int i = 0; i < graph[start].size(); i++) {
		heap.push(graph[start][i]);
	}
	while (!heap.empty()) {
		Node vertex = heap.top(); heap.pop();
		if (!isVisit[vertex.e]) {
			isVisit[vertex.e] = true;
			allWeight += vertex.weight;
			result.push_back(vertex.index);
			for (int i = 0; i < graph[vertex.e].size(); i++) {
				heap.push(graph[vertex.e][i]);
			}
		}
	}
	out << "Tree edges by Prim algorithm with starting vertex " << start << ": ";
	printResult(allWeight);
}

int main() {
	inp >> n >> m;
	graph.resize(n);
	for (int i = 0; i < m; i++) {
		int v, e, weight;
		inp >> v >> e >> weight;
		graph[v].push_back({ i, v, e, weight });
		graph[e].push_back({ i, e, v, weight });
		heap.push({ i, v, e, weight });
	}
	kruskal();
	prim(0);
	prim(n / 2);
	prim(n - 1);
	return 0;
}