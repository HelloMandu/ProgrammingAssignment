#include<fstream>
#include<algorithm>
#include<vector>
#define INF 987654321
using namespace std;
int n, m;
int arr[201][201];
int cache[201][201];
void getPath(ofstream& out, int y = n - 1, int x = m - 1) {
	if (y != 0 || x != 0) {
		if (y > 0 && x > 0) {
			if (cache[y - 1][x] <= cache[y][x - 1]) {
				getPath(out, y - 1, x);
			}
			else {
				getPath(out, y, x - 1);
			}
		}
		else if (y == 0) {
			getPath(out, y, x - 1);
		}
		else {
			getPath(out, y - 1, x);
		}
	}
	out << '(' << y << ' ' << x << ')' << '\n';
}

int main() {
	ifstream inp("gridpath.inp");
	ofstream out("gridpath.out");
	inp >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			inp >> arr[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cache[i][j] = INF;
		}
	}
	cache[0][0] = arr[0][0];
	for (int i = 1; i < n; i++) {
		if (arr[i][0] == -1) {
			break;
		}
		cache[i][0] = cache[i - 1][0] + arr[i][0];
	}
	for (int i = 1; i < m; i++) {
		if (arr[0][i] == -1) {
			break;
		}
		cache[0][i] = cache[0][i - 1] + arr[0][i];
	}
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			if (arr[i][j] != -1) {
				cache[i][j] = min(cache[i - 1][j], cache[i][j - 1]) + arr[i][j];
			}
		}
	}
	int& result = cache[n - 1][m - 1];
	if (result >= INF) {
		out << "No path." << '\n';
	}
	else {
		out << result << '\n';
		getPath(out);

	}
	return 0;
}