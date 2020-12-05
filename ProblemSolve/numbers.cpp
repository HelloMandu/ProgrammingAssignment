#include<fstream>
#include<string>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;


int arr[10001];

int main() {
	ifstream inp("numbers.inp");
	ofstream out("numbers.out");
	int testcase;
	inp >> testcase;
	for (int t = 1; t <= testcase; t++) {
		int n;
		inp >> n;
		for (int i = 0; i < n; i++) {
			inp >> arr[i];
		}
		sort(arr, arr + n);
		out << "Test Case #" << t << " : " << abs(arr[n - 2] - arr[1]) << '\n';
	}
	return 0;
}