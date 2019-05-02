#include<fstream>
#include<string>
#include<vector>
#define MAX 51
using namespace std;

ifstream inp("banker.inp");
ofstream out("banker.out");

struct Request {
	int commandIndex;
	int *request;
};

int n, m;
int commandIndex;
int resource[MAX];
int maxAllo[MAX][MAX];
int allocation[MAX][MAX];
int need[MAX][MAX];
int available[MAX];
int request[MAX];
int release[MAX];
vector<Request> Queue;

void setBankers() {
	inp >> n >> m;
	for (int i = 0; i < m; i++) {
		inp >> resource[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			inp >> maxAllo[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			inp >> allocation[i][j];
		}
	}
	for (int i = 0; i < m; i++) {
		int sum = 0;
		for (int j = 0; j < n; j++) {
			sum += allocation[j][i];
		}
		available[i] = resource[i] - sum;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			need[i][j] = maxAllo[i][j] - allocation[i][j];
		}
	}
}

void input(int arr[]) {
	inp >> commandIndex;
	for (int i = 0; i < m; i++) {
		inp >> arr[i];
	}
}

void printAvailable() {
	for (int i = 0; i < m; i++) {
		out << available[i] << ' ';
	}
	out << '\n';
}

void push(int commandIndex, int request[]) {
	int *trequest = new int[m];
	for (int i = 0; i < m; i++) {
		trequest[i] = request[i];
	}
	Queue.push_back({ commandIndex, trequest });
}

bool isSafe(int need[], int available[]) {
	for (int i = 0; i < m; i++) {
		if (need[i] > available[i]) {
			return false;
		}
	}
	return true;
}

bool canRequest(int commandIndex) {
	int tavailable[MAX];
	int tallocation[MAX][MAX];
	int tneed[MAX][MAX];
	for (int i = 0; i < m; i++) {
		tavailable[i] = available[i] - request[i];
		tallocation[commandIndex][i] = allocation[commandIndex][i] + request[i];
		tneed[commandIndex][i] = need[commandIndex][i] - request[i];
		if (tavailable[i] < 0 || maxAllo[commandIndex][i] < tallocation[commandIndex][i] || tneed[commandIndex][i] < 0) {
			return false;
		}
	}
	bool flag = false;
	for (int i = 0; i < n; i++) {
		if (i != commandIndex) {
			if (isSafe(need[i], tavailable)) {
				flag = true;
			}
		}
		else if (isSafe(tneed[i], tavailable)){
			flag = true;
		}
	}
	return flag;
}

bool canRequestQueue(Request *Queue) {
	int tavailable[MAX];
	int tallocation[MAX][MAX];
	int tneed[MAX][MAX];
	for (int i = 0; i < m; i++) {
		tavailable[i] = available[i] - Queue->request[i];
		tallocation[Queue->commandIndex][i] = allocation[Queue->commandIndex][i] + Queue->request[i];
		tneed[Queue->commandIndex][i] = need[Queue->commandIndex][i] - Queue->request[i];
		if (tavailable[i] < 0 || maxAllo[Queue->commandIndex][i] < tallocation[Queue->commandIndex][i] || tneed[Queue->commandIndex][i] < 0) {
			return false;
		}
	}
	bool flag = false;
	for (int i = 0; i < n; i++) {
		if (i != Queue->commandIndex) {
			if (isSafe(need[i], tavailable)) {
				flag = true;
			}
		}
		else if (isSafe(tneed[i], tavailable)) {
			flag = true;
		}
	}
	return flag;
}

void computeRequest() {
	if (canRequest(commandIndex)) {
		for (int i = 0; i < m; i++) {
			available[i] -= request[i];
			need[commandIndex][i] -= request[i];
			allocation[commandIndex][i] += request[i];
		}
	}
	else {
		push(commandIndex, request);
	}
	printAvailable();
}

void computeRelease() {
	for (int i = 0; i < m; i++) {
		available[i] += release[i];
		need[commandIndex][i] += release[i];
		allocation[commandIndex][i] -= release[i];
	}

	for (int it = 0; it < Queue.size(); it++) {
		if (canRequestQueue(&Queue[it])) {
			for (int i = 0; i < m; i++) {
				available[i] -= Queue[it].request[i];
				need[Queue[it].commandIndex][i] -= Queue[it].request[i];
				allocation[Queue[it].commandIndex][i] += Queue[it].request[i];
			}
			delete[] Queue[it].request;
			Queue.erase(Queue.begin() + it, Queue.begin() + it + 1);
			it = -1;
		}
	}
	printAvailable();
}

int main() {
	setBankers();
	string command;
	while (inp >> command) {
		if (command != "quit") {
			if (command == "request") {
				input(request);
				computeRequest();
			}
			else {
				input(release);
				computeRelease();
			}
		}
		else {
			return 0;
		}
	}
}