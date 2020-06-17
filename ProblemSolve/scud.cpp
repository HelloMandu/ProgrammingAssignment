#include<fstream>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;

struct Point {
	int x, y;
	int dx, dy;

	Point() : x(0), y(0), dx(0), dy(0) {};
	Point(int x, int y) : x(x), y(y), dx(0), dy(0) {};

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

vector<vector<Point> > kingdomsWall;
bool destroyed[10001];

inline int ccw(Point pivot, Point a, Point b) {
	return pivot.x * a.y + a.x * b.y + b.x * pivot.y - pivot.x * b.y - a.x * pivot.y - b.x * a.y;
}

vector<Point> convexHull(vector<Point> &kingdom) {
	sort(kingdom.begin(), kingdom.end());
	for (int i = 1; i < kingdom.size(); i++) {
		kingdom[i].dy = kingdom[i].y - kingdom[0].y;
		kingdom[i].dx = kingdom[i].x - kingdom[0].x;
	}
	sort(kingdom.begin() + 1, kingdom.end());
	stack<int> Stack;
	int pIdx = 0;
	Stack.push(pIdx++);
	Stack.push(pIdx++);
	while (pIdx < kingdom.size()) {
		while (Stack.size() > 1) {
			int first, second;
			second = Stack.top(); Stack.pop();
			first = Stack.top();
			if (ccw(kingdom[first], kingdom[second], kingdom[pIdx]) > 0) {
				Stack.push(second);
				break;
			}
		}
		Stack.push(pIdx++);
	}
	vector<Point> wallPoints(Stack.size());
	for (int i = wallPoints.size() - 1; i >= 0; i--) {
		wallPoints[i] = kingdom[Stack.top()]; Stack.pop();
	}
	kingdom.clear();
	return wallPoints;
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

int insidePolygon(vector<Point> &kingdom, Point missile) {
	int crossings = 0;
	for (int i = 0; i < kingdom.size(); i++) {
		int next = (i + 1) % kingdom.size();
		if (between(kingdom[i], kingdom[next], missile)) {
			return 1;
		}
		else if (isCrossing(missile, kingdom[i], kingdom[next])
			|| isCrossing(missile, kingdom[next], kingdom[i])) {
			crossings++;
		}
	}
	return crossings % 2;
}

double getArea(vector<Point> &kingdom) {
	double result = 0.0;
	for (int i = 0; i < kingdom.size(); i++) {
		int j = (i + 1) % kingdom.size();
		result += (kingdom[i].x * kingdom[j].y) - (kingdom[i].y * kingdom[j].x);
	}
	return fabs(result / 2);
}

int main() {
	ifstream inp("scud.inp");
	ofstream out("scud.out");
	int n = 0;
	while (inp >> n && n != -1) {
		vector<Point> kingdom;
		for (int i = 0; i < n; i++) {
			int x, y;
			inp >> x >> y;
			kingdom.push_back(Point(x, y));
		}
		kingdomsWall.push_back(convexHull(kingdom));
	}
	int x, y;
	while (inp >> x >> y) {
		for (int i = 0; i < kingdomsWall.size(); i++) {
			if (!destroyed[i]) {
				if (insidePolygon(kingdomsWall[i], { x, y })) {
					destroyed[i] = true;
					break;
				}
			}
		}
	}
	double result = 0;
	for (int i = 0; i < kingdomsWall.size(); i++) {
		if (destroyed[i]) {
			result += getArea(kingdomsWall[i]);
		}
	}
	out.setf(ios::fixed);
	out.precision(2);
	out << result;
	return 0;
}