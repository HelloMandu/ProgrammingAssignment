#include<fstream>
#include<algorithm>
#include<cstring>
using namespace std;

ifstream inp("sudoku.inp");
ofstream out("sudoku.out");

struct Sudoku {
	int num;
	char alphabet;
};

Sudoku map[10][10];
bool isVisit[9][10];

void input() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			inp >> map[i][j].num;
			
		}
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			inp >> map[i][j].alphabet;
			if (map[i][j].num) {
				isVisit[map[i][j].alphabet - 'a'][map[i][j].num] = true;
			}
		}
	}
}

bool hasNumber(int y, int x, int num) {
	for (int i = 0; i < 9; i++) {
		if (map[y][i].num == num || map[i][x].num == num) {
			return true;
		}
	}
	return isVisit[map[y][x].alphabet - 'a'][num];
}

void printMap() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			out << map[i][j].num << ' ';
		}
		out << '\n';
	}
	out << '\n';
}

bool traversal(int count = 0) {
	if (count == 81) {
		printMap();
		return true;
	}
	int y = count / 9, x = count % 9;
	if (map[y][x].num) {
		return traversal(count + 1);
	}
	for (int i = 1; i < 10; i++) {
		if (!hasNumber(y, x, i)) {
			map[y][x].num = i;
			isVisit[map[y][x].alphabet - 'a'][i] = true;
			if (traversal(count + 1)) {
				return  true;
			}
			isVisit[map[y][x].alphabet - 'a'][i] = false;
			map[y][x].num = 0;
		}
	}
	return false;
}

int main() {
	int testcase;
	inp >> testcase;
	for (int i = 1; i <= testcase; i++) {
		memset(isVisit, false, sizeof(isVisit));
		input();
		out << "Test Case No: " << i << '\n';
		traversal();
	}
	return 0;
}