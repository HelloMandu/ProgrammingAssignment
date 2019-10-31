#include<fstream>
#include<algorithm>
#define INFINITY 987654321
using namespace std;

int wood[201][201][201];

void init() {
	for (int i = 1; i < 201; i++) {
		for (int j = 1; j < 201; j++) {
			for (int k = 1; k < 201; k++) {
				wood[i][j][k] = INFINITY;
			}
		}
	}
}
void sliceCube() {
	for (int w = 1; w < 201; w++) {
		for (int h = w; h < 201; h++) {
			for (int l = h; l < 201; l++) {
				if (w == h && h == l) {
					wood[w][h][l] = 1;
				}
				else if(wood[w][h][l] == INFINITY){
					for (int i = 1; i < w / 2 + 1; i++) {
						wood[w][h][l] = min(wood[w][h][l], wood[i][h][l] + wood[w - i][h][l]);
					}
					for (int i = 1; i < h / 2 + 1; i++) {
						wood[w][h][l] = min(wood[w][h][l], wood[w][i][l] + wood[w][h - i][l]);
					}
					for (int i = 1; i < l / 2 + 1; i++) {
						wood[w][h][l] = min(wood[w][h][l], wood[w][h][i] + wood[w][h][l - i]);
					}
				}
				wood[h][w][l] = wood[h][l][w] = wood[l][h][w] = wood[w][l][h] = wood[l][w][h] = wood[w][h][l];
			}
		}
	}
}

int main() {
	ifstream inp("cube2.inp");
	ofstream out("cube2.out");
	int testcase;
	inp >> testcase;
	init();
	sliceCube();
	while (testcase--) {
		int w, h, l;
		inp >> w >> h >> l;
		out << wood[w][h][l] << '\n';
	}
	inp.close(); out.close();
	return 0;
}
