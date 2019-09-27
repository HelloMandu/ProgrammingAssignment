#include<fstream>
using namespace std;

long long pole[21][21][21];

void poleArrangement() {
	for (int i = 1; i < 21; i++) {
		pole[i][i][1] = pole[i][1][i] = 1;
	}
	for (int i = 2; i < 21; i++) {
		for (int j = 1; j < i + 1; j++) {
			for (int k = 1; k < i + 1; k++) {
				pole[i][j][k] = pole[i - 1][j - 1][k] + pole[i - 1][j][k - 1] + pole[i - 1][j][k] * (i - 2);
			}
		}
	}
}

int main() {
	ifstream inp("pole.inp");
	ofstream out("pole.out");
	int testcase;
	inp >> testcase;
	poleArrangement();
	while (testcase--) {
		int n, l, r;
		inp >> n >> l >> r;
		out << pole[n][l][r] << '\n';
	}
	inp.close(); out.close();
	return 0;
}