#include<fstream>
#include<algorithm>
#include<cstring>
#define INF 987654321
#define UP true
#define LEFT false
using namespace std;

int n, m, k;
int rowCost[101][101];
int colCost[101][101];
bool dot[101][101];
int costCache[101][101][201];
int countCache[101][101][201];
int footCache[101][101];
bool routeCache[101][101][201];

void init(ifstream& inp) {
	memset(rowCost, false, sizeof(rowCost));
	memset(colCost, false, sizeof(colCost));
	memset(dot, false, sizeof(dot));
	memset(countCache, 0, sizeof(countCache));
	memset(costCache, 0, sizeof(costCache));
	memset(footCache, 0, sizeof(footCache));
	memset(routeCache, false, sizeof(routeCache));
	inp >> n >> m >> k;
	for (int i = 0; i < k; i++) {
		int y, x;
		inp >> y >> x;
		dot[y][x] = true;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m - 1; j++) {
			inp >> rowCost[i][j];
		}
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < m; j++) {
			inp >> colCost[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int l = 0; l <= k; l++) {
				costCache[i][j][l] = INF;
			}
		}
	}
	for (int l = 0; l <= k; l++) {
		costCache[0][0][l] = 0;
	}
}

void computeFoot() {
	for (int i = 1; i < m; i++) {
		if (dot[0][i]) {
			footCache[0][i] = 1;
		}
		footCache[0][i] += footCache[0][i - 1];
	}
	for (int i = 1; i < n; i++) {
		if (dot[i][0]) {
			footCache[i][0] = 1;
		}
		footCache[i][0] += footCache[i - 1][0];
	}
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			footCache[i][j] = min(footCache[i - 1][j], footCache[i][j - 1]);
			if (dot[i][j]) {
				footCache[i][j] += 1;
			}
		}
	}
}

void computeCount() {
	int cnt = 0;
	for (int i = 0; i < m; i++) {
		if (dot[0][i]) {
			cnt++;
		}
		countCache[0][i][cnt] = 1;
	}
	cnt = 0;
	for (int i = 0; i < n; i++) {
		if (dot[i][0]) {
			cnt++;
		}
		countCache[i][0][cnt] = 1;
	}
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			if (dot[i][j]) {
				for (int l = footCache[i][j]; l <= k; l++) {
					countCache[i][j][l] = (countCache[i - 1][j][l - 1] + countCache[i][j - 1][l - 1]) % 100000;
				}
			}
			else {
				for (int l = footCache[i][j]; l <= k; l++) {
					countCache[i][j][l] = (countCache[i - 1][j][l] + countCache[i][j - 1][l]) % 100000;
				}
			}
		}
	}
}

void computeCost() {
	int first = dot[0][0] ? 1 : 0;
	int cnt = first;
	for (int i = 1; i < m; i++) {
		if (dot[0][i]) {
			cnt++;
			costCache[0][i][cnt] = costCache[0][i - 1][cnt - 1] + rowCost[0][i - 1];
		}
		else {
			costCache[0][i][cnt] = costCache[0][i - 1][cnt] + rowCost[0][i - 1];
		}
		routeCache[0][i][cnt] = LEFT;
	}
	cnt = first;
	for (int i = 1; i < n; i++) {
		if (dot[i][0]) {
			cnt++;
			costCache[i][0][cnt] = costCache[i - 1][0][cnt - 1] + colCost[i - 1][0];
		}
		else {
			costCache[i][0][cnt] = costCache[i - 1][0][cnt] + colCost[i - 1][0];
		}
		routeCache[i][0][cnt] = UP;
	}
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			if (dot[i][j]) {
				for (int l = footCache[i][j]; l <= k; l++) {
					int up = costCache[i - 1][j][l - 1] + colCost[i - 1][j];
					int left = costCache[i][j - 1][l - 1] + rowCost[i][j - 1];
					if (up >= left) {
						costCache[i][j][l] = left % 100000;
						routeCache[i][j][l] = LEFT;
					}
					else {
						costCache[i][j][l] = up % 100000;
						routeCache[i][j][l] = UP;
					}
				}
			}
			else {
				for (int l = footCache[i][j]; l <= k; l++) {
					int up = costCache[i - 1][j][l] + colCost[i - 1][j];
					int left = costCache[i][j - 1][l] + rowCost[i][j - 1];
					if (up >= left) {
						costCache[i][j][l] = left % 100000;
						routeCache[i][j][l] = LEFT;
					}
					else {
						
						costCache[i][j][l] = up % 100000;
						routeCache[i][j][l] = UP;
					}
				}
			}
		}
	}
}

void getPath(ofstream& out, int z, int y = n - 1, int x = m - 1) {
	int newZ;
	if (dot[y][x]) {
		newZ = z - 1;
	}
	else {
		newZ = z;
	}
	if (y != 0 || x != 0) {
		if (y > 0 && x > 0) {
			if (routeCache[y][x][z] == UP) {
				getPath(out, newZ, y - 1, x);
			}
			else {
				getPath(out, newZ, y, x - 1);
			}
		}
		else if (y == 0) {
			getPath(out, newZ, y, x - 1);
		}
		else {
			getPath(out, newZ, y - 1, x);
		}
		out << "->(";
	}
	else {
		out << '(';
	}
	out << y << ',' << x << ')';
}

int main() {
	ifstream inp("path2.inp");
	ofstream out("path2.out");
	int testcase;
	inp >> testcase;
	for (int t = 1; t <= testcase; t++) {
		init(inp);
		computeFoot();
		computeCount();
		computeCost();
		out << "Test Case No:" << t << '\n';
		for (int i = 0; i <= k; i++) {
			if (countCache[n - 1][m - 1][i]) {
				out << "k:" << i << " count:" << countCache[n - 1][m - 1][i] << " cost:" << costCache[n - 1][m - 1][i] << '\n';
				getPath(out, i);
				out << '\n';
			}
		}
		out << '\n';
	}
	return 0;
}