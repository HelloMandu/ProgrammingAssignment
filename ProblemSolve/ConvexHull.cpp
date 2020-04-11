#include<fstream>
#include<algorithm>
#include<stack>
#include<vector>
using namespace std;

struct Point {
	int y, x;
	int dy, dx;
	Point(int y = 0, int x = 0, int dy = 0, int dx = 0) : y(y), x(x), dy(dy), dx(dx) {}
	Point operator-(Point a) {
		return Point(y - a.y, x - a.x);
	}
	bool operator<(const Point &a) {
		if (dy * a.dx != dx * a.dy) {
			return dy * a.dx < dx * a.dy;
		}
		else if (x != a.x) {
			return x < a.x;
		}
		return y < a.y;
	}
};

Point point[20002];
stack<Point> Stack;

inline int ccw(Point a, Point b, Point c) {
	Point p = b - a, q = c - a;
	return p.x * q.y - p.y * q.x;
}

void convexHull(int n) {
	int pIdx = 0;
	Stack.push(point[pIdx++]);
	Stack.push(point[pIdx++]);
	while (pIdx < n) {
		while(Stack.size() > 1) {
			Point first, second;
			second = Stack.top(); Stack.pop();
			first = Stack.top();
			if (ccw(first, second, point[pIdx]) > 0) {
				Stack.push(second);
				break;
			}
		}
		Stack.push(point[pIdx++]);
	}
}

void printConvexHull(ofstream &out) {
	if (!Stack.empty()) {
		Point result = Stack.top(); Stack.pop();
		printConvexHull(out);
		out << result.x << ' ' << result.y << '\n';
	}
}

int main() {
	ifstream inp("tangent.inp");
	ofstream out("tangent.out");
	int n;
	inp >> n;
	for (int i = 0; i < n; i++) {
		inp >> point[i].x >> point[i].y;
	}
	sort(point, point + n);
	for (int i = 1; i < n; i++) {
		point[i].dy = point[i].y - point[0].y;
		point[i].dx = point[i].x - point[0].x;
	}
	sort(point + 1, point + n);
	convexHull(n);
	out << Stack.size() << '\n';
	printConvexHull(out);
	return 0;
}