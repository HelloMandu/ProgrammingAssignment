#include<fstream>
#include<algorithm>
#include<vector>
#include<stack>
#include<cstring>
using namespace std;

vector<vector<int> > graph;
vector<vector<int> > rGraph;
int n, m;
bool isVisit[10001];
stack<int> Stack;

void dfs(int node) {
	isVisit[node] = true;
	for (int i = 0; i < graph[node].size(); i++) {
		if (!isVisit[graph[node][i]]) {
			dfs(graph[node][i]);
		}
	}
	Stack.push(node);
}



void init(ifstream &inp) {
	inp >> n >> m;
	graph.resize(n);
	rGraph.resize(n);
	for (int i = 0; i < m; i++) {
		int u, v; inp >> u >> v;
		graph[u].push_back(v);
		rGraph[v].push_back(u);
	}
}

void rDfs(int node) {
	isVisit[node] = true;
	for (int i = 0; i < rGraph[node].size(); i++) {
		if (!isVisit[rGraph[node][i]]) {
			rDfs(rGraph[node][i]);
		}
	}
}

int main() {
	ifstream inp("scc.inp");
	ofstream out("scc.out");
	init(inp);
	memset(isVisit, false, sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		if (!isVisit[i]) {
			dfs(i);
		}
	}
	memset(isVisit, false, sizeof(int) * n);
	int result = 0;
	while (!Stack.empty()) {
		int node = Stack.top(); Stack.pop();
		if (!isVisit[node]) {
			rDfs(node);
			result++;
		}
	}
	out << result;
	return 0;
}
