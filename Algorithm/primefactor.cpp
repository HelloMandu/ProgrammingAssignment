#include<fstream>
using namespace std;

int getPrime(int n) {
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			return i;
		}
	}
	return n;
}

int main() {
	ifstream inp("primefactor.inp");
	ofstream out("primefactor.out");
	ios_base::sync_with_stdio(false), inp.tie(NULL), out.tie(NULL);
	int testcase;
	inp >> testcase;
	while (testcase--) {
		int n, result = 0, cnt = 0;
		inp >> n;
		while (n > 1) {
			int prime = getPrime(n);
			result += prime;
			n /= prime;
			cnt++;
		}
		if (cnt == 1) {
			out << "Prime Number\n";
		}
		else {
			out << result << '\n';
		}
	}
	return 0;
}