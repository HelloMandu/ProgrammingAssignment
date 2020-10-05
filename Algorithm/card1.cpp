#include<fstream>
#include<algorithm>
#include<cstring>
using namespace std;
int n;
int card[1001];
int cache[3][1001];
int main() {
	ifstream inp("card1.inp");
	ofstream out("card1.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		memset(cache, 0, sizeof(cache));
		inp >> n;
		for (int i = 0; i < n; i++) {
			inp >> card[i];
		}
		for (int i = 0; i < 3; i++) {
			cache[0][i] = cache[1][i] = cache[2][i] = card[i];
		}
		cache[0][3] = card[1] + card[3];
		cache[1][3] = card[0] + card[3];
		cache[2][3] = -987654321;
		for (int i = 4; i < n; i++) {
			cache[0][i] = max({ cache[1][i - 2], cache[2][i - 2] }) + card[i];
			cache[1][i] = max({ cache[0][i - 3], cache[1][i - 3], cache[2][i - 3] }) + card[i];
			cache[2][i] = max({ cache[0][i - 4], cache[1][i - 4], cache[2][i - 4] }) + card[i];
		}
		out << max({ cache[0][n - 1], cache[1][n - 1], cache[2][n - 1] }) << '\n';
	}
	return 0;
}