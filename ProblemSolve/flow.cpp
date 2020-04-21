#include<fstream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
#define INF 987654321
#define MAX 10001

struct Node {
	int edge, capacity, flow;
	Node *reverse;

	int residualFlow() { // 잔여 유량
		return capacity - flow;
	}
};

vector<vector<Node*> > graph;
int parent[MAX];
Node* route[MAX];
int result = 0;
bool canFlow(Node *node) { // 유량이 흐를 수 있는지 판단
	return parent[node->edge] == -1 && node->residualFlow();
}

bool networkFlow(int n) {
	memset(parent, -1, sizeof(int) * n);
	queue<int> Queue;  Queue.push(0);
	while (!Queue.empty()) {
		int node = Queue.front(); Queue.pop();
		for (int i = 0; i < graph[node].size(); i++) {
			Node *cur = graph[node][i];
			if (canFlow(cur)) {
				parent[cur->edge] = node;
				route[cur->edge] = cur;
				Queue.push(cur->edge);
				if (cur->edge == n - 1) {
					return true;
				}
			}
		}
	}
	return false;
}

void renualFlow(int n) {
	int cur = n - 1, flow = INF;
	while (cur) {
		flow = min(flow, route[cur]->residualFlow());
		cur = parent[cur];
	}
	cur = n - 1;
	while (cur) {
		route[cur]->flow += flow;
		route[cur]->reverse->flow += flow;
		cur = parent[cur];
	}
	result += flow;
}

int main() {
	ifstream inp("flow.inp");
	ofstream out("flow.out");
	int n;
	inp >> n;
	graph.resize(n);
	while (true) {
		int i, j, w;
		inp >> i >> j >> w;
		if (i == -1) {
			while (networkFlow(n)) {
				renualFlow(n);
			}
			out << result;
			graph.clear(); inp.close(); out.close();
			return 0;
		}
		Node *node1 = new Node({ j, w, 0, NULL }), *node2 = new Node({ i, w, 0, NULL });
		node1->reverse = node2; node2->reverse = node1;
		graph[i].push_back(node1); graph[j].push_back(node2);
	}
}