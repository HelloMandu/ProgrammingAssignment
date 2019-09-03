#include<fstream>
#include<string>
#include<algorithm>
using namespace std;

int cache[1001][1001];

string reverseStr(string str) {
	string reverse;
	for (int i = 0; i < str.length(); i++) {
		reverse.push_back(str[str.size() - (i + 1)]);
	}
	return reverse;
}

void lcs(string str1, string str2) {
	for (int i = 1; i <= str2.length(); i++) {
		for (int j = 1; j <= str1.length(); j++) {
			if (str2[i - 1] == str1[j - 1]) {
				cache[i][j] = cache[i - 1][j - 1] + 1;
			}
			else {
				cache[i][j] = max(cache[i - 1][j], cache[i][j - 1]);
			}
		}
	}
}

int main() {
	ifstream inp("palindrome.inp");
	ofstream out("palindrome.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		string str1, str2;
		inp >> str1;
		str2 = reverseStr(str1);
		lcs(str1, str2);
		if (str1.length() - cache[str1.length()][str2.length()] > 2) {
			out << -1 << '\n';
		}
		else {
			out << str1.length() - cache[str1.length()][str2.length()] << '\n';
		}
	}

	return 0;
}