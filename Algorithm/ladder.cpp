#include<fstream>
#include<algorithm>
#include<vector>
using namespace std;

struct Ladder {
	int height, next, nextHeight;
};

vector<Ladder> ladder[51];
int result[51];
int n;

bool compare(Ladder a, Ladder b) {
	return a.height > b.height;
}

void input(ifstream &inp) {
	inp >> n;
	while (true) {
		int bar, height, bar2, height2;
		inp >> bar >> height >> bar2 >> height2;
		if (bar == 0 && height == 0 && bar2 == 0 && height2 == 0) {
			return;
		}
		ladder[bar].push_back({ height, bar2, height2 });
		ladder[bar2].push_back({ height2, bar, height });
	}
}

int findNext(int nextBar, int height) {
	for (int i = 0; i < ladder[nextBar].size(); i++) {
		if (ladder[nextBar][i].height == height) {
			return i + 1;
		}
	}
	return -1;
}

int downLadder(int bar, int location) {
	if (location == ladder[bar].size()) {
		return bar;
	}
	int nextBar = ladder[bar][location].next;
	int nextLocation = findNext(nextBar, ladder[bar][location].nextHeight);
	return downLadder(nextBar, nextLocation);
}

int main() {
	ifstream inp("ladder.inp");
	ofstream out("ladder.out");
	input(inp);
	for (int i = 0; i < n; i++) {
		sort(ladder[i].begin(), ladder[i].end(), compare);
	}
	for (int i = 0; i < n; i++) {
		result[downLadder(i, 0)] = i;
	}
	for (int i = 0; i < n; i++) {
		out << result[i] << ' ';
	}
	inp.close(); out.close();
	return 0;
}