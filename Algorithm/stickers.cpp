#include<fstream>
#include<algorithm>
using namespace std;

int arr[2][100001];

int main() {
	ifstream inp("stickers.inp");
	ofstream out("stickers.out");
	int testcase, n;
	inp >> testcase;
	while (testcase--) {
		inp >> n;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < n; j++) {
				inp >> arr[i][j];
			}
		}
		arr[0][1] += arr[1][0];
		arr[1][1] += arr[0][0];
		for (int i = 2; i < n; i++) {
			arr[0][i] += max(arr[1][i - 1], arr[1][i - 2]);
			arr[1][i] += max(arr[0][i - 1], arr[0][i - 2]);
		}
		out << max(arr[0][n - 1], arr[1][n - 1]) << '\n';
	}
	return 0;
}