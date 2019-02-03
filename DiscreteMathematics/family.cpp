#include<fstream>
#include<string.h>
#define MAX 500000
using namespace std;

typedef struct Pedigree{
	int distance; // 거리를 저장
	bool check; // 시작여부
}Pedigree;

int graph[MAX];
Pedigree pedigree[MAX]; // 족보정보 저장

int family(int n) {
	int max = 0; // 반환할 결과값
	int distance = 0; // 대손의 최댓값
	for (int child = 1; child <= n; child++) { // n개의 정점을 시작정점으로 
		pedigree[child].check = true; // 시작한 정점 true
		int parent = graph[child]; // 부모의 값을 저장
		while (parent != 0) { // 루트에 도달할 때 까지 반복
			if (pedigree[parent].check == true) { // 도달한 부모의 정점이 거리를 가지고 있을 때
				distance += pedigree[parent].distance + 1; // 부모정점의 루트와의 거리를 더함
				break;
			}
			parent = graph[parent]; // 부모 -> 자식
			distance++; // 거리 + 1;
		}
		max = max > distance ? max : distance; // 거리의 최댓값 갱신
		pedigree[child].distance = distance; // parent정점으로부터의 거리
		distance = 0; // 거리를 0으로 초기화
	}
	memset(graph, 0, sizeof(int) * (n + 1));
	memset(pedigree, 0, sizeof(Pedigree) * (n + 1));
	return max + 1; // 정점을 포함
}

int main() {
	ifstream inp("family.inp");
	ofstream out("family.out");
	int t; // 총 경우의 수
	int n; // 정점의 수
	int V, E; // 시작 정점, 도착 정점
	inp >> t;
	while (t--) {
		inp >> n;
		for (int i = 0; i < n - 1; i++) {
			inp >> V >> E;
			graph[E] = V; // index = 도착정점, V = 시작정점
		}
		out << family(n) << endl;
	}
	return 0;
}