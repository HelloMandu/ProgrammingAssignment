#include<fstream>
#include<algorithm>
#define INF 987654321
using namespace std;

int n, m, k;
int cost[101][101];
bool dot[101][101];
int cache[101][101];

int main() {
	ifstream inp("path2.inp");
	ofstream out("path2.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		inp >> n >> m >> k;
		for (int i = 0; i < k; i++) {
			int y, x;
			inp >> y >> x;
			dot[y][x] = true;
		}

	}
	return 0;
}