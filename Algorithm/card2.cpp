#include<fstream>
#include<algorithm>
#include<cstring>
using namespace std;

int card[1001], cache[2][1001][1001];

int solution(int start, int end, bool turn) {
	int &ret = cache[turn][start][end];
	if (ret != -1) {
		return ret;
	}
	else if (start == end) {
		return ret = turn ? card[start] : 0;
	}
	return ret = turn ? max((solution(start + 1, end, !turn) + card[start]), (solution(start, end - 1, !turn) + card[end]))
		: min((solution(start + 1, end, !turn)), (solution(start, end - 1, !turn)));
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