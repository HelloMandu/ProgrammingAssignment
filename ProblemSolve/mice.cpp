#include<fstream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;

typedef long long lint;

struct Location {
	lint x, y;
	bool operator<(const Location &a) {
		if (x == a.x) {
			return y < a.y;
		}
		return x < a.x;
	}
	bool operator<=(const Location &a) {
		if (x == a.x) {
			return y <= a.y;
		}
		return x <= a.x;
	}
};

struct Node {
	int edge, capacity;
	Node *reverse;
	Node(int edge, int capacity) : edge(edge), capacity(capacity), reverse(NULL) {}
};

int n, k, h, m; // ¸ð¼­¸®¼ö, ÃÖ´ë¼ö, Áã±¸¸Û¼ö, Áã¼ö
Location edges[1001], holes[251], mices[251];
int level[1001], work[1001], sink;
vector<vector<Node*> > network;

inline int ccw(Location pivot, Location a, Location b) {
	lint result = 1LL * pivot.x * a.y + a.x * b.y + b.x * pivot.y - 1LL * pivot.x * b.y - a.x * pivot.y - b.x * a.y;
	if (result > 0) { return 1; }
	else if (result < 0) { return -1; }
	return 0;
}

bool canFlow(Node node) {
	return level[node.edge] == -1 && node.capacity > 0;
}

bool networkFlow() {
	memset(level, -1, sizeof(level));
	queue<int> Queue; Queue.push(0);
	level[0] = 0;
	while (!Queue.empty()) {
		int node = Queue.front(); Queue.pop();
		for (int i = 0; i < network[node].size(); i++) {
			Node &next = *network[node][i];
			if (canFlow(next)) {
				level[next.edge] = level[node] + 1;
				Queue.push(next.edge);
			}
		}
	}
	return level[sink] != -1;
}

int renualFlow(int node = 0, int flow = 987654321) {
	if (node == sink) {
		return flow;
	}
	for (int &i = work[node]; i < network[node].size(); i++) {
		Node &next = *network[node][i];
		if (level[next.edge] == level[node] + 1 && next.capacity > 0) {
			int f = renualFlow(next.edge, min(flow, next.capacity));
			if (f > 0) {
				next.capacity -= f;
				next.reverse->capacity += f;
				return f;
			}
		}
	}
	return 0;
}

bool isIntersect(Location a, Location b, Location c, Location d) {
	int ab = ccw(a, b, c) * ccw(a, b, d),
		cd = ccw(c, d, a) * ccw(c, d, b);
	if (ab == 0 && cd == 0) {
		if (b < a) { swap(a, b); }
		if (d < c) { swap(c, d); }
		return c <= b && a <= d;
	}
	return ab <= 0 && cd <= 0;
}

bool canSeek(Location mice, Location hole) {
	bool flag = false;
	for (int i = 0; i < n; i++) {
		if (isIntersect(mice, hole, edges[i % n], edges[(i + 1) % n])) {
			if (flag) { return false; }
			flag = true;
		}
	}
	return true;
}

void makeNetwork() {
	network.resize(m + h + 2);
	for (int i = 1; i <= m; i++) {
		Node *a = new Node(i, 1);
		Node *b = new Node(0, 0);
		a->reverse = b;
		b->reverse = a;
		network[0].push_back(a);
		network[i].push_back(b);
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= h; j++) {
			if (canSeek(mices[i], holes[j])) {
				Node *a = new Node(m + j, 1);
				Node *b = new Node(i, 0);
				a->reverse = b;
				b->reverse = a;
				network[i].push_back(a);
				network[m + j].push_back(b);
			}
		}
	}
	for (int i = m + 1; i <= m + h; i++) {
		Node *a = new Node(sink, k);
		Node *b = new Node(i, 0);
		a->reverse = b;
		b->reverse = a;
		network[i].push_back(a);
		network[sink].push_back(b);
	}
}

void init(ifstream &inp) {
	inp >> n >> k >> h >> m;
	sink = m + h + 1;
	network.clear();
	for (int i = 0; i < n; i++) {
		inp >> edges[i].x >> edges[i].y;
	}
	for (int i = 1; i <= h; i++) {
		inp >> holes[i].x >> holes[i].y;
	}
	for (int i = 1; i <= m; i++) {
		inp >> mices[i].x >> mices[i].y;
	}
}

int main() {
	ifstream inp("mice.inp");
	ofstream out("mice.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		int maxFlow = 0;
		init(inp);
		makeNetwork();
		while (networkFlow()) {
			memset(work, 0, sizeof(int) * sink);
			while (true) {
				int flow = renualFlow();
				if (!flow) { break; }
				maxFlow += flow;
			}
		}
		out << (maxFlow == m ? "Possible" : "Impossible") << '\n';
	}
	return 0;
}
