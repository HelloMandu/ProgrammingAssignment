#include<fstream>
#include<algorithm>
#include<string>
#include<cstring>
using namespace std;

struct Rect {
	int x, y, dx, dy;
};

Rect rect[10001];
int n;

int main() {
	ifstream inp("block.inp");
	ofstream out("block.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		inp >> n;
		for (int i = 0; i < n; i++) {
			inp >> rect[i].x >> rect[i].y >> rect[i].dx >> rect[i].dy;
			rect[i].dx += rect[i].x, rect[i].dy += rect[i].y;
		}
	}
	return 0;
}