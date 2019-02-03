#include<fstream>
#include<vector>
using namespace std;
#define infinity 1000000
ifstream inp("dijkstra.inp");
ofstream out("dijkstra.out");

typedef struct Graph {
	int E = 0; // 도착정점
	int weight = 0; // 그래프의 가중치
	int edge_number = 0; // 경로가 생성된 순서
}Graph;

typedef struct Dijkstra {
	bool check = false; // 갱신확정여부
	bool none = false; // 최단거리가 한번도 갱신되지 않았을 경우
	int distance = 0; // 최단거리
	int last_index = 0; // 갱신된 index
	int edge_number = 0; // 갱신된 edge의 순서
}Dijkstra;

vector< vector<Graph> > graph;
Dijkstra dist[10000];

int Min_index(int n) { // 최소거리를 가지는 index검색
	int min = infinity;
	int index = -1; // 끝났을 경우
	for (int i = 0; i < n; i++) { // 정점의 갯수 만큼 반복
		if (dist[i].distance < min && dist[i].check != true && dist[i].none == true && dist[i].distance != 0) {
			// 기존의 경로보다 작고, 갱신된 적이 없는 경우, 최단거리가 있으며, 한번이라도 갱신이 된 경우
			min = dist[i].distance; // 최단거리를 설정
			index = i; // 최단거리를 가지는 index
		}
	}
	return (index != -1 ? index : 0); // 모든 경로의 갱신이 끝났을 시 0 출력
}

void dijkstra(int n) {
	int E; // 도착정점
	int index = 0; // 시작은 항상 0부터
	dist[index].check = true; // 정점선택 후 true값으로 갱신
	dist[index].none = true; // 한번도 갱신되지 않은 경우 갱신
	for (int i = 0; i < n - 1; i++) { // 시작정점을 정했으므로 n-1번만큼 진행
		for (int t = 0; t < graph[index].size(); t++) {
			E = graph[index][t].E; // 도착정점을 저장
			if (dist[E].check != true) { // 아직 갱신되지 않은 index
				if (dist[E].none != true) {// 최단거리가 아직 한번도 갱신 되지 않는 경우
					dist[E].distance = dist[index].distance + graph[index][t].weight; // 최단거리 갱신
					dist[E].last_index = index; dist[E].none = true; // 갱신된 정점, 한번도 갱신되지 않은 경우 갱신
					dist[E].edge_number = graph[index][t].edge_number; // edge의 순서 갱신
				}
				else if (dist[index].distance + graph[index][t].weight <= dist[E].distance) {
					// 현재 그 정점까지의 거리 (dist[index].distance) + 정점 w까지의 거리가
					// 기존의 w정점까지의 거리보다 가깝다면 그 정보를 갱신해준다.
					if (dist[index].distance + graph[index][t].weight == dist[E].distance) { // 최단경로가 같을 때
						if (dist[E].edge_number < graph[index][t].edge_number) //새로운 경로가 최대경로보다 작을 시
							continue;
					}
					dist[E].distance = dist[index].distance + graph[index][t].weight; // 최단거리 갱신
					dist[E].last_index = index; // 갱신되었을 시 마지막 index를 저장
					dist[E].edge_number = graph[index][t].edge_number;  // edge의 순서
				}
			}
		}
		index = Min_index(n); // 최소거리를 가지는 index를 찾는다
		dist[index].check = true; // 최단거리를 찾은 경우
	}
}

void dijkstra_path(int n) { // 다익스트라 경로를 출력
	if (dist[n].distance == 0) {// 마지막 시작점에 도달 했을 때
		out << "V0" << ' ';
		return;
	}
	else
		dijkstra_path(dist[n].last_index); // 갱신되게 한 정점을 찾아감
	out << "V" << n << ' ';
}

int main() {
	int n, m; // 정점의수, 간선의 수
	int V; // 시작정점
	inp >> n >> m; // 정점의 수, 간선의 수
	graph.resize(n);
	for (int edge_number = 0; edge_number < m; edge_number++) { // 간선의 수 만큼 입력
		Graph input;
		inp >> V >> input.E >> input.weight; // 시작, 도착, 간선
		input.edge_number = edge_number;
		graph[V].push_back(input);
	}
	dijkstra(n);//다익스트라 알고리즘
	for (int i = 1; i < n; i++) { // 정점순서대로 출력
		dijkstra_path(i); // 경로를 출력
		if (dist[i].distance != 0)
			out << "(" << dist[i].distance << ")" << endl; // 거리를 출력
		else
			out << "V" << i << ' ' << "(-1)" << endl;
	}
	graph.clear();
	inp.close(); out.close();
	return 0;
}

/*#include<fstream>
using namespace std;
#define infinity 1000000
ifstream inp("dijkstra.inp");
ofstream out("dijkstra.out");

typedef struct Dijkstra {
	bool check = false; // 갱신확정여부
	bool none = false; // 최단거리가 한번도 갱신되지 않았을 경우
	int distance = 0; // 최단거리
	int last_index = 0; // 갱신된 index
	int edge_number = 0; // 갱신된 edge의 순서
}Dijkstra;

typedef struct Graph {
	int weight = infinity; // 그래프의 가중치
	int edge_number = 0; // 경로가 생성된 순서
}Graph;

Graph graph[10000][10000];
Dijkstra dist[10000];

int Min_index(int n) { // 최소거리를 가지는 index검색
	int min = infinity;
	int index = -1; // 끝났을 경우
	for (int i = 0; i < n; i++) { // 정점의 갯수 만큼 반복
		if (dist[i].distance < min && dist[i].check != true && dist[i].none == true && dist[i].distance != 0) {
			// 기존의 경로보다 작고, 갱신된 적이 없는 경우, 최단거리가 있으며, 한번이라도 갱신이 된 경우
			min = dist[i].distance; // 최단거리를 설정
			index = i; // 최단거리를 가지는 index
		}
	}
	return (index != -1 ? index : 0); // 모든 경로의 갱신이 끝났을 시 -1 출력
}

void dijkstra(int n, int m) {
	int index = 0; // 시작은 항상 0부터
	dist[index].check = true; // 정점선택 후 true값으로 갱신
	dist[index].none = true; // 한번도 갱신되지 않은 경우 갱신
	for (int i = 0; i < n - 1; i++) { // 시작정점을 정했으므로 n-1번만큼 진행
		for (int t = 0; t < n; t++) {
			if (dist[t].check != true) { // 아직 갱신되지 않은 index
				if (dist[t].none != true && graph[index][t].weight != infinity) {// 최단거리가 아직 한번도 갱신 되지 않는 경우
					dist[t].distance = dist[index].distance + graph[index][t].weight; // 최단거리 갱신
					dist[t].last_index = index; dist[t].none = true; // 갱신된 정점, 한번도 갱신되지 않은 경우 갱신
					dist[t].edge_number = graph[index][t].edge_number; // edge의 순서 갱신
				}
				else if (dist[index].distance + graph[index][t].weight <= dist[t].distance) {
					// 현재 그 정점까지의 거리 (dist[index].distance) + 정점 w까지의 거리가
					// 기존의 w정점까지의 거리보다 가깝다면 그 정보를 갱신해준다.
					if (dist[index].distance + graph[index][t].weight == dist[t].distance) { // 최단경로가 같을 때
						if (dist[t].edge_number > graph[index][t].edge_number) //새로운 경로가 최대경로보다 작을 시
							continue;
					}
					dist[t].distance = dist[index].distance + graph[index][t].weight; // 최단거리 갱신
					dist[t].last_index = index; // 갱신되었을 시 마지막 index를 저장
					dist[t].edge_number = graph[index][t].edge_number;  // edge의 순서
				}
			}
		}
		index = Min_index(n); // 최소거리를 가지는 index를 찾는다
		dist[index].check = true; // 최단거리를 찾은 경우
	}
}

void dijkstra_path(int n) { // 다익스트라 경로를 출력
	if (dist[n].distance == 0) {// 마지막 시작점에 도달 했을 때
		out << "V0" << ' ';
		return;
	}
	else
		dijkstra_path(dist[n].last_index); // 갱신되게 한 정점을 찾아감
	out << "V" << n << ' ';
}

int main() {
	int n, m; // 정점의수, 간선의 수
	int V, E, weight; // 시작 정점, 도착 정점, 간선
	inp >> n >> m;
	for (int edge_number = 0; edge_number < m; edge_number++) { // 간선의 수 만큼 입력
		inp >> V >> E >> weight; // 시작, 도착, 간선
		graph[V][E].weight = weight; // 다익스트라 갱신
		graph[V][E].edge_number = edge_number; // 경로의 순서 갱신
	}
	dijkstra(n, m);//다익스트라 알고리즘
	for (int i = 1; i < n; i++) { // 정점순서대로 출력
		dijkstra_path(i); // 경로를 출력
		if (dist[i].distance != 0)
			out << "(" << dist[i].distance << ")" << endl; // 거리를 출력
		else
			out << "V" << i << ' ' << "(-1)" << endl;
	}
	inp.close(); out.close();
	return 0;
}*/