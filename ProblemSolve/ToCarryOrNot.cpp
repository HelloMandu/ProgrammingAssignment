#include<fstream>
#include<string>
#include<algorithm>
using namespace std;

typedef unsigned int uInt;

string decimalToBinary(uInt n) {
	string result;
	while (n) {
		result.push_back((n % 2) + '0');
		n /= 2;
	}
	return result;
}

string addBinary(string &bn1, string &bn2) {
	string result;
	int length = min(bn1.size(), bn2.size());
	for (int i = 0; i < length; i++) {
		if (bn1[i] != bn2[i]) {
			result.push_back('1');
		}
		else {
			result.push_back('0');
		}
	}
	for (int i = length; i < bn1.size(); i++) {
		result.push_back(bn1[i]);
	}
	for (int i = length; i < bn2.size(); i++) {
		result.push_back(bn2[i]);
	}
	return result;
}

uInt binaryToDecimal(string &bn) {
	uInt result = 0;
	for (int i = 0; i < bn.size(); i++) {
		result += (bn[i] - '0') << i;
	}
	return result;
}

int main() {
	ifstream inp("ToCarryOrNot.inp");
	ofstream out("ToCarryOrNot.out");
	string bn1, bn2;
	string bResult;
	uInt n1, n2;
	while (inp >> n1 >> n2) {
		bn1 = decimalToBinary(n1), bn2 = decimalToBinary(n2);
		bResult = addBinary(bn1, bn2);
		out << binaryToDecimal(bResult) << '\n';
	}
	return 0;
}