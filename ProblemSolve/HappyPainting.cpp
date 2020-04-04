#include<fstream>
#include<vector>
#include<set>
#include<cstring>
using namespace std;

/*
1 x y c
Change x’s father to y. If x = y or x is a ancestor of y, simply ignore
it. The edge between x and its old father is removed, and the new
edge should be painted with color c.
2 x y c
Paint all the edges along the path x–y with color c. If there is no
path between x and y, simply ignore it.
3 x y
Count the number of edges along the path x–y, and the total number
of colors among these edges.
*/

struct Node {
	int parent, color;
};

Node nodes[500001];
bool isVisit[500001];

bool isParent(int x, int y) {
	if (y == 0) {
		return false;
	}
	else if (x == nodes[y].parent) {
		return true;
	}
	return isParent(x, nodes[y].parent);
}

void changeParent(int x, int y, int c) {
	if (x != y && !isParent(x, y)) {
		nodes[x].parent = y;
		nodes[x].color = c;
	}
}

void getAncestor(int n, int& sameParent) {
	if (sameParent == 0 && isVisit[n] == true) {
		sameParent = n;
		return;
	}
	isVisit[n] = true;
	if (nodes[n].parent == 0) {
		return;
	}
	return getAncestor(nodes[n].parent, sameParent);
}

void paintEdges(int n, int c, int sameParent) {
	if (n == sameParent) {
		return;
	}
	nodes[n].color = c;
	paintEdges(nodes[n].parent, c, sameParent);
}

int countPath(set<int>& colors, int n, int sameParent) {
	if (n == sameParent) {
		return 0;
	}
	colors.insert(nodes[n].color);
	return countPath(colors, nodes[n].parent, sameParent) + 1;
}

void operation(ofstream &out, int n, int type, int x, int y, int c) {
	memset(isVisit, false, sizeof(isVisit));
	int edges = 0, sameParent = 0;
	getAncestor(x, sameParent); getAncestor(y, sameParent);
	switch (type) {
	case 1:
		changeParent(x, y, c);
		return;
	case 2:
		if (sameParent) {
			paintEdges(x, c, sameParent);
			paintEdges(y, c, sameParent);
		}
		return;
	case 3:
		set<int> colors;
		if (sameParent) {
			edges = countPath(colors, x, sameParent)
				+ countPath(colors, y, sameParent);
		}
		out << edges << ' ' << colors.size() << '\n';
		return;
	}
}

int main() {
	ifstream inp("HappyPainting.inp");
	ofstream out("HappyPainting.out");
	int n, m;
	inp >> n >> m;
	for (int i = 1; i <= n; i++) {
		inp >> nodes[i].parent;
	}
	for (int i = 1; i <= n; i++) {
		inp >> nodes[i].color;
	}
	while (m--) {
		int type, x, y, c = 0;
		inp >> type;
		inp >> x >> y;
		if (type != 3) {
			inp >> c;
		}
		operation(out, n, type, x, y, c);
	}
	return 0;
}