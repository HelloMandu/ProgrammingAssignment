#include<fstream>
#include<string.h>
#define MAX 1000
using namespace std;

int Qsize = 0; // Queue의 수

void Entrance(int entrance[], int people) {
	Qsize = 0;
	bool check = false;
	for (int i = 0; i <= Qsize; i++) {
		if (entrance[i] < people) { // 새로운 사람의 순서가 더 높을 시
			entrance[i] = people; // 새로운 사람으로 갱신
			check = true; // 갱신 완료
			break;
		}
	}
	if(!check) // 갱신이 되지 않았을 시 Qsize를 한 칸 늘림
		entrance[++Qsize] = people;
}

int main() {
	ifstream inp("entrance.inp");
	ofstream out("entrance.out");
	int t; // 총 테스트 케이스
	int n, people; // 총 사람 수
	int entrance[MAX] = { 0 };
	inp >> t;
	while (t--) {
		inp >> n;
		for (int i = 0; i < n; i++) {
			inp >> people;
			Entrance(entrance, people);
		}
		out << Qsize + 1 << '\n';
		Qsize = 0; memset(entrance, 0, sizeof(int) * n);
	}
	return 0;
}