#include<fstream>
#include<algorithm>
using namespace std;

struct Lamp {
	int start, finish;
};

Lamp lamp[100001];
int n, k;
int start, finish;

bool compare(Lamp &a, Lamp &b) {
	return a.start < b.start;
}

bool compareSearch(const Lamp &a, const Lamp &b) {
	return a.start < b.start;
}

int findLongest(int index) {
	int result = 0;
	bool flag = false;
	for (int i = 0; i < index; i++) {
		if (start < lamp[i].finish) {
			if (lamp[result].finish < lamp[i].finish) {
				result = i;
			}
			flag = true;
		}
	}
	return flag ? lamp[result].finish : -1;
}

int solution() {
	int result = 0;
	while (start < finish) {
		Lamp temp = { start, 0 };
		int index = -1;
		index = upper_bound(lamp, lamp + n, temp, compareSearch) - lamp;
		if (index == -1) {
			return -1;
		}
		start = findLongest(index);
		if (start == -1) {
			return -1;
		}
		result++;
	}
	return result;
}

int main() {
	ifstream inp("light.inp");
	ofstream out("light.out");
	inp >> n;
	for (int i = 0; i < n; i++) {
		inp >> lamp[i].start >> lamp[i].finish;
	}
	sort(lamp, lamp + n, compare);
	inp >> k;
	while (k--) {
		inp >> start >> finish;
		out << solution() << '\n';
	}
	return 0;
}