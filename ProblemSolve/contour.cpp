#include<fstream>
#include<vector>
#include<set>
#include<algorithm>
#define START true
#define END false
using namespace std;
#pragma warning(disable:4996)

typedef long long lint;

struct Rectangle {
	lint x, y; 
	bool type;
	bool operator<(const Rectangle &a) {
		return x < a.x;
	}
};

vector<Rectangle> rec;
int visit[1000001];

bool input(ifstream &inp) {
	rec.clear();
	lint l = 0, h, r;
	while (inp >> l >> h >> r) {
		if (l == 0) { break; }
		rec.push_back({ l, h, START });
		rec.push_back({ r, h, END });
	}
	return rec.size();
}

int main() {
	ifstream inp("contour.inp");
	ofstream out("contour.out");
	for (int t = 1; ; t++) {
		if (!input(inp)) { break; }
		sort(rec.begin(), rec.end());
		vector<lint> result;
		set<lint> s;
		lint area = 0;
		for (int i = 0; i < rec.size(); i++) {
			if (i && s.size()) {
				area += (rec[i].x - rec[i - 1].x) * (*(--s.end()));
			}
			if (rec[i].type == START) {
				if (++visit[rec[i].y] == 1) { s.insert(rec[i].y); }
			}
			else {
				if (--visit[rec[i].y] == 0) { s.erase(rec[i].y); }
				if (s.empty() && area) {
					result.push_back(area);
					area = 0;
				}
			}
		}
		out << "Test Case #" << t << " : ";
		for (int i = 0; i < result.size(); i++) {
			out << result[i] << ' ';
		}
		out << '\n';
	}
	return 0;
}