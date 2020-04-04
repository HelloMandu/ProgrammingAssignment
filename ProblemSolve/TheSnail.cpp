#include<fstream>
using namespace std;

int getFatigue(int& wall, int& up, int& down, int percent) {
	wall *= 100;
	up *= 100;
	down *= 100;
	return up * percent / 100;
}

int main() {
	ifstream inp("TheSnail.inp");
	ofstream out("TheSnail.out");
	int wall, up, down, percent, fatigue;
	while (inp >> wall >> up >> down >> percent) {
		if (wall == 0) {
			return 0;
		}
		fatigue = getFatigue(wall, up, down, percent);
		int height = 0, days = 1;
		while (true) {
			if (up > 0) {
				height += up;
			}
			if (height > wall) {
				out << "success on day " << days << '\n';
				break;
			}
			height -= down;
			up -= fatigue;
			if (height <= 0) {
				out << "failure on day " << days << '\n';
				break;
			}
			days++;
		}
	}
}