#include<fstream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;

class Graph {
public:
	int E;
	int weight;
};

class Traversal {
private:
	enum { MAX = 10000 };
	bool check[MAX];
public:
	vector< vector<Graph> > graph;
	void createGraph(const int n);
	void setGraph(const int V, const int E, const int weight);
	int DFS_Traversal(int V, int n);
	int BFS_Traversal(int V, int n);
	void Print_Travarsal(ofstream &out, int n, int m, int start);
};

bool compare(const Graph &p1, const Graph &p2) { //오름차순 정렬 비교함수
	return p1.E < p2.E;
}

void Traversal::createGraph(const int n) {
	graph.resize(n);
}

void Traversal::setGraph(const int V, const int E, const int weight) {
	graph[V].push_back({ E, weight }); // 시작
	graph[E].push_back({ V, weight }); // 도착
}

int Traversal::DFS_Traversal(int V, int n) { // 깊이우선탐색, Stack
	stack<int> Stack; // 스택
	int result = 0;
	Stack.push(V); // 시작정점 push
	check[V] = true; // 방문한 정점 true
	while (!Stack.empty()) { // stack이 공백이 될 때 까지
		for (int i = 0; i < graph[V].size(); i++) { // 시작정점의 인접 정점을 검사
			if (check[graph[V][i].E] != true) { // 도착 정점이 방문하지 않은 정점일 때
				check[graph[V][i].E] = true; // 방문한 정점 true
				Stack.push(graph[V][i].E); // 정점을 push
				result += graph[V][i].weight; // 가중치+
				V = graph[V][i].E; // 정점을 바꿈
				i = -1; // 처음부터 돌기 위해
			}
		}
		Stack.pop(); // 인접정점을 다 돌았을 때 pop
		if (!Stack.empty())
			V = Stack.top(); // 다돌았을 때 top을 정점으로
	}
	memset(check, false, sizeof(bool) * n); // check를 초기화
	return result;
}

int Traversal::BFS_Traversal(int V, int n) { // 너비우선탐색, Queue
	queue<int> Queue; // 큐
	int result = 0;
	Queue.push(V); // 시작정점 push
	check[V] = true; // 방문한 정점 true
	while (!Queue.empty()) { // Queue가 공백이 될 때 까지
		for (int i = 0; i < graph[V].size(); i++) { // 시작정점의 인접 정점을 검사
			if (check[graph[V][i].E] != true) { // 도착 정점이 방문하지 않은 정점일 때
				check[graph[V][i].E] = true; // 방문한 정점 true
				Queue.push(graph[V][i].E); // 정점을 push
				result += graph[V][i].weight; // 가중치+
			}
		}
		Queue.pop(); // 인접정점을 다 돌았을 때 pop
		if (!Queue.empty())
			V = Queue.front(); // 다돌았을 때 top을 정점으로
	}
	memset(check, false, sizeof(bool) * n); // check를 초기화
	return result;
}

void Traversal::Print_Travarsal(ofstream &out, int n, int m, int start) {
	out << "n=" << n << " m=" << m << " start=" << start
		<< " DFS:" << DFS_Traversal(start, n) << " BFS:" << BFS_Traversal(start, n)
		<< '\n';
}

int main() {
	ifstream inp("graph.inp");
	ofstream out("graph.out");
	int t; // 총테스트케이스
	int n, m; // 정점, 에지의 개수
	int V, E, weight; // 시작, 도착, 가중치
	int k, start; // 순회할 정점의 수, 시작정점
	inp >> t;
	Traversal traversal; // 순회 class생성
	while (t--) {
		inp >> n >> m;
		traversal.createGraph(n); // 정점의 수 만큼 할당
		for (int i = 0; i < m; i++) {
			inp >> V >> E >> weight;
			traversal.setGraph(V, E, weight);
		}
		for (int i = 0; i < n; i++) // 정점을 깊이순으로 정렬
			sort(traversal.graph[i].begin(), traversal.graph[i].end(), compare);
		inp >> k; // 시작정점의 수
		while (k--) {
			inp >> start; // 시작정점
			traversal.Print_Travarsal(out, n, m, start); // 순회결과 출력
		}
		traversal.graph.clear(); // graph반환
	}
	inp.close(); out.close();
	return 0;
}