#include <fstream>
#include <vector>
using namespace std;

vector <int> number, result;
vector <char> opt;

bool calc() {
	for (int i = 0; i < number.size() - 1; i++) {
		int a = number[i];
		int b = number[i + 1];
		char c = opt[i];
		if (c != '+' && c != '-') {
			switch (c)
			{
			case '*':
				number[i] = a * b;
				break;
			case '/':
				if (b == 0) return false;
				number[i] = a / b;
				break;
			case '%':
				if (b == 0) return false;
				number[i] = a % b;
				break;
			}
		}
		number.erase(number.begin() + i + 1);
		opt.erase(opt.begin() + i--);
	}

	for (int i = 0; i < number.size() - 1; i++) {
		int a = number[i];
		int b = number[i + 1];
		char c = opt[i];
		switch (c) {
		case '+':
			number[i] = a + b;
			break;
		case '-':
			number[i] = a - b;
			break;
		}
		number.erase(number.begin() + i + 1);
		opt.erase(opt.begin() + i--);
	}
	return true;
}

int main() {
	ifstream inp("expression.inp");
	ofstream out("expression.out");
	int n, a; char c;
	inp >> n;
	for (int i = 0; i < n; i++) {
		while (true) {
			inp >> a >> c;
			number.push_back(a);
			opt.push_back(c);
			if (c == '=') break;
		}
		if (calc()) {
			out << number[0] << '\n';
		}
		else {
			out << "Error!" << '\n';
		}
		number.clear(); opt.clear();
	}
	return 0;
}
