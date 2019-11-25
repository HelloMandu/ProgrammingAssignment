#include<fstream>
#include<algorithm>
#include<cstring>
using namespace std;

int card[1001], cache[2][1001][1001];

int solution(int start, int finish, bool turn) {
	int &ret = cache[turn][start][finish];
	if (ret != -1) {
		return ret;
	}
	else if (start == finish) {
		return ret = turn ? card[start] : 0;
	}
	if (turn) {
		ret = max(solution(start + 1, finish, !turn) + card[start], solution(start, finish - 1, !turn) + card[finish]);
	}
	else {
		ret = min(solution(start + 1, finish, !turn), solution(start, finish - 1, !turn));
	}
	return ret;
}

int main() {
	ifstream inp("card.inp");
	ofstream out("card.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		memset(cache, -1, sizeof(cache));
		int n;
		inp >> n;
		for (int i = 0; i < n; i++) {
			inp >> card[i];
		}
		out << solution(0, n - 1, true) << '\n';
	}
	return 0;
}