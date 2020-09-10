#include<fstream>
#include<algorithm>
using namespace std;

int arr[11][11];
int start, finish, blocks;

int main() {
	ifstream inp("path.inp");
	ofstream out("path.out");
	ios_base::sync_with_stdio(false), inp.tie(NULL), out.tie(NULL);
	inp >> start >> finish >> blocks;
	int sY = start / 10, sX = start % 10;
	int fY = finish / 10, fX = finish % 10;
	for (int i = 0; i < blocks; i++) {
		int block;
		inp >> block;
		arr[block / 10][block % 10] = -1;
	}
	if (sY <= fY && sX <= fX) {
		arr[sY][sX] = 1;
		bool flag = false;
		for (int i = sX + 1; i <= fX; i++) {
			if (arr[sY][i] == -1) {
				flag = true;
			}
			arr[sY][i] = flag ? 0 : 1;
		}
		flag = false;
		for (int i = sY + 1; i <= fY; i++) {
			if (arr[i][sX] == -1) {
				flag = true;
			}
			arr[i][sX] = flag ? 0 : 1;
		}
		for (int i = sY + 1; i <= fY; i++) {
			for (int j = sX + 1; j <= fX; j++) {
				if (arr[i][j] != -1) {
					arr[i][j] = arr[i - 1][j] + arr[i][j - 1];
				}
				else {
					arr[i][j] = 0;
				}
			}
		}
	}
	else if (sY <= fY && sX >= fX) {
		arr[sY][sX] = 1;
		bool flag = false;
		for (int i = sX - 1; i >= fX; i--) {
			if (arr[sY][i] == -1) {
				flag = true;
			}
			arr[sY][i] = flag ? 0 : 1;
		}
		flag = false;
		for (int i = sY + 1; i <= fY; i++) {
			if (arr[i][sX] == -1) {
				flag = true;
			}
			arr[i][sX] = flag ? 0 : 1;
		}
		for (int i = sY + 1; i <= fY; i++) {
			for (int j = sX - 1; j >= fX; j--) {
				if (arr[i][j] != -1) {
					arr[i][j] = arr[i - 1][j] + arr[i][j + 1];
				}
				else {
					arr[i][j] = 0;
				}
			}
		}
	}
	else if (sY >= fY && sX <= fX) {
		arr[sY][sX] = 1;
		bool flag = false;
		for (int i = sX + 1; i <= fX; i++) {
			if (arr[sY][i] == -1) {
				flag = true;
			}
			arr[sY][i] = flag ? 0 : 1;
		}
		flag = false;
		for (int i = sY - 1; i >= fY; i--) {
			if (arr[i][sX] == -1) {
				flag = true;
			}
			arr[i][sX] = flag ? 0 : 1;
		}
		for (int i = sY - 1; i >= fY; i--) {
			for (int j = sX + 1; j <= fX; j++) {
				if (arr[i][j] != -1) {
					arr[i][j] = arr[i + 1][j] + arr[i][j - 1];
				}
				else {
					arr[i][j] = 0;
				}
			}
		}
	}
	else {
		arr[sY][sX] = 1;
		bool flag = false;
		for (int i = sX - 1; i >= fX; i--) {
			if (arr[sY][i] == -1) {
				flag = true;
			}
			arr[sY][i] = flag ? 0 : 1;
		}
		flag = false;
		for (int i = sY - 1; i >= fY; i--) {
			if (arr[i][sX] == -1) {
				flag = true;
			}
			arr[i][sX] = flag ? 0 : 1;
		}
		for (int i = sY - 1; i >= fY; i--) {
			for (int j = sX - 1; j >= fX; j--) {
				if (arr[i][j] != -1) {
					arr[i][j] = arr[i + 1][j] + arr[i][j + 1];
				}
				else {
					arr[i][j] = 0;
				}
			}
		}
	}
	out << arr[fY][fX];
	return 0;
}