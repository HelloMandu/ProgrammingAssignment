#include<fstream>
#include<algorithm>
using namespace std;

int alice[10001][10001], robot[10001][10001];
int main() {
	ifstream inp("card.inp");
	ofstream out("card.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		int n;
		inp >> n;
		for (int i = 0; i < n; i++) {
			inp >> alice[i][i];
		}
		for (int j = 1; j < n; j++) {
			for (int i = 0; i + j < n; i++) {
				robot[i][j + i] = min(alice[i][j + i - 1], alice[i + 1][j + i]);
				alice[i][j + i] = (alice[i][j + i - 1] + robot[i][j + i - 1] + alice[j + i][j + i]) - robot[i][j + i];
			}
		}
		out << alice[0][n - 1] << '\n';
	}
	return 0;
}