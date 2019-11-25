#include<fstream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;

struct Rect {
	int x, y, dx, dy;
};
int n;
Rect rect[10001];
int tree[100001];

int getHeight(int node, int start, int finish, int left, int right) {
	if (left > finish || right < start) {
		return 0;
	}
	else if (left <= start && finish <= right) {
		return tree[node];
	}
	return max(getHeight(node * 2, start, (start + finish) / 2, left, right), 
		getHeight(node * 2 + 1, (start + finish) / 2 + 1, finish, left, right));
}

void update(int node, int start, int finish, int left, int right, int diff) {
	if (right < start || left > finish) {
		return;
	}
	tree[node] = max(tree[node], diff);
	if (start != finish) {
		update(node * 2, start, (start + finish) / 2, left, right, diff);
		update(node * 2 + 1, (start + finish) / 2 + 1, finish, left, right, diff);
	}
}

bool compareY(Rect &a, Rect &b) {
	return a.y < b.y;
}

bool compareX(Rect &a, Rect &b) {
	return a.x < b.x;
}

bool rowPressure() {
	bool renuwal = false;
	sort(rect, rect + n, compareY);
	vector<int> sorted;
	for (int i = 0; i < n; i++) {
		sorted.push_back(rect[i].x); sorted.push_back(rect[i].dx);
	}
	sort(sorted.begin(), sorted.end());
	vector<int> cols;
	cols.push_back(sorted[0]);
	for (int i = 1; i < sorted.size(); i++) {
		if (sorted[i - 1] != sorted[i]) {
			cols.push_back(sorted[i]);
		}
	}

	memset(tree, 0, sizeof(tree));

	for (int i = 0; i < n; i++) {
		int rectHeight = rect[i].dy - rect[i].y;
		int left = lower_bound(cols.begin(), cols.end(), rect[i].x) - cols.begin();
		int right = lower_bound(cols.begin(), cols.end(), rect[i].dx) - cols.begin();
		int height = getHeight(1, 0, cols.size() - 1, left, right - 1);
		if (height < rect[i].y) {
			rect[i].y = height;
			rect[i].dy = height + rectHeight;
			renuwal = true;
		}
		update(1, 0, cols.size() - 1, left, right - 1, rect[i].dy);
	}
	return renuwal;
}

bool colPressure() {
	bool renuwal = false;
	sort(rect, rect + n, compareX);
	vector<int> sorted;
	for (int i = 0; i < n; i++) {
		sorted.push_back(rect[i].y); sorted.push_back(rect[i].dy);
	}
	sort(sorted.begin(), sorted.end());
	vector<int> rows;
	rows.push_back(sorted[0]);
	for (int i = 1; i < sorted.size(); i++) {
		if (sorted[i - 1] != sorted[i]) {
			rows.push_back(sorted[i]);
		}
	}

	memset(tree, 0, sizeof(tree));

	for (int i = 0; i < n; i++) {
		int rectLength = rect[i].dx - rect[i].x;
		int left = lower_bound(rows.begin(), rows.end(), rect[i].y) - rows.begin();
		int right = lower_bound(rows.begin(), rows.end(), rect[i].dy) - rows.begin();
		int length = getHeight(1, 0, rows.size() - 1, left, right - 1);
		if (length < rect[i].x) {
			rect[i].x = length;
			rect[i].dx = length + rectLength;
			renuwal = true;
		}
		update(1, 0, rows.size() - 1, left, right - 1, rect[i].dx);
	}
	return renuwal;
}

int main() {
	ifstream inp("block.inp");
	ofstream out("block.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		inp >> n;
		for (int i = 0; i < n; i++) {
			inp >> rect[i].x >> rect[i].y >> rect[i].dx >> rect[i].dy;
		}
		while (true) {
			if (!rowPressure() && !colPressure()) {
				int X = 0, Y = 0;
				for (int i = 0; i < n; i++) {
					X = max(X, rect[i].dx);
					Y = max(Y, rect[i].dy);
				}
				out << X << ' ' << Y << '\n';
				break;
			}
		}
	}
	return 0;
}