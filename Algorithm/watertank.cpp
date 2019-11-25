#include<fstream>
#include<algorithm>
#include<cstring>
using namespace std;

enum Direction{ north, east, south, west }; // ºÏµ¿³²¼­

struct Square {
	int dir[4], water;
};

int n, m, h;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
Square square[1002][1002];
bool isVisit[1002][1002];

void input(ifstream &inp) {
	inp >> n >> m >> h;
	for (int i = 1; i <= n + 1; i++) {
		for (int j = 1; j <= m; j++) {
			int dot; inp >> dot;
			square[i][j].dir[north] = dot;
			square[i - 1][j].dir[south] = dot;
		}
	}
	for (int i = 1; i <= m; i++) {
		square[0][i].dir[south] = square[1][i].dir[north];
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m + 1; j++) {
			int dot; inp >> dot;
			square[i][j].dir[west] = dot;
			square[i][j - 1].dir[east] = dot;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			square[i][j].water = h;
		}
	}
}

int isOpen(int row, int col) {
	for (int i = 0; i < 4; i++) {
		if (square[row][col].dir[i] != -1) {
			return i;
		}
	}
	return -1;
}

bool isRange(int row, int col) {
	return 0 < row && row <= n && 0 < col && col <= m;
}

void dfs(int row, int col, int hole, int dir) {
	square[row][col].water = min(square[row][col].water, hole);
	for (int i = 0; i < 4; i++) {
		if (isRange(row + dy[i], col + dx[i]) && square[row][col].dir[i] != -1 && i != (dir + 2) % 4 && !isVisit[row + dy[i]][col + dx[i]]) {
			isVisit[row + dy[i]][col + dx[i]] = true;
			dfs(row + dy[i], col + dx[i], max(square[row][col].dir[i], hole), i);
			isVisit[row + dy[i]][col + dx[i]] = false;
		}
	}
}

void traversal() {
	for (int i = 0; i <= n + 1; i++) {
		for (int j = 0; j <= m + 1; ) {
			int hole = isOpen(i, j);
			if (hole != -1) {
				dfs(i + dy[hole], j + dx[hole], square[i][j].dir[hole], hole);
			}
			if (i == 0 || i == n + 1) { j++; }
			else { j += m + 1; }
		}
	}
}

int getResult() {
	int result = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			result += square[i][j].water;
		}
	}
	return result;
}

int main() {
	ifstream inp("watertank.inp");
	ofstream out("watertank.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		memset(square, -1, sizeof(square));
		input(inp);
		traversal();
		out << getResult() << '\n';
	}
	return 0;
}