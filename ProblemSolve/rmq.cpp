#include<fstream>
#include<cmath>
#include<cstdlib>
#define MID(start, end) ((start + end) / 2)
using namespace std;

int arr[1000001];
int *tree;

int init(int node, int start, int end) {
	if (start == end) {
		return tree[node] = start;
	}
	int mid = MID(start, end);
	int a = init(node * 2, start, mid),
		b = init(node * 2 + 1, mid + 1, end);
	return tree[node] = arr[a] <= arr[b] ? a : b;
}

int query(int node, int start, int end, int left, int right) {
	if (left > end || right < start) {
		return -1;
	}
	else if (left <= start && end <= right) {
		return tree[node];
	}
	int mid = MID(start, end),
		a = query(node * 2, start, mid, left, right),
		b = query(node * 2 + 1, mid + 1, end, left, right);
	if (a == -1) {
		return b;
	}
	else if (b == -1) {
		return a;
	}
	return arr[a] <= arr[b] ? a : b;
}

void update(int node, int start, int end, int index) {
	if (start == end && start == index) { 
		return;
	}
	else if (start <= index && index <= end) {
		int mid = MID(start, end);
		update(2 * node, start, mid, index);
		update(2 * node + 1, mid + 1, end, index);
		tree[node] = arr[tree[2 * node]] <= arr[tree[2 * node + 1]] ? tree[2 * node] : tree[2 * node + 1];
	}
}

int main() {
	ifstream inp("rmq.inp");
	ofstream out("rmq.out");
	ios_base::sync_with_stdio(0); inp.tie(0); out.tie(0);
	int n;
	inp >> n;
	for (int i = 0; i < n; i++) {
		inp >> arr[i];
	}
	int height = (int)ceil(log2(n));
	tree = (int*)malloc(sizeof(int) * (2 << (height + 1)));
	init(1, 0, n - 1);
	char type; int a, b; long long result = 0;
	while (inp >> type >> a >> b) {
		if (type == 's') {
			out << result % 100000;
			return 0;
		}
		else if (type == 'q') {
			result += query(1, 0, n - 1, a, b);
		}
		else {
			arr[a] = b;
			update(1, 0, n - 1, a);
		}
	}
	free(tree);
}