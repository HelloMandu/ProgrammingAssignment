#include<fstream>
#include<cmath>
using namespace std;
#pragma warning(disable:4996)

int main() {
	FILE *inp = fopen("cryptography.inp", "r");
	FILE *out = fopen("cryptography.out", "w");
	double n, p;
	while (fscanf(inp, "%lf\n%lf\n", &n, &p) != -1) {
		fprintf(out, "%.0lf\n", pow(p, 1 / n));
	}
	return 0;
}