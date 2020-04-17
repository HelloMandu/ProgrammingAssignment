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
		else if (x != a.x) {
			return x < a.x;
		}
		return y < a.y;
	}
};
vector<Point> pPoints, qPoints, points, pHull, qHull, hull, innerPoints;
int pTop, pBottom, qTop, qBottom;

inline lint ccw(Point pivot, Point a, Point b) {
	return pivot.x * a.y + a.x * b.y + b.x * pivot.y - pivot.x * b.y - a.x * pivot.y - b.x * a.y;
}

inline lint getDirection(Point a, Point b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

vector<Point> convexHull(vector<Point> points) {
	stack<int> Stack;
	sort(points.begin(), points.end());
	for (int i = 1; i < points.size(); i++) {
		points[i].dy = points[i].y - points[0].y;
		points[i].dx = points[i].x - points[0].x;
	}
	sort(points.begin() + 1, points.end());
	int pIdx = 0;
	Stack.push(pIdx++);
	Stack.push(pIdx++);
	while (pIdx < points.size()) {
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
	vector<Point> result;
	result.resize(Stack.size());
	for (int i = result.size() - 1; i >= 0; i--) {
		result[i] = points[Stack.top()]; Stack.pop();
	}
	return result;
}

void init(ifstream &inp) {
	int x, y, pLength, qLength;
	inp >> pLength;
	for (int i = 0; i < pLength; i++) {
		inp >> x >> y;
		pPoints.push_back({ y, x, 0, 0, i, 'P' });
		points.push_back({ y, x, 0, 0, i, 'P' });
	}
	inp >> qLength;
	for (int i = 0; i < qLength; i++) {
		inp >> x >> y;
		qPoints.push_back({ y, x, 0, 0, i, 'Q' });
		points.push_back({ y, x, 0, 0, i, 'Q' });
	}
	pHull = convexHull(pPoints);
	qHull = convexHull(qPoints);
	hull = convexHull(points);
}

void closestPoint(int &p, int &q) {
	for (int i = 0; i < pHull.size(); i++) {
		if (ccw(pHull[p], pHull[i], qHull[q]) == 0) {
			if (getDirection(pHull[i], qHull[q]) < getDirection(pHull[p], qHull[q])) {
				p = i;
			}
		}
	}
	for (int i = 0; i < qHull.size(); i++) {
		if (ccw(qHull[q], qHull[i], pHull[p]) == 0) {
			if (getDirection(qHull[i], pHull[p]) < getDirection(qHull[q], pHull[p])) {
				q = i;
			}
		}
	}
}

void findPointPtoQ() {
	while (true) {
		bool flagP = false, flagQ = false;
		for (int i = 0; i < qHull.size(); i++) {
			if (ccw(pHull[pTop], qHull[i], qHull[qBottom]) > 0) {
				flagQ = true;
				qBottom = (qBottom  + qHull.size() - 1) % qHull.size();
				break;
			}
		}
		if (flagQ) {
			continue;
		}
		for (int i = 0; i < pHull.size(); i++) {
			if (ccw(qHull[qBottom], pHull[i], pHull[pTop]) > 0) {
				flagP = true;
				pTop = (pTop + pHull.size() - 1) % pHull.size();
				break;
			}
		}
		if (flagP) {
			continue;
		}
		break;
	}
	closestPoint(pTop, qBottom);
	pTop = pHull[pTop].n, qBottom = qHull[qBottom].n;
}

void findPointQtoP() {
	while (true) {
		bool flagP = false, flagQ = false;
		for (int i = 0; i < pHull.size(); i++) {
			if (ccw(qHull[qTop], pHull[i], pHull[pBottom]) < 0) {
				flagP = true;
				pBottom = (pBottom + 1) % pHull.size();
				break;
			}
		}
		if (flagP) {
			continue;
		}
		for (int i = 0; i < qHull.size(); i++) {
			if (ccw(pHull[pBottom], qHull[i], qHull[qTop]) < 0) {
				flagQ = true;
				qTop = (qTop + 1) % qHull.size();
				break;
			}
		}
		if (flagQ) {
			continue;
		}
		break;
	}
	closestPoint(pBottom, qTop);
	pBottom = pHull[pBottom].n, qTop = qHull[qTop].n;
}

void findPoint() {
	for (int i = 0; i < hull.size(); i++) {
		Point cur = hull[i], next = hull[(i + 1) % hull.size()];
		if (cur.polygon == 'P' && next.polygon == 'Q') {
			pBottom = cur.n, qBottom = next.n;
		}
		else if (cur.polygon == 'Q' && next.polygon == 'P') {
			qTop = cur.n, pTop = next.n;
		}
	}
	for (int i = 0; i < pHull.size(); i++) {
		if (pHull[i].n == pTop) { pTop = i; }
		else if (pHull[i].n == pBottom) { pBottom = i; }
	}
	for (int i = 0; i < qHull.size(); i++) {
		if (qHull[i].n == qTop) { qTop = i; }
		else if (qHull[i].n == qBottom) { qBottom = i;}
	}
	findPointPtoQ();
	findPointQtoP();
}

void makeInnerPolygon() {
	for (int i = pTop; ; i = (i + pPoints.size() - 1) % pPoints.size()) {
		innerPoints.push_back(pPoints[i]);
		if (i == pBottom) {
			break;
		}
	}
	for (int i = qBottom; ; i = (i + qPoints.size() - 1) % qPoints.size()) {
		innerPoints.push_back(qPoints[i]);
		if (i == qTop) {
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
	return result / 2;
}

void clear() {
	pPoints.clear(), qPoints.clear(), points.clear(), pHull.clear(), qHull.clear(), hull.clear(), innerPoints.clear();
}

int main() {
	ifstream inp("tangent2.inp");
	FILE *out = fopen("tangent2.out", "wt");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		init(inp);
		findPoint();
		makeInnerPolygon();
		fprintf(out, "%.1lf\n", getArea());
		clear();
	}
	return 0;
}