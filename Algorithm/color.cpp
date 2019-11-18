#include<fstream>
#include<algorithm>
#include<string>
#include<cstring>
using namespace std;

string str1, str2;
int dp[5002][5002], arr1[5002][26], arr2[5002][26];

int getLen(int x, int y, int c) {
	int ret1 = 0, ret2 = 0;
	if (arr1[x][c] + arr2[y][c] == arr1[str1.size() - 1][c] + arr2[str2.size() - 1][c]) {
		ret1 = x + y;
	}
	if (arr1[x][c] + arr2[y][c] == 1) {
		ret2 = x + y;
	}
	return ret1 - ret2;
}

int solution() {
	for (int i = 1; i < str1.size(); i++) {
		for (int j = 0; j < 26; j++) {
			arr1[i][j] = arr1[i - 1][j];
		}
		arr1[i][str1[i] - 'A']++;
	}
	for (int i = 1; i < str2.size(); i++) {
		for (int j = 0; j < 26; j++) {
			arr2[i][j] = arr2[i - 1][j];
		}
		arr2[i][str2[i] - 'A']++;
	}
	dp[0][0] = 0;
	for (int i = 0; i < str1.size(); i++) {
		for (int j = 0; j < str2.size(); j++) {
			dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + getLen(i + 1, j, str1[i + 1] - 'A'));
			dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + getLen(i, j + 1, str2[j + 1] - 'A'));
		}
	}
	return dp[str1.size() - 1][str2.size() - 1];
}

int main() {
	ifstream inp("color.inp");
	ofstream out("color.out");
	int testcase;
	inp >> testcase;
	while (testcase--){
		str1.clear(); str2.clear();
		str1.push_back('*');
		str2.push_back('*');
		string temp1, temp2;
		inp >> temp1 >> temp2;
		str1 += temp1, str2 += temp2;
		for (int i = 0; i < str1.size(); i++) {
			for (int j = 0; j < str2.size(); j++) {
				dp[i][j] = 987654321;
			}
		}
		memset(arr1, 0, sizeof(arr1));
		memset(arr2, 0, sizeof(arr2));
		out << solution() << '\n';
	}
	return 0;
}