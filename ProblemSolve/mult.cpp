#include<fstream>
#include<vector>
#include<cmath>
using namespace std;

void solve(int n, int p, int &result) {
	for (int i = 2; i <= sqrt(n); i++) {
		if (n % i == 0) {
			int divisor = i, div = n / i;
			if (divisor >= p) {
				solve(div, divisor, result);
				result++;
			}
		}
	}
}

int main() {
	ifstream inp("mult.inp");
	ofstream out("mult.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		int n, result = 0;
		inp >> n;
		solve(n, 1, result);
		out << n << ' ' << result << '\n';
	}
	return 0;
}
