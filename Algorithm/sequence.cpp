#include<fstream>
#include<algorithm>
using namespace std;

int n;
int s[1001], c[1001];

bool compare(int& a, int& b) {
	return a > b;
}

int main() {
	ifstream inp("sequence.inp");
	ofstream out("sequence.out");
	ios_base::sync_with_stdio(false), inp.tie(NULL), out.tie(NULL);
	inp >> n;
	for (int i = 0; i < n; i++) {
		inp >> s[i];
	}
	for (int i = 0; i < n; i++) {
		inp >> c[i];
	}
	sort(s, s + n, compare);
	for (int i = n - 1; i > 0; i--) {
		for (int j = i - c[i]; j < i; j++) {
			swap(s[j], s[j + 1]);
		}
	}
	for (int i = 0; i < n; i++) {
		out << s[i] << '\n';
	}
	return 0;
}