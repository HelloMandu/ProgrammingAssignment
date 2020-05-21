#include<fstream>
#include<vector>
#include<stack>
#include<cstring>
#define BLUE 'B'
#define RED 'R'
using namespace std;

struct Select {
	int lamp;
	char color;
};

int k, n;
vector<vector<int> > graph;
vector<vector<int> > rGraph;
bool isVisit[20005];
int scc[20005];
stack<int> Stack;

int r(Select node) {
	return node.color == RED ? node.lamp : node.lamp + k;
}

int f(Select node) {
	return node.color == RED ? node.lamp + k : node.lamp;
}

bool hasEdge(int rA, int fB) {
	for (int i = 0; i < graph[rA].size(); i++) {
		if (graph[rA][i] == fB) {
			return true;
		}
	}
	return false;
}

void connect(Select a, Select b) {
	int rA = r(a), rB = r(b);
	int fA = f(a), fB = f(b);
	if (!hasEdge(rA, fB)) {
		graph[rA].push_back(fB);
		graph[rB].push_back(fA);
		rGraph[fA].push_back(rB);
		rGraph[fB].push_back(rA);
	}

}

void init(ifstream &inp) {
	memset(scc, -1, sizeof(scc));
	Select select[3];
	inp >> k >> n;
	graph.resize(20005);
	rGraph.resize(20005);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			inp >> select[j].lamp >> select[j].color;
		}
		for (int i = 0; i < 3; i++) {
			int cur = i, next = (i + 1) % 3;
			connect(select[cur], select[next]);
		}
	}
}

void dfs(int node) {
	isVisit[node] = true;
	for (int i = 0; i < graph[node].size(); i++) {
		if (!isVisit[graph[node][i]]) {
			dfs(graph[node][i]);
		}
	}
	Stack.push(node);
}


void rDfs(int node, int set) {
	isVisit[node] = true;
	scc[node] = set;
	for (int i = 0; i < rGraph[node].size(); i++) {
		if (!isVisit[rGraph[node][i]]) {
			rDfs(rGraph[node][i], set);
		}
	}
}

int getResult() {
	for (int i = 1; i <= k; i++) {
		if (scc[i] == scc[i + k]) {
			return -1;
		}
	}
	return 1;
}

int main() {
	ifstream inp("show.inp");
	ofstream out("show.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		init(inp);
		memset(isVisit, false, sizeof(isVisit));
		for (int i = 1; i <= 2 * k; i++) {
			if (!isVisit[i]) {
				dfs(i);
			}
		}
		memset(isVisit, false, sizeof(isVisit));
		int cnt = 0;
		while (!Stack.empty()) {
			int node = Stack.top(); Stack.pop();
			if (!isVisit[node]) {
				rDfs(node, cnt);
				cnt++;
			}
		}
		out << getResult() << '\n';
		graph.clear(); rGraph.clear();
	}
	return 0;
}
