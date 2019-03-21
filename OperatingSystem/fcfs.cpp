#include<fstream>
#include<algorithm>
#define MAX 51
using namespace std;

struct Process {
	int num, arrivedTime, cpuSchedule;
};

Process readyQueue[MAX];
int front = 0;

bool compare(Process &a, Process &b) {
	if (a.arrivedTime == b.arrivedTime) {
		return a.num < b.num;
	}
	return a.arrivedTime < b.arrivedTime;
}

int getWaitingTime(int n) {
	int waitingTime = 0, allTime = 0;
	while (front < n) {
		if (readyQueue[front].arrivedTime > allTime) {
			allTime = readyQueue[front].arrivedTime + readyQueue[front].cpuSchedule;
		}
		else {
			allTime += readyQueue[front].cpuSchedule;
		}
		for (int present = front + 1; present < n; present++) {
			if (allTime > readyQueue[present].arrivedTime) {
				waitingTime += allTime - readyQueue[present].arrivedTime;
				readyQueue[present].arrivedTime = allTime;
			}
		}
		front++;
	}
	return waitingTime;
}

int main() {
	ifstream inp("fcfs.inp");
	ofstream out("fcfs.out");
	int n;
	inp >> n;
	for (int i = 0; i < n; i++) {
		inp >> readyQueue[i].num >> readyQueue[i].arrivedTime >> readyQueue[i].cpuSchedule;
	}
	sort(readyQueue, readyQueue + n, compare);
	out << getWaitingTime(n);
	return 0;
}