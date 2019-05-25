#include<fstream>
#include<vector>
#include<algorithm>
#define MAX 100001
using namespace std;

struct Page {
	int pid, pageNumber;
};

struct Heap {
	int index, pid, pageNumber;
};

bool compare(Heap &p1, Heap &p2) {
	return p1.index > p2.index;
}

int n;
vector<Page> input;
vector<Page> memory;

void inputPage(ifstream &inp) {
	inp >> n;
	while (true) {
		int pid, pageNumber;
		inp >> pid >> pageNumber;
		if (pid == -1 && pageNumber == -1) {return;}
		input.push_back({ pid, pageNumber });
	}
}

bool isFull(int frame[], int pid) {
	return frame[pid] == n;
}

bool hasPage(vector<Page> &pageTable, Page page) {
	for (int i = 0; i < pageTable.size(); i++) {
		if (pageTable[i].pid == page.pid && pageTable[i].pageNumber == page.pageNumber) {
			return true;
		}
	}
	return false;
}

void pushPage(vector<Page> &pageTable, vector<Page> &Stack, int frame[], Page newPage) {
	memory.push_back(newPage);
	pageTable.push_back(newPage);
	Stack.push_back(newPage);
	frame[newPage.pid]++;
}

void setMemory(Page replace, Page page) {
	for (int i = 0; i < memory.size(); i++) {
		if (memory[i].pid == replace.pid && memory[i].pageNumber == replace.pageNumber) {
			memory[i].pageNumber = page.pageNumber;
			return;
		}
	}
}

void setPageTable(vector<Page> &pageTable, Page replace, Page page) {
	for (int i = 0; i < pageTable.size(); i++) {
		if (pageTable[i].pid == replace.pid && pageTable[i].pageNumber == replace.pageNumber) {
			pageTable[i].pageNumber = page.pageNumber;
			return;
		}
	}
}

void printMemory(ofstream &out) {
	for (int i = 0; i < memory.size(); i++) {
		out << i << ' ' << memory[i].pid << ' ' << memory[i].pageNumber << '\n';
	}
}

void fifoReplacement(vector<Page> &Stack, vector<Page> &pageTable, Page page) {
	Page replace;
	for (int i = 0; i < Stack.size(); i++) {
		if (Stack[i].pid == page.pid) {
			replace = Stack[i];
			Stack.erase(Stack.begin() + i);
			Stack.push_back(page);
			break;
		}
	}
	setMemory(replace, page);
	setPageTable(pageTable, replace, page);
}

void FIFO(ofstream &out) {
	int pageFault = 0;
	int frame[MAX] = { 0 };
	vector<Page> Stack;
	vector<Page> pageTable;
	for (int i = 0; i < input.size(); i++) {
		if (!hasPage(pageTable, input[i])) {
			if (isFull(frame, input[i].pid)) {
				fifoReplacement(Stack, pageTable, input[i]);
			}
			else {
				pushPage(pageTable, Stack, frame, input[i]);
			}
			pageFault++;
		}
	}
	out << "FIFO: " << pageFault << '\n';
	printMemory(out);
	memory.clear();
}

void lruStackRenewal(vector<Page> &Stack, Page page) {
	for (int i = 0; i < Stack.size(); i++) {
		if (Stack[i].pid == page.pid && Stack[i].pageNumber == page.pageNumber) {
			Stack.erase(Stack.begin() + i);
			Stack.push_back(page);
			return;
		}
	}
	Stack.push_back(page);
}

void lruReplacement(vector<Page> &Stack, vector<Page> &pageTable, Page page) {
	Page replace;
	for (int i = 0; i < Stack.size(); i++) {
		if (Stack[i].pid == page.pid) {
			replace = Stack[i];
			Stack.erase(Stack.begin() + i);
			Stack.push_back(page);
			break;
		}
	}
	setMemory(replace, page);
	setPageTable(pageTable, replace, page);
}

void LRU(ofstream &out) {
	int pageFault = 0;
	int frame[MAX] = { 0 };
	vector<Page> Stack;
	vector<Page> pageTable;
	for (int i = 0; i < input.size(); i++) {
		if (!hasPage(pageTable, input[i])) {
			if (isFull(frame, input[i].pid)) {
				lruReplacement(Stack, pageTable, input[i]);
			}
			else {
				pushPage(pageTable, Stack, frame, input[i]);
			}
			pageFault++;
		}
		else {
			lruStackRenewal(Stack, input[i]);
		}
	}
	out << "LRU: " << pageFault << '\n';
	printMemory(out);
	memory.clear();
}

void optReplacement(vector<Page> &Stack, vector<Page> &pageTable, Page page, int front) {
	vector<Page> curPage; // 현재프로세스페이지
	for (int i = 0; i < pageTable.size(); i++) {
		if (pageTable[i].pid == page.pid) {
			curPage.push_back(pageTable[i]);
		}
	}
	vector<Heap> optimal; // 뒤에잇는거
	for (int i = 0; i < curPage.size(); i++) {
		for (int j = front; j < input.size(); j++) {
			if (curPage[i].pid == input[j].pid && curPage[i].pageNumber == input[j].pageNumber) {
				optimal.push_back({ j, input[j].pid , input[j].pageNumber });
				break;
			}
		}
	}
	if (optimal.empty()) { // 뒤에 하나도 안들어올 때 fifo
		fifoReplacement(Stack, pageTable, page);
	}
	else {
		sort(optimal.begin(), optimal.end(), compare); // 정렬
		if (optimal.size() == n) { // 모두 다 뒤에 있을 때
			Page replace;
			replace.pid = optimal[0].pid, replace.pageNumber = optimal[0].pageNumber;
			for (int i = 0; i < Stack.size(); i++) {
				if (Stack[i].pid == replace.pid && Stack[i].pageNumber == replace.pageNumber) {
					Stack.erase(Stack.begin() + i);
					Stack.push_back(page);
					break;
				}
			}
			setMemory(replace, page);
			setPageTable(pageTable, replace, page);
		}
		else {
			vector<Page> notOptimal;
			for (int i = 0; i < curPage.size(); i++) {
				bool flag = false;
				for (int j = 0; j < optimal.size(); j++) {
					if (curPage[i].pageNumber == optimal[j].pageNumber) {
						flag = true;
						break;
					}
				}
				if (!flag) {
					notOptimal.push_back({ curPage[i].pid, curPage[i].pageNumber });
				}
			}
			Page replace;
			for (int i = 0; i < Stack.size(); i++) {
				bool flag = false;
				for (int j = 0; j < notOptimal.size(); j++) {
					if (Stack[i].pid == notOptimal[j].pid && Stack[i].pageNumber == notOptimal[j].pageNumber) {
						replace = notOptimal[j];
						Stack.erase(Stack.begin() + i);
						Stack.push_back(page);
						flag = true;
						break;
					}
				}
				if (flag) break;
			}
			setMemory(replace, page);
			setPageTable(pageTable, replace, page);
		}
	}
}

void OPT(ofstream &out) {
	int pageFault = 0;
	int frame[MAX] = { 0 };
	vector<Page> pageTable;
	vector<Page> Stack;
	for (int i = 0; i < input.size(); i++) {
		if (!hasPage(pageTable, input[i])) {
			if (isFull(frame, input[i].pid)) {
				optReplacement(Stack, pageTable, input[i], i + 1);
			}
			else {
				pushPage(pageTable, Stack, frame, input[i]);
			}
			pageFault++;
		}
	}
	out << "OPT: " << pageFault << '\n';
	printMemory(out);
	memory.clear();
}

int main() {
	ifstream inp("page.inp");
	ofstream out("page.out");
	inputPage(inp);
	FIFO(out);
	LRU(out);
	OPT(out);
	return 0;
}