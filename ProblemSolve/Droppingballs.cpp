#include<fstream>
#include<cstring>
using namespace std;

bool tree[1048577];

int droppingBalls(int node, int depth, int height) {
	if (depth == height) {
		return node;
	}
	else if (!tree[node]) { // left
		tree[node] = !tree[node];
		return droppingBalls(node * 2, depth + 1, height);
 	}
	else { // right
		tree[node] = !tree[node];
		return droppingBalls(node * 2 + 1, depth + 1, height);
	}
}

int main() {
	ifstream inp("Droppingballs.inp");
	ofstream out("Droppingballs.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		memset(tree, false, sizeof(tree));
		int height, count, result;
		inp >> height >> count;
		for (int i = 0; i < count; i++) {
			result = droppingBalls(1, 1, height);
		}
		out << result << '\n';
	}
	return 0;
}