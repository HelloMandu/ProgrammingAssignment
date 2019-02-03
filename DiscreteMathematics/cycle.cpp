#include<fstream>
#include<vector>
#include<queue>
#include<string.h>
#define MAX 1000000
using namespace std;

int state[MAX]; // 0: 방문안함 1: 홀수 2: 짝수

bool OddCycle(vector< vector<int> > &graph) {
	queue<int> Queue; // Queue선언
	int V = 0; // 시작은 0
	Queue.push(V); // 시작정점 push
	state[V] = 2; // 상태를 저장
	int level = 1; // level이 짝수인지 홀수인지 저장
	int prepush = 1, pushcount = 0, popcount = 0; // 이전 push값을 저장, push한 횟수를 저장, pop한 횟수를 저장
	while (!Queue.empty()) {
		for (int i = 0; i < graph[V].size(); i++) {
			if (state[V] == state[graph[V][i]]) // 상태가 같은 경우
				return true; // 홀수 사이클이므로 true반환
			else if (state[graph[V][i]] == 0) { // 한번도 방문하지 않은 정점일 때
				state[graph[V][i]] = level; // 상태를 저장
				Queue.push(graph[V][i]); // 방문한 정점을 push
				pushcount++; // push한 수를 저장
			}
		}
		Queue.pop(); // 인접정점을 다 돌았을 때 pop
		popcount++; // pop한 횟수를 저장
		if (!Queue.empty())
			V = Queue.front(); // 다돌았을 때 top을 정점으로
		if (prepush == popcount) { // push횟수와 pop횟수가 겹칠 때 level++
			level = (level == 1) ? 2 : 1;
			prepush = pushcount;
			pushcount = 0; popcount = 0;
		}
	}
	return false; // 홀수 사이클이 아닌경우
}

int main() {
	ifstream inp("cycle.inp");
	ofstream out("cycle.out");
	int t; // 총 테스트케이스
	int n, m; // 정점의 수, 간선의 수
	int V, E; // 시작 정점, 도착정점
	vector< vector<int> > graph; // 그래프선언
	inp >> t;
	while (t--) {
		inp >> n >> m;
		graph.resize(n); // 정점의 수만큼 공간할당
		for (int i = 0; i < m; i++) {
			inp >> V >> E;
			graph[V].push_back(E); // 시작정점
			graph[E].push_back(V); // 도착정점
		}
		if (OddCycle(graph))
			out << "O\n";
		else
			out << "X\n";
		memset(state, 0, sizeof(int) * n); // check를 초기화
		graph.clear();
	}
	return 0;
}