#include<fstream>
#include<algorithm>
#include<cstring>
using namespace std;

int arr[1000001];

int main() {
	ifstream inp("coinmove.inp");
	ofstream out("coinmove.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		int p, k, s;
		inp >> p >> k >> s;

		memset(arr, 0, sizeof(arr));
	}
	inp.close(); out.close();
	return 0;
}
