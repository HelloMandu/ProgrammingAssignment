#include<fstream>
#include<algorithm>
#include<cmath>
using namespace std;
#pragma warning(disable:4996)

int cost[1001];

int main() {
	FILE *inp = fopen("Trip.inp", "r");
	FILE *out = fopen("Trip.out", "w");
	int n;
	while (fscanf(inp, "%d", &n)) {
		int sum = 0, lowerAvg, upperAvg;
		if (n == 0) {
			return 0;
		}
		for (int i = 0; i < n; i++) {
			int dollor, cent;
			fscanf(inp, "%d.%d", &dollor, &cent);
			cost[i] = dollor * 100 + cent;
			sum += cost[i];
 		}
		lowerAvg = sum / n;
		upperAvg = ceil((double)sum / n);
		int smallResult = 0, largeResult = 0;
		for (int i = 0; i < n; i++) {
			if (cost[i] < lowerAvg) {
				smallResult += lowerAvg - cost[i];
			}
			else if(upperAvg < cost[i]) {
				largeResult += cost[i] - upperAvg;
			}
		}
		int result = max(smallResult, largeResult);
		fprintf(out, "$%d.%02d\n", result / 100, result % 100);
	}
}