#include<fstream>
#include<string>
#define DOWN 0
#define RIGHT 1
#define TOP 2
#define LEFT 3
using namespace std;

string str;

void input(ifstream &inp) {
	inp >> str;
	str.push_back(str[0]);
	str.push_back(str[1]);
}

int pandora() {
	int y = 1, x = 1;
	int ppdir = 0, pdir = 0, dir = 0;
	for (int i = 0; i < str.length(); i++) {
		ppdir = pdir;
		pdir = dir;
		if (str[i] == 'L') {
			dir = (dir + 1) % 4;
		}
		else {
			dir = (dir + 3) % 4;
		}
		if ((ppdir == DOWN && pdir == LEFT && dir == TOP) || (ppdir == TOP && pdir == RIGHT && dir == DOWN)) {
			y = 0;
		}
		else if ((ppdir == RIGHT && pdir == DOWN && dir == LEFT) || (ppdir == LEFT && pdir == TOP && dir == RIGHT)) {
			x = 0;
		}
	}
	return y + x;
}

int main() {
	ifstream inp("pandora.inp");
	ofstream out("pandora.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		input(inp);
		out << pandora() << '\n';
	}
	return 0;
}