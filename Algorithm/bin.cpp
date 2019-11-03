#include<fstream>
#include<algorithm>
#include<cstring>
#define INFINITY 987654321
using namespace std;

int n, m;
int home[501];
int distanceSum[501][501];
int cache[501][501];

int main() {
	ifstream inp("bin.inp");
	ofstream out("bin.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		inp >> n >> m;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= m; j++) {
				cache[i][j] = INFINITY;
			}
		}
		memset(distanceSum, 0, sizeof(distanceSum));
		for (int i = 1; i <= n; i++) {
			inp >> home[i];
		}
		sort(home + 1, home + n + 1);
		for (int i = 1; i <= n; i++) {
			for (int j = i; j <= n; j++) {
				distanceSum[i][j] = distanceSum[i][j - 1] + home[j] - home[i + (j - i) / 2];
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				for (int k = 1; k <= i; k++) {
					cache[i][j] = min(cache[i][j], cache[i - k][j - 1] + distanceSum[i - k + 1][i]);
				}
			}
		}
		out << cache[n][m] << '\n';
	}
	inp.close(); out.close();
	return 0;
}