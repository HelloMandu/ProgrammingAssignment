#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define MAX 10000

typedef struct Graph {
	int E; // 도착 정점
	int weight; // 가중치
}Graph;

Graph graph[MAX][MAX];
int length[MAX];
bool check[MAX]; // 방문햇는지 체크
int Stack[MAX];
int Queue[MAX];
int top = -1;
int front = -1, rear = -1;

int compare(const void *arg1, const void * arg2) {
	int v1 = ((Graph *)arg1)->E;
	int v2 = ((Graph *)arg2)->E;
	if (v1 > v2) return 1;
	else return -1;
}

int DFS_Traversal(int V, int n) {
	int result = 0;
	Stack[++top] = V;
	check[V] = true; // 방문한 정점 true
	while (top != -1) { // stack이 공백이 될 때 까지
		for (int i = 0; i < length[V]; i++) { // 시작정점의 인접 정점을 검사
			if (check[graph[V][i].E] != true) { // 도착 정점이 방문하지 않은 정점일 때
				check[graph[V][i].E] = true; // 방문한 정점 true
				Stack[++top] = graph[V][i].E; // 정점을 push
				result += graph[V][i].weight; // 가중치+
				V = graph[V][i].E; // 정점을 바꿈
				i = -1; // 처음부터 돌기 위해
			}
		}
		V = Stack[--top]; // 다돌았을 때 top을 정점으로
	}
	memset(check, false, sizeof(bool) * n); // check를 초기화
	return result;
}

int BFS_Traversal(int V, int n) { // 너비우선탐색, Queue
	int result = 0;
	Queue[++rear] = V; // 시작정점 push
	check[V] = true; // 방문한 정점 true
	while (front != rear) { // Queue가 공백이 될 때 까지
		V = Queue[++front]; // 다돌았을 때 top을 정점으로 
		for (int i = 0; i < length[V]; i++) { // 시작정점의 인접 정점을 검사
			if (check[graph[V][i].E] != true) { // 도착 정점이 방문하지 않은 정점일 때
				check[graph[V][i].E] = true; // 방문한 정점 true
				Queue[++rear] = graph[V][i].E; // 정점을 push
				result += graph[V][i].weight; // 가중치+
			}
		}
	}
	front = -1; rear = -1;
	memset(check, false, sizeof(bool) * n); // check를 초기화
	return result;
}

int main() {
	FILE *inp = fopen("graph.inp", "rt");
	FILE *out = fopen("graph.out", "wt");
	int t; // 총테스트케이스
	int n, m; // 정점, 에지의 개수
	int V, E, weight; // 시작
	int k, start; // 순회할 정점의 수, 시작정점

	fscanf(inp, "%d", &t);
	while (t--) {
		fscanf(inp, "%d %d", &n, &m);
		for (int i = 0; i < m; i++) {
			fscanf(inp, "%d %d %d", &V, &E, &weight);
			graph[V][length[V]].E = E; // 시작
			graph[V][length[V]++].weight = weight;
			graph[E][length[E]].E = V; // 시작
			graph[E][length[E]++].weight = weight;
		}

		for (int i = 0; i < n; i++) // 정점을 깊이순으로 정렬
			qsort(graph[i], length[i], sizeof(Graph), compare);

		fscanf(inp, "%d", &k); // 시작정점의 수
		while (k--) {
			fscanf(inp, "%d", &start); // 시작정점
			fprintf(out, "n=%d m=%d start=%d DFS:%d BFS:%d\n", n, m, start, DFS_Traversal(start, n), BFS_Traversal(start, n));
		}
		memset(length, 0, sizeof(int)*n);
	}
	return 0;
}