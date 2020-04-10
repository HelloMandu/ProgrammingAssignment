#include<fstream>
using namespace std;

struct Point {
	int y, x;
	Point(int y = 0, int x = 0) : y(y), x(x) {}
	Point operator-(Point a) {
		return Point(y - a.y, x - a.x);
	}
};

Point point[20002];
Point pivot;

inline int ccw(Point pivot, Point b, Point c) {
	Point p = b - pivot, q = c - pivot;
	return p.x * q.y - p.y * q.x;
}

bool between(Point a, Point b, Point pivot) {
	if (ccw(pivot, a, b) != 0) {
		return 0;
	}
	if (a.x != b.x) {
		return a.x <= pivot.x && pivot.x <= b.x
			|| b.x <= pivot.x && pivot.x <= a.x;
	}
	else {
		return a.y <= pivot.y && pivot.y <= b.y
			|| b.y <= pivot.y && pivot.y <= a.y;
	}
}

bool isCrossing(Point pivot, Point a, Point b) {
	return a.y < pivot.y && b.y >= pivot.y && ccw(a, b, pivot) > 0;
}

int insidePolygon(int n) {
	int crossings = 0;
	for (int i = 0; i < n; i++) {
		int next = (i + 1) % n;
		if (between(point[i], point[next], pivot)) {
			return 1;
		}
		else if (isCrossing(pivot, point[i], point[next])
			|| isCrossing(pivot, point[next], point[i])) {
			crossings++;
		}
	}
	return crossings % 2;
}

int main() {
	ifstream inp("point.inp");
	ofstream out("point.out");
	int n, testcase;
	inp >> n;
	for (int i = 0; i < n; i++) {
		inp >> point[i].x >> point[i].y;
	}
	inp >> testcase;
	while (testcase--) {
		inp >> pivot.x >> pivot.y;
		out << insidePolygon(n) << '\n';
	}
	return 0;
}