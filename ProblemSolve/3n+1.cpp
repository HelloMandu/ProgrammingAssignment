#include<fstream>
#include<algorithm>
#include<cstring>
using namespace std;

/*세그먼트트리 이용해서 다시해보기*/

typedef long long lint;

lint sequence(lint n) {
	if (n == 1) {
		return 1;
	}
	else if ((n % 2) != 0) {
		return sequence(3 * n + 1) + 1;
	}
	else {
		return sequence(n / 2) + 1;
	}
}

int main() {
	ifstream inp("3n+1.inp");
	ofstream out("3n+1.out");
	int a, b;
	while (inp >> a >> b) {
		int start, end;
		if (a < b) { start = a, end = b; }
		else { start = b, end = a; }
		lint result = 0;
		for (int i = start; i <= end; i++) {
			result = max(result, sequence(i));
		}
		out << a << ' ' << b << ' ' << result << '\n';
	}
	return 0;
}