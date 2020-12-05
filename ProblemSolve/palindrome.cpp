#include<fstream>
#include<string>
#include<algorithm>
#include<cstring>
using namespace std;

void init(string &str) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] += 32;
		}
	}
}

int isPalindrome(string& str) {
	for (int i = 0; i < str.length() / 2; i++) {
		if (str[i] != str[str.length() - i - 1]) {
			return 0;
		}
	}
	return 1;
}

int main() {
	ifstream inp("palindrome.inp");
	ofstream out("palindrome.out");
	int n;
	inp >> n;
	while (n--) {
		string str;
		inp >> str;
		init(str);
		out << isPalindrome(str) << '\n';
	}
	return 0;
}