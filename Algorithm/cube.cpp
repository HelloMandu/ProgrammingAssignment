#include<fstream>
#include<string>
#include<cstring>
using namespace std;

string cube1, cube2;
char maked[6];
bool isVisit[6];
int idx[3];
int check[12][3] = { // ³ë°¡´Ù ÁË¼ÛÇÔµÂ;
	{1, 2, 3},
	{1, 3, 5},
	{1, 5, 4},
	{1, 4, 2},
	{2, 1, 4},
	{2, 4, 6},
	{2, 6, 3},
	{2, 3, 1},
	{3, 1, 2},
	{3, 2, 6},
	{3, 6, 5},
	{3, 5, 1}
};

void setCube(string &str) {
	cube1 = str.substr(0, 6);
	cube2 = str.substr(6, 12);
}

bool isSame() {
	for (int i = 0; i < 6; i++) {
		if (cube2[i] != maked[i]) {
			return false;
		}
	}
	return true;
}

bool findCube(int i) {
	for (int j = 1; j < 3; j++) {
		if (check[i][j] - 1 != idx[j]) {
			return false;
		}
	}
	return true;
}

bool isCube() {
	if (idx[0] < 3) {
		for (int i = (idx[0] * 4); i < (idx[0] * 4) + 4; i++) {
			if (findCube(i)) {
				return true;
			}
		}
		return false;
	}
	else {
		for (int i = (6 - (idx[0] + 1)) * 4; i < (idx[0] * 4) + 4; i++) {
			if (findCube(i)) {
				return false;
			}
		}
		return true;
	}
}

bool makeCube(int count = 0) {
	if (count == 3) {
		return isSame() && isCube();
	}
	for (int i = 0; i < 6; i++) {
		if (!isVisit[i]) {
			isVisit[i] = isVisit[6 - (i + 1)] = true;
			maked[count] = cube1[i];
			maked[6 - (count + 1)] = cube1[6 - (i + 1)];
			idx[count] = i;
			if (makeCube(count + 1)) {
				return true;
			}
			isVisit[i] = isVisit[6 - (i + 1)] = false;
		}
	}
	return false;
}

int main() {
	ifstream inp("cube.inp");
	ofstream out("cube.out");
	string str;
	while (inp >> str) {
		setCube(str);
		out << (makeCube() ? "TRUE" : "FALSE") << '\n';
		memset(isVisit, false, sizeof(isVisit));
	}
	inp.close(); out.close();
	return 0;
}