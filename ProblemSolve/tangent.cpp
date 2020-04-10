#include<fstream>
#include<algorithm>
#include<stack>
#include<vector>
using namespace std;

typedef long long lint;

struct Point {
	int y, x, dy, dx, n;
	char polygon;
	Point() {}
	Point(int y, int x, char polygon, int n) :Point(y, x, 0, 0, polygon, n) {}
	Point(int y, int x, int dy, int dx, char polygon, int n) : y(y), x(x), dy(dy), dx(dx), polygon(polygon), n(n) {}

	bool operator<(const Point &a) {
		if (dy * a.dx != dx * a.dy) {
			return dy * a.dx < dx * a.dy;
		}
		else if (y != a.y) {
			return y < a.y;
		}
		return x < a.x;
	}
};

int pLength, qLength;
Point pPoints[10001], qPoints[10001];
vector<Point> points, hullPoints;

inline lint ccw(Point pivot, Point a, Point b) {
	return pivot.x * a.y + a.x * b.y + b.x * pivot.y - pivot.x * b.y - a.x * pivot.y - b.x * a.y;
}

void convexHull(stack<int> &Stack, int n) {
	int pIdx = 0;
	Stack.push(pIdx++);
	Stack.push(pIdx++);
	while (pIdx < n) {
		while (Stack.size() > 1) {
			int first, second;
			second = Stack.top(); Stack.pop();
			first = Stack.top();
			if (ccw(points[first], points[second], points[pIdx]) > 0) {
				Stack.push(second);
				break;
			}
		}
		Stack.push(pIdx++);
	}
}

void init(ifstream &inp) {
	inp >> pLength;
	for (int i = 0; i < pLength; i++) {
		inp >> pPoints[i].x >> pPoints[i].y;
		points.push_back({ pPoints[i].y, pPoints[i].x, 'P', i });
	}
	inp >> qLength;
	for (int i = 0; i < qLength; i++) {
		inp >> qPoints[i].x >> qPoints[i].y;
		points.push_back({ pPoints[i].y, pPoints[i].x, 'Q', i });
	}
	sort(points.begin(), points.end());
	for (int i = 1; i < points.size(); i++) {
		points[i].dy = points[i].y - points[0].y;
		points[i].dx = points[i].x - points[0].x;
	}
	sort(points.begin() + 1, points.end());
	stack<int> Stack;
	convexHull(Stack, points.size());
	while (!Stack.empty()) {
		hullPoints.push_back(points[Stack.top()]);
		Stack.pop();
	}
}

int main() {
	ifstream inp("tangent.inp");
	ofstream out("tangent.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		init(inp);
		int pBegin, pEnd, qBegin, qEnd;
		for (int i = 0; i < hullPoints.size(); i++) {
			Point cur = hullPoints[i], next = hullPoints[(i + 1) % hullPoints.size()];
			if (cur.polygon == 'P' && next.polygon == 'Q') {
				pBegin = cur.n, qEnd = next.n;
				/*p점들을 추가*/
			}
			else if (cur.polygon == 'Q' && next.polygon == 'P') {
				qBegin = cur.n, pEnd = next.n;
				/*q점들을 추가*/
			}
		}
	}
	return 0;
}