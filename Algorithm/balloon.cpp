#include<fstream>
#include<algorithm>
#include<cstring>
using namespace std;

int n;
int arr[1001];
int cache[1001];
int result = 0;
int length = 0;

void getRoute(int cur, int count) {
	if (count == 1) {
		result++;
		return;
	}
	for (int i = cur - 1; i >= 0; i--) {
		if (arr[cur] > arr[i] && (cache[i] == count - 1)) {
			getRoute(i, count - 1);
		}
	}
}

int main() {
	ifstream inp("balloon.inp");
	ofstream out("balloon.out");
	while (inp >> n) {
		if (n == 0) {
			return 0;
		}
		result = 0;
		length = 0;
		memset(cache, 0, sizeof(cache));
		for (int i = 0; i < n; i++) {
			inp >> arr[i];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < i; j++) {
				if (arr[i] > arr[j]) {
					cache[i] = max(cache[i], cache[j]);
				}
			}
			cache[i] += 1;
			length = max(length, cache[i]);
		}
		for (int i = 0; i < n; i++) {
			if (cache[i] == length) {
				getRoute(i, length);
			}
		}
		out << length << ' ' << result << '\n';
	}
	return 0;
}