#include<fstream>
#include<algorithm>
using namespace std;

int bottles[104][104][104];

void solution() {/* 나->컴->나 인 경우에서 1, 2, 3추가되면 무조건 이김 */
	for (int i = 3; i < 104; i++) {
		for (int j = 3; j < 104; j++) {
			for (int k = 3; k < 104; k++) {
				if (!(i == 3 && j == 3 && k == 3)) {
					if (bottles[i - 1][j][k] == -1 || bottles[i][j - 1][k] == -1 || bottles[i][j][k - 1] == -1) {
						bottles[i][j][k] = 1;
					}
					else if (bottles[i - 2][j][k] == -1 || bottles[i][j - 2][k] == -1 || bottles[i][j][k - 2] == -1) {
						bottles[i][j][k] = 1;
					}
					else if (bottles[i - 3][j][k] == -1 || bottles[i][j - 3][k] == -1 || bottles[i][j][k - 3] == -1) {
						bottles[i][j][k] = 1;
					}
					else {
						bottles[i][j][k] = -1;
					}
				}
			}
		}
	}
}

int main() {
	ifstream inp("coin.inp");
	ofstream out("coin.out");
	int n;
	inp >> n;
	solution();
	while (n--) {
		int a, b, c;
		inp >> a >> b >> c;
		out << '(' << a << ' ' << b << ' ' << c << ')' << " : " << bottles[a + 3][b + 3][c + 3] << '\n';
	}
	inp.close();
	out.close();
	return 0;
}