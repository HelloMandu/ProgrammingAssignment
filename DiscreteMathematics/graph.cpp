#include<fstream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
#include<string.h>
#define MAX 10000
using namespace std;

struct Graph {
	int E; // 도착 정점
	int weight; // 가중치
};

vector< vector<Graph> > graph; // graph
bool check[MAX]; // 방문햇는지 체크
stack<int> Stack; // 스택
queue<int> Queue; // 큐

bool compare(Graph &p1, Graph &p2) { //오름차순 정렬 비교함수
	return p1.E < p2.E;
}

int DFS_Traversal(int V, int n) { // 깊이우선탐색, Stack
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

int BFS_Traversal(int V, int n) { // 너비우선탐색, Queue
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

int main() {
	ifstream inp("graph.inp");
	ofstream out("graph.out");

	int t; // 총테스트케이스
	int n, m; // 정점, 에지의 개수
	int V; // 시작
	int k, start; // 순회할 정점의 수, 시작정점

	inp >> t;
	while (t--) {
		inp >> n >> m;
		graph.resize(n); // 정점의 수 만큼 할당
		for (int i = 0; i < m; i++) {
			Graph input; // 도착, 가중치
			inp >> V >> input.E >> input.weight;
			graph[V].push_back(input); // 시작
			swap(V, input.E); // V와 E를 swap
			graph[V].push_back(input); // 도착
		}

		for (int i = 0; i < n; i++) // 정점을 깊이순으로 정렬
			sort(graph[i].begin(), graph[i].end(), compare);

		inp >> k; // 시작정점의 수
		while (k--) {
			inp >> start; // 시작정점
			out << "n=" << n << " m=" << m << " start=" << start
				<< " DFS:" << DFS_Traversal(start, n) << " BFS:" << BFS_Traversal(start, n)
				<< endl;
		}
		graph.clear(); // graph반환
	}
	inp.close(); out.close();
	return 0;
}