#include<fstream>
#include<algorithm>
#include<cstring>
using namespace std;

int card[1001];
int cache[1001][3];
int main() {
	ifstream inp("card.inp");
	ofstream out("card.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		int n;
		inp >> n;

		memset(cache, 0, sizeof(cache));
	}
	return 0;
}