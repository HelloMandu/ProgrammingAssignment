#include<fstream>
#include<algorithm>
#include<string>
using namespace std;
#pragma warning(disable:4996)

int shuff[101][53], card[53], n;
string suits[4] = { "Clubs", "Diamonds", "Hearts", "Spades" };
string values[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
bool isFirst;
char line[10];

int main() {
	FILE *inp = fopen("StackThemUp.inp", "rt");
	ofstream out("StackThemUp.out");

	int testcase;
	fscanf(inp, "%d\n", &testcase);
	while (testcase--) {
		fscanf(inp, "%d\n", &n);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= 52; j++) {
				fscanf(inp, "%d", &shuff[i][j]);
			}
		}
		for (int i = 1; i <= 52; i++) {
			card[i] = i;
		}
		fgets(line, 10, inp);
		while (fgets(line, 10, inp)) {
			if (line[0] == '\n') { break; }
			sscanf(line, "%d", &n);
			int deck[53];
			for (int i = 1; i <= 52; i++) {
				deck[i] = card[shuff[n][i]];
			}
			for (int i = 1; i <= 52; i++) {
				card[i] = deck[i];
			}
		}
		if (isFirst) { out << "\n"; }
		isFirst = true;
		for (int i = 1; i <= 52; i++) {
			out << values[(card[i] - 1) % 13] << " of " << suits[(card[i] - 1) / 13] << '\n';
		}
	}
	return 0;
}
