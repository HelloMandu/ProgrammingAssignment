#include<fstream>
using namespace std;

bool isSpare(int first, int second) {
	return (first + second) == 10;
}

bool isStrike(int score) {
	return score == 10;
}

int main() {
	ifstream inp("bowling.inp");
	ofstream out("bowling.out");

	int testcase;
	inp >> testcase;
	while (testcase--) {
		pair<int, int> arr[10];
		for (int i = 0; i < 9; i++) {
			inp >> arr[i].first;
			if (!isStrike(arr[i].first)) {
				inp >> arr[i].second;
			}
		}
		inp >> arr[9].first >> arr[9].second;
		int allScore = 0;
		for (int i = 0; i < 9; i++) {
			allScore += arr[i].first + arr[i].second;
			if (isStrike(arr[i].first)) {
				if (isStrike(arr[i + 1].first) && i != 8) {
					allScore += arr[i + 1].first + arr[i + 2].first;
				}
				else {
					allScore += arr[i + 1].first + arr[i + 1].second;
				}
			}
			else if (isSpare(arr[i].first, arr[i].second)) {
				allScore += arr[i + 1].first;
			}
		}
		allScore += arr[9].first + arr[9].second;
		if (arr[9].first + arr[9].second > 9) {
			int third;
			inp >> third;
			allScore += third;
		}
		out << allScore << '\n';
	}
	return 0;
}