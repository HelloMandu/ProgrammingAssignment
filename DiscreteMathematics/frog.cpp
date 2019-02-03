#include<fstream>
#include<vector>
using namespace std;

typedef struct Stone {
	char kind; // 돌의 종류
	int width; // 너비
	bool check; // 돌을 밟앗는지 체크
}Stone;

vector<Stone> stone;

int Foward(int N, int D) { // 정방향
	int max = 0; //최대 거리
	int width = 0; // 실제 이동한 거리
	for (int i = 1; i <= N; i++) {
		if (stone[i].kind == 'B') { // B일때 무조건 밟음
			if (max < stone[i].width - width) // 이전 이동거리가 현재이동거리보다 작을 시
				max = stone[i].width - width; // 최대 이동거리 갱신
			width = stone[i].width; // 이동거리 갱신
		}
		else if (stone[i].kind == 'S' && stone[i].check != true) { // S일때 안밟은 경우
			if (max < stone[i].width - width) // 이전 이동거리가 현재이동거리보다 작을 시
				max = stone[i].width - width; // 최대 이동거리 갱신
			width = stone[i].width; // 이동거리 갱신
			stone[i].check = true; // 밟음 check
			if (stone[i + 1].kind == 'S') // 다음 밟을 돌이 S인 경우 한칸 건너 뜀
				i++;
		}
	}
	if (D - width > max) // 마지막 남은 경로의 거리가 최대 거리일 때
		max = D - width;
	return max;
}

int Reverse(int N, int D) { // 역방향
	int max = 0; //최대 거리
	int width = D; // 실제 이동한 거리
	for (int i = N; i > 0; i--) {
		if (stone[i].kind == 'B') { // B일때 무조건 밟음
			if (max < width - stone[i].width) // 이전 이동거리가 현재이동거리보다 작을 시
				max = width - stone[i].width; // 최대 이동거리 갱신
			width = stone[i].width; // 이동거리 갱신
		}
		else if (stone[i].kind == 'S' && stone[i].check != true) { // S일때 안밟은 경우
			if (max < width - stone[i].width) // 이전 이동거리가 현재이동거리보다 작을 시
				max = width - stone[i].width; // 최대 이동거리 갱신
			width = stone[i].width; // 이동거리 갱신
			stone[i].check = true; // 밟음 check
			if (stone[i - 1].kind == 'S') // 다음 밟을 돌이 S인 경우 한칸 건너 뜀
				i--;
		}
	}
	if (width > max) // 마지막 남은 경로의 거리가 최대 거리일 때
		max = width;
	return max;
}

int frog(int N,/*돌의 개수*/ int D/*너비*/) {
	int foward = Foward(N, D);
	int reverse = Reverse(N, D);
	return foward > reverse ? foward : reverse; // 정방향과 역방향 중 큰 수를 리턴
}

int main() {
	ifstream inp("frog.inp");
	ofstream out("frog.out");
	int t; // 테스트케이스
	int N, D; // 돌의 개수, 강의 너비
	char bar;
	inp >> t;
	for (int i = 1; i <= t; i++) {
		inp >> N >> D;
		stone.resize(N + 2); // stone 할당
		for(int j = 1; j <= N; j++)
			inp >> stone[j].kind >> bar >> stone[j].width;
		out << "Case " << i << ": " << frog(N,D) << endl;
		stone.clear(); // stone 반환
	}
	inp.close(); out.close();
	return 0;
}