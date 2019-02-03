#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> V; // 시작정점을 저장
vector<int> E; // 도착정점을 저장

int BSearch(int len, int target) {
	int first = 0;
	int last = len - 1;
	int mid = 0;
	while (first <= last) {
		mid = (first + last) / 2;
		if (E[mid] == target) // 타겟을 찾은 경우
			return mid;
		else {
			if (E[mid] > target) // mid가 타겟보다 큰경우
				last = mid - 1;
			else // mid가 타겟보다 작은 경우
				first = mid + 1;
		}
	}
	return -1;
}

int tree() {
	int root = -1; // root를 -1로 초기화
	sort(V.begin(), V.end()); // V정렬
	sort(E.begin(), E.end()); // E 정렬
	for (int i = 1; i < V.size(); i++) { // i - 1을 참조해야하므로 i = 1;
		if (V[i] != V[i - 1]) { // 다음 index가 다른 값일 때 root 탐색
			if (!binary_search(E.begin(), E.end(), V[i - 1])) { // 찾는 값이 없을 때 root조건에 성립
				if (root != -1)// root가 두개인 경우
					return -1;
				else // root가 없을 시 갱신
					root = V[i - 1];
			}
		}
		if (E[i] == E[i - 1]) // 자신을 가리키는 간선이 두개 이상일 때
			return -1;
	}
	if (!binary_search(E.begin(), E.end(), V[V.size() - 1])) { // 찾는 값이 없을 때 root조건에 성립
		if (root != -1)// root가 두개인 경우
			return -1;
		else // root가 없을 시 갱신
			root = V[V.size() - 1];
	}
	return root;
}

int main() {
	ifstream inp("tree.inp");
	ofstream out("tree.out");
	int v, e; // 시작정점, 도착정점
	int TreeNum = 0; // tree의 번호
	while (true) {
		inp >> v >> e;
		if (v == -1 && e == -1) // v, e가 -1일 때 프로그램 종료
			break;
		else if (v == 0 && e == 0) {//  v, e가 0일 때 트리 입력 끝
			out << "Test Case " << ++TreeNum << ": " << tree() << "\n";
			V.clear(); E.clear(); // V와 E를 반환
		}
		else { // 시작정점과 도착정점을 삽입
			V.push_back(v); E.push_back(e);
		}
	}
	return 0;
}