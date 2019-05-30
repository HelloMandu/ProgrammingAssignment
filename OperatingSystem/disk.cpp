#include<fstream>
#include<string>
#include<vector>
#define RIGHT 0
#define LEFT 1
using namespace std;

struct Request {
	int time, head;
};

vector<Request> request;
string type;
int transmissionTime;

void input(ifstream &inp) {
	inp >> type >> transmissionTime;
	while (true) {
		int time, head;
		inp >> time >> head;
		if (time == -1 && head == -1) {
			return;
		}
		request.push_back({ time, head });
	}
}

void push(vector<Request> &Queue, int &front, int time) {
	while (front < request.size() && request[front].time <= time) {
		Queue.push_back(request[front++]);
	}
}

inline int getDistance(int a, int b) {
	return abs(a - b);
}

void fcfs(ofstream &out) {
	int time = 0, header = 0, front = 0;
	vector<Request> Queue;
	while (front < request.size()) {
		if (Queue.empty()) {
			time = request[front].time;
			push(Queue, front, time);
		}
		while (!Queue.empty()) {
			Request now = Queue.front(); Queue.erase(Queue.begin());
			time += getDistance(header, now.head) + transmissionTime;
			header = now.head;
			push(Queue, front, time);
		}
	}
	out << time << ' ' << header;
}

Request findNearRequest(vector<Request> &Queue, int header) {
	int nearIndex = 0;
	for (int i = 0; i < Queue.size(); i++) {
		if (getDistance(Queue[nearIndex].head, header) > getDistance(Queue[i].head, header)) {
			nearIndex = i;
		}
	}
	Request ret = Queue[nearIndex]; Queue.erase(Queue.begin() + nearIndex);
	return ret;
}

void sstf(ofstream &out) {
	int time = 0, header = 0, front = 0;
	vector<Request> Queue;
	while (front < request.size()) {
		if (Queue.empty()) {
			time = request[front].time;
			push(Queue, front, time);
		}
		while (!Queue.empty()) {
			Request now = findNearRequest(Queue, header);
			time += getDistance(header, now.head) + transmissionTime;
			header = now.head;
			push(Queue, front, time);
		}
	}
	out << time << ' ' << header;
}

int checkDirection(vector<Request> &Queue, int header, int &direction) {
	if (direction == RIGHT) {
		for (int i = 0; i < Queue.size(); i++) {
			if (Queue[i].head >= header) {
				return RIGHT;
			}
		}
	}
	else {
		for (int i = 0; i < Queue.size(); i++) {
			if (Queue[i].head <= header) {
				return LEFT;
			}
		}
	}
	return direction == RIGHT ? LEFT : RIGHT;
}

Request findLookRequest(vector<Request> &Queue, int header, int &direction) {
	int nearIndex = 0;
	direction = checkDirection(Queue, header, direction);
	if (direction == RIGHT) {
		for (int i = 0; i < Queue.size(); i++) {
			if (Queue[i].head >= header) {
				if (getDistance(Queue[nearIndex].head, header) > getDistance(Queue[i].head, header)) {
					nearIndex = i;
				}

			}
		}
	}
	else {
		for (int i = 0; i < Queue.size(); i++) {
			if (Queue[i].head <= header) {
				if (getDistance(Queue[nearIndex].head, header) > getDistance(Queue[i].head, header)) {
					nearIndex = i;
				}
			}
		}
	}
	Request ret = Queue[nearIndex]; Queue.erase(Queue.begin() + nearIndex);
	return ret;
}

void look(ofstream &out) {
	int time = 0, header = 0, front = 0, direction = RIGHT;
	vector<Request> Queue;
	while (front < request.size()) {
		if (Queue.empty()) {
			time = request[front].time;
			push(Queue, front, time);
		}
		while (!Queue.empty()) {
			Request now = findLookRequest(Queue, header, direction);
			time += getDistance(header, now.head) + transmissionTime;
			header = now.head;
			push(Queue, front, time);
		}
	}
	out << time << ' ' << header;
}

int main() {
	ifstream inp("disk.inp");
	ofstream out("disk.out");
	input(inp);
	if (type == "FCFS") { fcfs(out); }
	else if (type == "SSTF") { sstf(out); }
	else { look(out); }
	return 0;
}