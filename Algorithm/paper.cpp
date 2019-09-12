#include<fstream>
#include<vector>
#include<algorithm>
#define NONE 0
#define SEPERATE 1
#define ALL 2
using namespace std;

struct Paper {
	int x, y, dx, dy;
};

int n;
Paper paper[2001];
int board[8001][8001];
vector<int> location;
vector<int> pressure;

void input(ifstream &inp) {
	inp >> n;
	for (int i = 0; i < n; i++) {
		int x, y, width, height;
		inp >> x >> y >> width >> height;
		paper[i] = { x, y, x + width, y + height };
		location.push_back(x);
		location.push_back(y);
		location.push_back(x + width);
		location.push_back(y + height);
	}
}

void pressureLocation() {
	sort(location.begin(), location.end());
	location.push_back(-1);
	for (int i = 0; i < location.size() - 1; i++) {
		if (location[i] != location[i + 1]) {
			pressure.push_back(location[i]);
		}
	}
	for (int i = 0; i < n; i++) {
		paper[i].x = lower_bound(pressure.begin(), pressure.end(), paper[i].x) - pressure.begin();
		paper[i].y = lower_bound(pressure.begin(), pressure.end(), paper[i].y) - pressure.begin();
		paper[i].dx = lower_bound(pressure.begin(), pressure.end(), paper[i].dx) - pressure.begin();
		paper[i].dy = lower_bound(pressure.begin(), pressure.end(), paper[i].dy) - pressure.begin();
	}
}

void coloringBoard() {
	for (int i = 0; i < n; i++) {
		for (int j = paper[i].y; j < paper[i].dy; j++) {
			for (int k = paper[i].x; k < paper[i].dx; k++) {
				board[j][k] = i;
			}
		}
	}
}

int getType(Paper paper, int idx) {
	bool seen = false, notSeen = false;
	for (int i = paper.y; i < paper.dy; i++) {
		for (int j = paper.x; j < paper.dx; j++) {
			if (board[i][j] == idx) {
				seen = true;
			}
			else {
				notSeen = true;
			}
		}
	}
	if (seen && notSeen) {
		return SEPERATE;
	}
	else if (seen) {
		return ALL;
	}
	else {
		return NONE;
	}
}

void getResult(ofstream &out) {
	int none = 0, seperate = 0, all = 0;
	for (int i = 0; i < n; i++) {
		switch (getType(paper[i], i)) {
		case NONE:
			none++;
			break;
		case SEPERATE:
			seperate++;
			break;
		case ALL:
			all++;
			break;
		}
	}
	out << none << ' ' << seperate << ' ' << all;
}

int main() {
	ifstream inp("paper.inp");
	ofstream out("paper.out");
	input(inp);
	pressureLocation();
	coloringBoard();
	getResult(out);
	inp.close(); out.close();
	return 0;
}