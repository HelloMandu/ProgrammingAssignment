#include<fstream>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;

vector<int> rec;

int getGcd(int a, int b) {
	return b ? getGcd(b, a % b) : a;
}

void pythagorean() {
	map<pair<int, int>, bool> cache;
	for (int i = 2; i < 500; i++) {
		int j = i % 2 ? 2 : 1;
		for (; j < i; j += 2) {
			int w = 2 * i * j, h = i * i - j * j;
			int gcd = getGcd(w, h);
			w /= gcd, h /= gcd;
			if (w > h) { swap(w, h); }
			if (!cache[make_pair(w, h)]) {
				cache[make_pair(w, h)] = true;
				rec.push_back(2 * (w + h));
			}
		}
	}
	sort(rec.begin(), rec.end());
}

int getResult(int wire) {
	int cnt = 0;
	while (wire - rec[cnt] >= 0) {
		wire -= rec[cnt++];
	}
	return cnt;
}

int main() {
	ifstream inp("rectangles.inp");
	ofstream out("rectangles.out");
	pythagorean();
	int testcase;
	inp >> testcase;
	while (testcase--) {
		int wire;
		inp >> wire;
		out << getResult(wire) << '\n';
	}
	return 0;
}