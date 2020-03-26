#include<fstream>
#include<string>
#include<algorithm>
using namespace std;

ifstream inp("Waldorf.inp");
ofstream out("Waldorf.out");

int n, m;
string str;
char matrix[501][501];
int dy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };

void setStr() {
	inp >> str;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] += 32;
		}
	}
}

bool isRange(int row, int col) {
	return row > -1 && row < n && col > -1 && col < m;
}

bool isWord(int row, int col, int dir, int count = 0) {
	if (count == str.size()) {
		return true;
	}
	if (isRange(row, col)) {
		if (str[count] != matrix[row][col]) {
			return false;
		}
		return isWord(row + dy[dir], col + dx[dir], dir, count + 1);
	}
	return false;
}

bool hasWord(int row, int col) {
	for (int i = 0; i < 8; i++) {
		if (isWord(row, col, i, 0)) {
			out << row + 1 << ' ' << col + 1 << '\n';
			return true;
		}
	}
	return false;
}

void findStr() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (matrix[i][j] == str[0]) {
				if (hasWord(i, j)) {
					return;
				}
			}
		}
	}
	out << -1 << '\n';
}

int main() {
	int testcase;
	inp >> testcase;
	for (int t = 1; t <= testcase; t++) {
		inp >> n >> m;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				inp >> matrix[i][j];
				if (matrix[i][j] >= 'A' && matrix[i][j] <= 'Z') {
					matrix[i][j] += 32;
				}
			}
		}
		int count;
		inp >> count;
		while (count--) {
			setStr();
			findStr();
		}
		out << '\n';
	}
	return 0;
}