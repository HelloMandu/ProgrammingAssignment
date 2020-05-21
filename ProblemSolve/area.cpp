#include<fstream>
#include<cmath>
using namespace std;
#pragma warning(disable:4996)

struct Point {
	double x, y;
};

struct Circle {
	Point point;
	double radius;
};

Circle circle[3];
Point triangle[3];

bool innerCircle(Circle c, Point p) {
	Point diff;
	diff.x = p.x - c.point.x, diff.y = p.y - c.point.y;
	return sqrt((diff.x * diff.x) + (diff.y * diff.y)) < c.radius;
}

Point getPoint(Circle c1, Circle c2, Circle other) {
	Point one, two, diff;
	double l, k;
	diff.x = c2.point.x - c1.point.x;
	diff.y = c2.point.y - c1.point.y;
	l = sqrt((diff.x * diff.x) + (diff.y * diff.y));
	k = ((l * l) + (c1.radius * c1.radius) - (c2.radius * c2.radius)) / (2 * l);
	one.x = c1.point.x + (diff.x * k / l) + (diff.y / l) * sqrt((c1.radius * c1.radius) - k * k);
	one.y = c1.point.y + (diff.y * k / l) - (diff.x / l) * sqrt((c1.radius * c1.radius) - k * k);
	two.x = c1.point.x + (diff.x * k / l) - (diff.y / l) * sqrt((c1.radius * c1.radius) - k * k);
	two.y = c1.point.y + (diff.y * k / l) + (diff.x / l) * sqrt((c1.radius * c1.radius) - k * k);
	return innerCircle(other, one) ? one : two;
}

double getArea() {
	double result = 0.0;
	for (int i = 0; i < 3; i++) {
		int j = (i + 1) % 3;
		result += (triangle[i].x * triangle[j].y) - (triangle[i].y * triangle[j].x);
	}
	return abs(result / 2);
}

int main() {
	ifstream inp("area.inp");
	FILE *out = fopen("area.out", "wt");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		for (int i = 0; i < 3; i++) {
			inp >> circle[i].point.x >> circle[i].point.y >> circle[i].radius;
		}
		triangle[0] = getPoint(circle[0], circle[1], circle[2]);
		triangle[1] = getPoint(circle[0], circle[2], circle[1]);
		triangle[2] = getPoint(circle[1], circle[2], circle[0]);
		fprintf(out, "%.2lf\n", getArea());
	}
	return 0;
}