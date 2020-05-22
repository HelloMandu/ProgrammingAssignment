#include <fstream>
using namespace std;

int main() {
	ifstream inp("ones.inp");
	ofstream out("ones.out");
	int n;
	while (inp >> n) {
		int cnt = 1, num = 1;
		while (num % n != 0) {
			num = (num * 10 + 1) % n;
			cnt++;
		}
		out << cnt << '\n';
	}
	return 0;
}