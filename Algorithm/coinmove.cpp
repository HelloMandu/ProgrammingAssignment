#include<fstream>
#include<algorithm>
#include<cstring>
using namespace std;

int p, k, s;
bool arr[1000001][8];

bool canWin(int idx, int stair) {
	if (idx != 0 && idx % p == 0) {
		return false;
	}
	for (int i = 1; i <= k; i++) {
		if (i != stair) {
			if (arr[idx][i]) {
				return false;
			}
		}
	}
	return true;
}

void coinmove() {
	for (int i = 1; i <= s; i++) {
		if (i % p != 0 || i == s) {
			for (int j = 1; j <= k; j++) {
				if (i - j >= 0) {
					arr[i][j] = canWin(i - j, j);
				}
			}
		}
	}
}

int winningNumber() {
	for (int i = 1; i <= k; i++) {
		if (arr[s][i]) {
			return s - i;
		}
	}
	return -1;
}

int main() {
	ifstream inp("coinmove.inp");
	ofstream out("coinmove.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		inp >> p >> k >> s;
		coinmove();
		out << winningNumber() << '\n';
		memset(arr, false, sizeof(arr));
	}
	inp.close(); out.close();
	return 0;
}