#include<fstream>
#include<string>
using namespace std;

string str;
string::iterator cur;

/*
1. Its first character is either a ¡¯D¡¯ or an ¡¯E¡¯.
2. The first character is followed by a string of one or more ¡¯F¡¯s.
3. The string of one or more ¡¯F¡¯s is followed by either a Slump or a ¡¯G¡¯. The Slump or ¡¯G¡¯ that
follows the F¡¯s ends the Slump. For example DFFEFFFG is a Slump since it has a ¡¯D¡¯ for its first
character, followed by a string of two F¡¯s, and ended by the Slump ¡¯EFFFG¡¯.
*/
bool isSlump() {
	cur++;
	while (*cur == 'D' || *cur == 'E') {
		cur++;
		if (*cur != 'F') {
			return false;
		}
		while (*cur == 'F') {
			cur++;
			if (*cur == 'D' || *cur == 'E') {
				break;
			}
		}
	}
	return *cur == 'G';
}

/*
1. Its first character is an ¡¯A¡¯.
2. If it is a two character Slimp then its second and last character is an ¡¯H¡¯.
3. If it is not a two character Slimp then it is in one of these two forms:
a) ¡¯A¡¯ followed by ¡¯B¡¯ followed by a Slimp followed by a ¡¯C¡¯.
b) ¡¯A¡¯ followed by a Slump (see above) followed by a ¡¯C¡¯.
*/
bool isSlimp() {
	if (*cur == 'A') {
		cur++;
		if (*cur == 'H') {
			return true;
		}
		else if (*cur == 'B') {
			cur++;
			if (isSlimp() && cur != str.end() - 1) {
				return *(++cur) == 'C';
			}
		}
		else {
			cur--;
			if (isSlump() && cur != str.end() - 1) {
				return *(++cur) == 'C';
			}
		}
	}
	return false;
}

bool isSlurpys() {
	return isSlimp() && isSlump() && cur == str.end() - 1;
}

int main() {
	ifstream inp("Slurpys.inp");
	ofstream out("Slurpys.out");
	int testcase;
	inp >> testcase;
	out << "SLURPYS OUTPUT" << '\n';
	while (testcase--) {
		inp >> str;
		cur = str.begin();
		out << (isSlurpys() ? "YES" : "NO") << '\n';
	}
	out << "END OF OUTPUT" << '\n';
	return 0;
}