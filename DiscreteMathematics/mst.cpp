#include<fstream>
#include<vector>
#include<queue>
#include<algorithm>
#define MAX 10000
using namespace std;

typedef struct Graph {
	int E; // 도착정점
	int weight; // 가중치
}Graph;

vector< vector<Graph> > graph; // 그래프 선언
vector<Graph> result; // 결과를 저장
bool visit[MAX]; // 방문여부 체크

struct compare { // 최소힙 비교
	bool operator()(Graph &a, Graph &b) {
		return a.weight > b.weight;
	}
};

bool Sort_compare(Graph &a, Graph &b) { // 정렬 비교
	if (a.E == b.E) // 총정점의 수가 같을시 비용을 비교
		return a.weight < b.weight;
	return a.E < b.E; // 총정점의 수 비교
}

void Prim_Algorithm(int start) { // 프림알고리즘
	priority_queue< Graph, vector<Graph>, compare > heap; // 최소힙 선언
	visit[start] = true; // 시작정점 true
	int All_cost = 0, V_count = 1;
	for (int i = 0; i < graph[start].size(); i++) { // 시작정점의 노드들을 넣음
		if (!visit[graph[start][i].E])// 방문하지 않은 정점에 한하여 push
			heap.push(graph[start][i]);
	}
	while (!heap.empty()) {
		Graph Min_node = heap.top(); heap.pop(); // 모든 인접정점 중 최소비용을 가지는 정점 pop
		int V = Min_node.E; int cost = Min_node.weight; // 비용과 정점을 저장
		if (!visit[V]) { // 방문하지 않은 정점에 한하여
			visit[V] = true; // 방문한 정점 true
			V_count++; // 정점의 수++
			All_cost += cost; // 비용++
			for (int i = 0; i < graph[V].size(); i++) {
				if (!visit[graph[V][i].E]) // 방문하지 않은 정점에한하여 push
					heap.push(graph[V][i]);
			}
		}
	}
	result.push_back({ V_count, All_cost }); // 결과를 저장
}

int main() {
	ifstream inp("mst.inp");
	ofstream out("mst.out");
	int n, m; // 정점의 수, 에지의 수
	int V, E, weight; // 시작 정점, 도착정점, 가중치
	inp >> n >> m;
	graph.resize(n);
	while (m--) {
		inp >> V >> E >> weight;
		graph[V].push_back({ E, weight });
		graph[E].push_back({ V, weight });
	}
	for (int V = 0; V < n; V++) {
		if(!visit[V]) // 방문안한 정점에 한하여 
			Prim_Algorithm(V);
	}
	sort(result.begin(), result.end(), Sort_compare); // 정렬
	for (int i = 0; i < result.size(); i++)
		out << result[i].E << ' ' << result[i].weight << '\n';
	inp.close(); out.close();
	return 0;
}