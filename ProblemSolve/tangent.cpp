#include<fstream>
#include<algorithm>
#include<stack>
#include<vector>
#include<cmath>
using namespace std;
#pragma warning(disable:4996)

typedef long long lint;

struct Point {
	lint y, x, dy, dx, n;
	char polygon;

	bool operator<(const Point &a) {
		if (dy * a.dx != dx * a.dy) {
			return (lint)dy * a.dx < (lint)dx * a.dy;
		}
		else if (y != a.y) {
			return y < a.y;
		}
		return x < a.x;
	}
};
Point pPoints[10001], qPoints[10001];
vector<Point> points, hullPoints, innerPoints;
int pLength, qLength, pTop, pBottom, qTop, qBottom;

inline lint ccw(Point pivot, Point a, Point b) {
	return pivot.x * a.y + a.x * b.y + b.x * pivot.y - pivot.x * b.y - a.x * pivot.y - b.x * a.y;
}

lint getDirection(Point a, Point b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
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
		pPoints[i].n = i; pPoints[i].polygon = 'P';
		points.push_back(pPoints[i]);
	}
	inp >> qLength;
	for (int i = 0; i < qLength; i++) {
		inp >> qPoints[i].x >> qPoints[i].y;
		qPoints[i].n = i; qPoints[i].polygon = 'Q';
		points.push_back(qPoints[i]);
	}
	sort(points.begin(), points.end());
	for (int i = 1; i < points.size(); i++) {
		points[i].dy = points[i].y - points[0].y;
		points[i].dx = points[i].x - points[0].x;
	}
	sort(points.begin() + 1, points.end());
	stack<int> Stack;
	convexHull(Stack, points.size());
	hullPoints.resize(Stack.size());
	for (int i = hullPoints.size() - 1; i >= 0; i--) {
		hullPoints[i] = points[Stack.top()]; Stack.pop();
	}
}

void findPoint() {
	for (int i = 0; i < hullPoints.size(); i++) {
		Point cur = hullPoints[i], next = hullPoints[(i + 1) % hullPoints.size()];
		if (cur.polygon == 'P' && next.polygon == 'Q') {
			pBottom = cur.n, qBottom = next.n;
			for (int j = 0; j < pLength; j++) {
				if (ccw(cur, pPoints[j], next) == 0) {
					if (getDirection(pPoints[j], next) < getDirection(cur, next)) {
						cur = pPoints[j], pBottom = pPoints[j].n;
					}
				}
			}
			for (int j = 0; j < qLength; j++) {
				if (ccw(cur, qPoints[j], next) == 0) {
					if (getDirection(cur, qPoints[j]) < getDirection(cur, next)) {
						next = qPoints[j], qBottom = qPoints[j].n;
					}
				}
			}
		}
		else if (cur.polygon == 'Q' && next.polygon == 'P') {
			qTop = cur.n, pTop = next.n;
			for (int j = 0; j < qLength; j++) {
				if (ccw(cur, qPoints[j], next) == 0) {
					if (getDirection(next, qPoints[j]) < getDirection(next, cur)) {
						cur = qPoints[j], qTop = qPoints[j].n;
					}
				}
			}
			for (int j = 0; j < pLength; j++) {
				if (ccw(cur, pPoints[j], next) == 0) {
					if (getDirection(pPoints[j], cur) < getDirection(next, cur)) {
						next = pPoints[j], pTop = pPoints[j].n;
					}
				}
			}
		}
	}
}

void makeInnerPolygon() {
	for (int i = pTop; ; i = (i + pLength - 1) % pLength) {
		innerPoints.push_back(pPoints[i]);
		if (pPoints[i].n == pBottom) {
			break;
		}
	}
	for (int i = qBottom; ; i = (i + qLength - 1) % qLength) {
		innerPoints.push_back(qPoints[i]);
		if (qPoints[i].n == qTop) {
			break;
		}
	}
}

double getArea() {
	double result = 0.0;
	for (int i = 0; i < innerPoints.size(); i++) {
		int j = (i + 1) % innerPoints.size();
		result += (innerPoints[i].x * innerPoints[j].y) - (innerPoints[i].y * innerPoints[j].x);
	}
	if (pTop == pBottom) {
		for (int i = 0; i < pLength; i++) {
			int j = (i + 1) % pLength;
			result -= (pPoints[i].x * pPoints[j].y) - (pPoints[i].y * pPoints[j].x);
		}
	}
	else if (qTop == qBottom) {
		for (int i = 0; i < qLength; i++) {
			int j = (i + 1) % qLength;
			result -= (qPoints[i].x * qPoints[j].y) - (qPoints[i].y * qPoints[j].x);
		}
	}
	return fabs(result / 2);
}

int main() {
	ifstream inp("tangent.inp");
	FILE *out = fopen("tangent.out", "wt");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		init(inp);
		findPoint();
		makeInnerPolygon();
		fprintf(out, "%.1lf\n", getArea());
		points.clear(); hullPoints.clear(); innerPoints.clear();
	}
	return 0;
}