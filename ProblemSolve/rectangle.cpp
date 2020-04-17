#include<fstream>
#include<algorithm>
#include<vector>
#define START 1
#define END -1
#define MAX 10001
using namespace std;

struct Rectangle {
	int x, y, dy, line;
	bool operator<(const Rectangle &a) {
		return x < a.x;
	}
};

vector<Rectangle> rec;
int tree[MAX * 8];
int cnt[MAX * 8];

void updateTree(int root, int left, int right, int start, int end, int line) {
	if (left > end || right < start) {
		return;
	}
	if (left <= start && end <= right) {
		cnt[root] += line;
	}
	else {
		int mid = (start + end) / 2;
		updateTree(root * 2, left, right, start, mid, line);
		updateTree(root * 2 + 1, left, right, mid + 1, end, line);
	}
	if (!cnt[root]) {
		if (start != end) {
			tree[root] = tree[root * 2] + tree[root * 2 + 1];
		}
		else {
			tree[root] = 0;
		}
	}
	else {
		tree[root] = end - start + 1;
	}
}

int main() {
	ifstream inp("rectangle.inp");
	ofstream out("rectangle.out");
	int n;
	inp >> n;
	for (int i = 0; i < n; i++) {
		int x, y, dx, dy;
		inp >> x >> y >> dx >> dy;
		rec.push_back({ x, y + MAX, dy + MAX, START });
		rec.push_back({ dx, y + MAX, dy + MAX, END });
	}
	sort(rec.begin(), rec.end());
	int result = 0;
	for (int i = 0; i < n * 2; i++) {
		if (i) {
			result += (rec[i].x - rec[i - 1].x) * tree[1];
		}
		updateTree(1, rec[i].y, rec[i].dy - 1, 0, (MAX * 2) - 2, rec[i].line);
	}
	out << result;
	return 0;
}