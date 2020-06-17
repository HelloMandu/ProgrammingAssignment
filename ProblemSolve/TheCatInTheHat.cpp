#include<fstream>
#include<cmath>
using namespace std;
#pragma warning(disable:4996)

typedef long long lint;

int main() {
	FILE *inp = fopen("TheCatInTheHat.inp", "r");
	FILE *out = fopen("TheCatInTheHat.out", "w");
	lint height, worker;
	while (fscanf(inp, "%lld %lld\n", &height, &worker)) {
		if (height == 0) { break; }
		double c = log(height) / log(worker);
		int left = 1, right = 2147483645, mid = (left + right) / 2;
		while (left <= right) {
			if (log(mid + 1) / log(mid) - c > 0.000000000001) left = mid + 1;
			else if (log(mid + 1) / log(mid) - c < -0.000000000001) right = mid - 1;
			else break;
			mid = (left + right) / 2;
		}
		int n = mid, level = round(log(height) / (log(n + 1)));
		lint notWorking = 0, totalHeight = 0;
		int cnt = 1;
		for (int i = 0; i < level; i++) {
			notWorking += cnt;
			totalHeight += (height * cnt);
			cnt *= n;
			height /= (n + 1);
		}
		totalHeight += cnt;
		fprintf(out, "%lld %lld\n", notWorking, totalHeight);
	}
	return 0;
}