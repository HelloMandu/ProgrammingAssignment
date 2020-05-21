#include<fstream>
#include<algorithm>
#include<vector>
#include<stack>
#include<cmath>
#include<cstring>
using namespace std;

struct SafeInspection {
	int machineNum, start;
	bool isFirst;
	bool operator<(const SafeInspection &a) {
		return start < a.start;
	}
};

int n, d;
vector<vector<int> > graph, rGraph;
SafeInspection schedule[20002];
bool isVisit[20002];
int scc[20002];
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


void rDfs(int node, int set) {
	isVisit[node] = true;
	scc[node] = set;
	for (int i = 0; i < rGraph[node].size(); i++) {
		if (!isVisit[rGraph[node][i]]) {
			rDfs(rGraph[node][i], set);
		}
	}
}

void doSCC() {
	memset(isVisit, false, sizeof(isVisit));
	for (int i = 0; i < 2 * n; i++) {
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
}

bool getResult() {
	for (int i = 0; i < n; i++) {
		if (scc[i] == scc[i + n]) {
			return false;
		}
	}
	return true;
}

int r(SafeInspection a) {
	return a.isFirst ? a.machineNum + n : a.machineNum;
}

int f(SafeInspection a) {
	return a.isFirst ? a.machineNum : a.machineNum + n;
}

void makeGraph() {
	sort(schedule, schedule + 2 * n);
	for (int i = 0; i < 2 * n - 1; i++) {
		for (int j = i + 1; j < 2 * n && (schedule[i].start + d) > schedule[j].start; j++) {
			int r1 = r(schedule[i]), r2 = r(schedule[j]);
			int f1 = f(schedule[i]), f2 = f(schedule[j]);
			graph[r1].push_back(f2), graph[r2].push_back(f1);
			rGraph[f1].push_back(r2), rGraph[f2].push_back(r1);
		}
	}
}

int main() {
	ifstream inp("factory.inp");
	ofstream out("factory.out");
	int testcase;
	inp >> testcase;
	for (int t = 1; t <= testcase; t++) {
		graph.clear(); rGraph.clear();
		inp >> n >> d;
		graph.resize(2 * n); rGraph.resize(2 * n);
		for (int i = 0; i < n; i++) {
			int e1, e2;
			inp >> e1 >> e2;
			if (e1 > e2) { swap(e1, e2); }
			schedule[i] = { i, e1, true };
			schedule[i + n] = { i, e2, false };
		}
		makeGraph();
		doSCC();
		out << "Test Case #" << t << ": " << (getResult() ? "Possible" : "Impossible") << '\n';
	}
	return 0;
}