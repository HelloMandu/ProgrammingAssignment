#include<fstream>
using namespace std;

typedef long long lint;

struct Operation {
	lint r, m;
};

Operation oper[51];
int n;

lint getGcd(lint a, lint b) {
	return b ? getGcd(b, a % b) : a;
}

lint inverse(lint n, lint mod) {
	for (int i = 1; i < mod; i++) {
		if ((n * i) % mod == 1) {
			return i;
		}
	}
	return 0;
}

Operation extendGcd(lint r1, lint r2) {
	lint s1 = 1, s2 = 0, t1 = 0, t2 = 1;
	lint q, r, s, t;
	while (r2) {
		q = r1 / r2;
		r = r1 - q * r2;
		r1 = r2; r2 = r;
		s = s1 - q * s2;
		s1 = s2; s2 = s;
		t = t1 - q * t2;
		t1 = t2; t2 = t;
	}
	return { r1, s1 };
}

lint crt() {
	for (int i = 0; i < n - 1; i++) {
		Operation cur = oper[i], next = oper[i + 1];
		next.r -= cur.r;
		while (next.r < 0) { next.r += next.m; }
		lint gcd = getGcd(getGcd(cur.m, next.r), next.m);
		next.r /= gcd, next.m /= gcd;
		Operation exGcd = extendGcd(cur.m / gcd, next.m);
		if (next.r % exGcd.r != 0) { return -1; }
		lint s = exGcd.m;
		next.r = (next.r * s) % next.m;
		while (next.r < 0) { next.r += next.m; }
		oper[i + 1] = { cur.r + cur.m * next.r, cur.m * next.m };
	}
	return oper[n - 1].r;
}

int main() {
	ifstream inp("crt.inp");
	ofstream out("crt.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		inp >> n;
		for (int i = 0; i < n; i++) {
			inp >> oper[i].r >> oper[i].m;
		}
		out << crt() << '\n';
	}
	return 0;
}