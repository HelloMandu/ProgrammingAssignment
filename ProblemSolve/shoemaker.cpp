#include<fstream>
#include<algorithm>
using namespace std;

struct Job {
	int id, time, fine;

	bool operator<(const Job &A) {
		int a = time * A.fine,
			b = fine * A.time;
		if (a == b) {
			return id < A.id;
		}
		return a < b;
	}
};

Job job[1001];

int main() {
	ifstream inp("shoemaker.inp");
	ofstream out("shoemaker.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		int n;
		inp >> n;
		for (int i = 0; i < n; i++) {
			inp >> job[i].time >> job[i].fine;
			job[i].id = i + 1;
		}
		sort(job, job + n);
		for (int i = 0; i < n; i++) {
			out << job[i].id << ' ';
		}
		out << '\n';
	}
	return 0;
}