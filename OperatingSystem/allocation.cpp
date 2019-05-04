#include<fstream>
#include<vector>
#include<queue>
#define MAX 1001
#define INFINITY 987654321
using namespace std;

struct Process {
	int pid, startTime, cpuBurst, size;
};

struct Memory {
	int address, pid, size, endTime;
};

struct Heap {
	int index, size;
};

struct compareBest {
	bool operator()(Heap &m1, Heap &m2) {
		if (m1.size == m2.size) {
			return m1.index > m2.index;
		}
		return m1.size > m2.size;
	}
};

struct compareWorst {
	bool operator()(Heap &m1, Heap &m2) {
		if (m1.size == m2.size) {
			return m1.index > m2.index;
		}
		return m1.size < m2.size;
	}
};

int n, result;
Process process[MAX];

void input(ifstream &inp) {
	inp >> n;
	for (int i = 0; i < n; i++) {
		inp >> process[i].startTime >> process[i].cpuBurst >> process[i].size;
		process[i].pid = i;
	}
}

bool canAllocate(Memory &memory, Process &process) {
	return memory.size >= process.size;
}

bool allocateProcess(vector<Memory> &memory, Process &process, int index, int time) {
	if (process.pid == n - 1) {
		result = memory[index].address;
		return true;
	}

	memory[index].pid = process.pid;
	memory[index].endTime = time + process.cpuBurst;

	if (memory[index].size > process.size) {
		Memory newMemory = { memory[index].address + process.size, -1, memory[index].size - process.size, INFINITY };
		memory[index].size = process.size;
		memory.insert(memory.begin() + index + 1, newMemory);
	}
	return false;
}

bool releaseMemory(vector<Memory> &memory, int time) {
	/*시작 삭제 -1*//*시작 삭제 요소*//*요소 삭제 요소*//*-1 삭제 요소*//*요소 삭제 -1*//*-1 삭제 -1*//*-1 삭제 끝*//*요소 삭제 끝*/
	bool flag = false;
	for (int i = 0; i < memory.size(); i++) {
		if (time == memory[i].endTime) {
			memory[i].pid = -1;
			memory[i].endTime = INFINITY;
			flag = true;
		}
	}
	for (int i = 0; i < memory.size() - 1; i++) {
		if (memory[i].pid == memory[i + 1].pid) {
			memory[i].size += memory[i + 1].size;
			memory.erase(memory.begin() + i + 1);
			i--;
		}
	}
	return flag;
}

bool allocateFirstReadyQueue(vector<Memory> &memory, vector<Process> &readyQueue, int time) {
	for (int i = 0; i < memory.size(); i++) {
		if (memory[i].pid == -1) {
			for (int j = 0; j < readyQueue.size(); j++) {
				if (canAllocate(memory[i], readyQueue[j])) {
					if (allocateProcess(memory, readyQueue[j], i, time)) {
						return true;
					}
					readyQueue.erase(readyQueue.begin() + j--);
					break;
				}
			}
		}
	}

	return false;
}

bool allocateFirstFit(vector<Memory> &memory, vector<Process> &readyQueue, int front, int time) {
	for (int i = 0; i < memory.size(); i++) {
		if (memory[i].pid == -1) {
			if (canAllocate(memory[i], process[front])) {
				if (allocateProcess(memory, process[front], i, time)) {
					return true;
				}
				else {
					return false;
				}
			}
		}
	}
	readyQueue.push_back(process[front]);
	return false;
}

int firstFit() {
	int front = 0, time = 0;
	vector<Memory> memory;
	vector<Process> readyQueue;
	memory.push_back({ 0, -1, 1000, INFINITY });
	while (true) {
		if (releaseMemory(memory, time)) { // 반환햇다면
			if (!readyQueue.empty() && allocateFirstReadyQueue(memory, readyQueue, time)) { // 대기큐 확인
				return result;
			}
		}
		while (time == process[front].startTime) {
			if (allocateFirstFit(memory, readyQueue, front, time)) {
				return result;
			}
			front++;
		}
		time++;
	}
}

bool allocateBestReadyQueue(vector<Memory> &memory, vector<Process> &readyQueue, int time) {
	for (int i = 0; i < readyQueue.size(); i++) {
		priority_queue<Heap, vector<Heap>, compareBest> heap;
		bool flag = false;
		for (int j = 0; j < memory.size(); j++) {
			if (memory[j].pid == -1 && canAllocate(memory[j], readyQueue[i])) {
				heap.push({ j, memory[j].size });
				flag = true;
			}
		}
		if (flag) {
			if (allocateProcess(memory, readyQueue[i], heap.top().index, time)) {
				return true;
			}
			readyQueue.erase(readyQueue.begin() + i--);
		}
	}
	return false;
}

bool allocateBestFit(vector<Memory> &memory, vector<Process> &readyQueue, int front, int time) {
	priority_queue<Heap, vector<Heap>, compareBest> heap;
	bool flag = false;
	for (int i = 0; i < memory.size(); i++) {
		if (memory[i].pid == -1 && canAllocate(memory[i], process[front])) {
			heap.push({ i, memory[i].size });
			flag = true;
		}
	}
	if (flag) {
		if (allocateProcess(memory, process[front], heap.top().index, time)) {
			return true;
		}
	}
	else {
		readyQueue.push_back(process[front]);
	}
	return false;
}

int bestFit() {
	int front = 0, time = 0;
	vector<Memory> memory;
	vector<Process> readyQueue;
	memory.push_back({ 0, -1, 1000, INFINITY });
	while (true) {
		if (releaseMemory(memory, time)) { // 반환햇다면
			if (!readyQueue.empty() && allocateBestReadyQueue(memory, readyQueue, time)) { // 대기큐 확인
				return result;
			}
		}
		while (time == process[front].startTime) {
			if (allocateBestFit(memory, readyQueue, front, time)) {
				return result;
			}
			front++;
		}
		time++;
	}
}

bool allocateWorstReadyQueue(vector<Memory> &memory, vector<Process> &readyQueue, int time) {
	for (int i = 0; i < readyQueue.size(); i++) {
		priority_queue<Heap, vector<Heap>, compareWorst> heap;
		bool flag = false;
		for (int j = 0; j < memory.size(); j++) {
			if (memory[j].pid == -1 && canAllocate(memory[j], readyQueue[i])) {
				heap.push({ j, memory[j].size });
				flag = true;
			}
		}
		if (flag) {
			if (allocateProcess(memory, readyQueue[i], heap.top().index, time)) {
				return true;
			}
			readyQueue.erase(readyQueue.begin() + i--);
		}
	}
	return false;
}

bool allocateWorstFit(vector<Memory> &memory, vector<Process> &readyQueue, int front, int time) {
	priority_queue<Heap, vector<Heap>, compareWorst> heap;
	bool flag = false;
	for (int i = 0; i < memory.size(); i++) {
		if (memory[i].pid == -1 && canAllocate(memory[i], process[front])) {
			heap.push({ i, memory[i].size });
			flag = true;
		}
	}
	if (flag) {
		if (allocateProcess(memory, process[front], heap.top().index, time)) {
			return true;
		}
	}
	else {
		readyQueue.push_back(process[front]);
	}
	return false;
}

int worstFit() {
	int front = 0, time = 0;
	vector<Memory> memory;
	vector<Process> readyQueue;
	memory.push_back({ 0, -1, 1000, INFINITY });
	while (true) {
		if (releaseMemory(memory, time)) { // 반환햇다면
			if (!readyQueue.empty() && allocateWorstReadyQueue(memory, readyQueue, time)) { // 대기큐 확인
				return result;
			}
		}
		while (time == process[front].startTime) {
			if (allocateWorstFit(memory, readyQueue, front, time)) {
				return result;
			}
			front++;
		}
		time++;
	}
}

int main() {
	ifstream inp("allocation.inp");
	ofstream out("allocation.out");
	input(inp);
	out << firstFit() << '\n' << bestFit() << '\n' << worstFit();
	return 0;
}