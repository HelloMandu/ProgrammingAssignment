#include<fstream>
#include<queue>
#define NONE 0
#define MIX 1
using namespace std;

int k;
char map[20][20];
bool isVisit[20][20];
int black = 0, white = 0;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
char color;

void input(ifstream &inp) {
	inp >> k;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			inp >> map[i][j];
		}
	}
}

bool isRange(int i, int j) {
	return i > -1 && i < k && j > -1 && j < k;
}

void bfs(int i, int j) {
	queue<pair<int, int> > Queue;
	Queue.push({ i, j });
	isVisit[i][j] = true;
	color = NONE;
	int dot = 1;
	while (!Queue.empty()) {
		int y = Queue.front().first, x = Queue.front().second;
		if (map[y][x] == '.') {
			for (int i = 0; i < 4; i++) {
				int nextY = y + dy[i], nextX = x + dx[i];
				if (isRange(nextY, nextX) && !isVisit[nextY][nextX]) {
					if (map[nextY][nextX] == '.') {
						isVisit[nextY][nextX] = true;
						dot++;
					}
					Queue.push({ nextY, nextX });
				}
			}
		}
		else if (color != MIX) {
			if (color == NONE) {
				color = map[y][x];
			}
			else if (color != map[y][x]) {
				color = MIX;
			}
		}
		Queue.pop();
	}
	if (color == 'B') {
		black += dot;
	}
	else if (color == 'W') {
		white += dot;
	}
}

void countHome() {
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			if (map[i][j] == '.' && !isVisit[i][j]) {
				bfs(i, j);
			}
		}
	}
}

int main() {
	ifstream inp("pandora.inp");
	ofstream out("pandora.out");
	input(inp);
	countHome();
	out << black << ' ' << white;
	inp.close(); out.close();
	return 0;
}