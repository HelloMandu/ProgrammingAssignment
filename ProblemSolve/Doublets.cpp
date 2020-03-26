#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;

vector<string> words;
int parent[25144];
bool isVisit[25144];
int sIdx, eIdx;

bool isDoublets(string a, string b) {
	bool diff = false;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] != b[i]) {
			if (!diff) {
				diff = true;
			}
			else {
				return false;
			}
		}
	}
	return true;
}

bool findSequence(string start, string end) {
	for (int i = 0; i < words.size(); i++) {
		if (start == words[i]) {
			sIdx = i;
			break;
		}
	}
	for (int i = 0; i < words.size(); i++) {
		if (end == words[i]) {
			eIdx = i;
			break;
		}
	}
	parent[sIdx] = sIdx;
	isVisit[sIdx] = true;
	queue<int> Queue; Queue.push(sIdx);
	while (!Queue.empty()) {
		int front = Queue.front(); Queue.pop();
		if (front == eIdx) {
			return true;
		}
		for (int i = 0; i < words.size(); i++) {
			if (!isVisit[i] && isDoublets(words[front], words[i])) {
				parent[i] = front;
				isVisit[i] = true;
				Queue.push(i);
			}
		}
	}
	return false;
}

void printResult(ofstream &out, int sIdx, int eIdx) {
	if (sIdx != eIdx) {
		printResult(out, sIdx, parent[eIdx]);
	}
	out << words[eIdx] << '\n';
}


int main() {
	ifstream inp("Doublets.inp");
	ofstream out("Doublets.out");
	string word;
	while (getline(inp, word) && word.size()) {
		if (word.back() != ' ') {
			word.push_back(' ');
		}
		words.push_back(word);
	}
	string start, end;
	while (inp >> start >> end) {
		start.push_back(' ');
		end.push_back(' ');
		memset(parent, 0, sizeof(parent));
		memset(isVisit, false, sizeof(isVisit));
		if (start.size() == end.size() && findSequence(start, end)) {
			printResult(out, sIdx, eIdx);
		}
		else {
			out << "No solution." << '\n';
		}
		out << '\n';
	}
	return 0;
}