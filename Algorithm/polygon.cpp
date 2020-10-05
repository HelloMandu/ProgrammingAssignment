#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

int n;
vector<int> List1, List2;

bool isSame() {
	for (int i = 0; i < n; i++) {
		if (List1[i] != List2[i]) {
			return false;
		}
	}
	return true;
}

void list2Reverse() {
	reverse(List2.begin(), List2.end());
	int next = 0, start = List2[0];
	for (int i = 0; i < n; i++) {
		next = (i + 1) % n;
		if (!next) {
			if ((start > 0 && List2[i] > 0) || (start < 0 && List2[i] < 0))
				List2[i] *= -1;
		}
		else if ((List2[next] > 0 && List2[i] > 0) || (List2[next] < 0 && List2[i] < 0)) {
			List2[i] *= -1;
		}
	}
}

int solution() {
	for(int i = 0; i < n; i++) {
		if (List1.front() == List2.front()) {
			if (isSame()) {
				return 1;
			}
		}
		List2.push_back(List2.front());
		List2.erase(List2.begin());
	}
	list2Reverse();
	for (int i = 0; i < n; i++) {
		if (List1.front() == List2.front()) {
			if (isSame()) {
				return 1;
			}
		}
		List2.push_back(List2.front());
		List2.erase(List2.begin());
	}
	return 0;
}

int main() {
	ifstream inp("polygon.inp");
	ofstream out("polygon.out");
	ios_base::sync_with_stdio(false), inp.tie(NULL), out.tie(NULL);
	int testcase;
	inp >> testcase;
	while (testcase--) {
		inp >> n;
		for (int i = 0; i < n; i++) {
			int num;
			inp >> num;
			List1.push_back(num);
		}
		for (int i = 0; i < n; i++) {
			int num;
			inp >> num;
			List2.push_back(num);
		}
		out << solution() << '\n';
		List1.clear();
		List2.clear();
	}
	return 0;
}