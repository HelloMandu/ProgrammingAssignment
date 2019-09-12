#include<fstream>
#include<string>
#include<algorithm>
#include<stack>
#include<vector>
using namespace std;

void input(ifstream &inp, vector<string> &inputStr) {
	stack<string> Stack;
	string temp;
	inp >> temp;
	Stack.push("(");
	inputStr.push_back(temp);
	while (!Stack.empty()) {
		inp >> temp;
		if (temp == "(") {
			Stack.push("(");
		}
		else if (temp == ")") {
			Stack.pop();
		}
		inputStr.push_back(temp);
	}
}

void printInput(ofstream &out, vector<string> &inputStr) {
	for (int i = 0; i < inputStr.size(); i++) {
		out << inputStr[i] << ' ';
	}
	out << '\n';
}

void preorder(ofstream &out, vector<string> &inputStr) {
	int internal = 0;
	for (int i = 0; i < inputStr.size(); i++) {
		if (inputStr[i] == "(") {
			out << 'r' << internal++ << '\n';
		}
		else if (inputStr[i] != ")") {
			out << inputStr[i] << '\n';
		}
	}
}

void inorder(ofstream &out, vector<string> &inputStr) {
	int internal = 0;
	stack<int> Stack;
	for (int i = 0; i < inputStr.size(); i++) {
		if (inputStr[i] == "(") {
			Stack.push(internal++);
		}
		else if (inputStr[i] != ")") {
			out << inputStr[i] << '\n';
			if (!Stack.empty()) {
				out << 'r' << Stack.top() << '\n';
				Stack.pop();
			}
		}
	}
}

int main() {
	ifstream inp("tree.inp");
	ofstream out("tree.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		vector<string> inputStr;
		input(inp, inputStr);
		printInput(out, inputStr);
		out << "Preorder" << '\n';
		preorder(out, inputStr);
		out << "Inorder" << '\n';
		inorder(out, inputStr);
	}
	return 0;
}