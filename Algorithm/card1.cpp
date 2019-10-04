#include<fstream>
#include<algorithm>
#include<cstring>
using namespace std;

int card[1001];
int cache[1001][3];
int main() {
	ifstream inp("card.inp");
	ofstream out("card.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		int n;
		inp >> n;
		for (int i = 0; i < n; i++) {
			inp >> card[i];
		}
		for (int i = 0; i < 3; i++) {
			cache[i][0] = cache[i][1] = cache[i][2] = card[i];
		}
		cache[3][0] = max(cache[1][1], cache[1][2]) + card[3];
		cache[3][1] = max(cache[0][0], cache[0][2]) + card[3];
		cache[3][2] = -987654321;
		for (int i = 4; i < n; i++) {
			cache[i][0] = max(cache[i - 2][1], cache[i - 2][2]) + card[i];
			cache[i][1] = max(cache[i - 3][0], max(cache[i - 3][1], cache[i - 3][2])) + card[i];
			cache[i][2] = max(cache[i - 4][0], max(cache[i - 4][1], cache[i - 4][2])) + card[i];
		}
		out << max(cache[n - 1][0], max(cache[n - 1][1], cache[n - 1][2])) << '\n';
		memset(cache, 0, sizeof(cache));
	}
	return 0;
}