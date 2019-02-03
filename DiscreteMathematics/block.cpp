#include<stdio.h>
#include<math.h>
#pragma warning(disable:4996)
int arr[1000][1000];
void block(int n) {
	for (int t = 0; t < n; t++) {
		for (int i = 0; i < n-1; i++) {
			for (int j = 0; j < i + 1; j++) {
				if (arr[i + 1][j] != -1 && arr[i + 1][j + 1] != -1) // root
					arr[i][j] = (arr[i + 1][j] + arr[i + 1][j + 1]) % 100;
				else if (arr[i][j] != -1 && arr[i + 1][j] != -1) { // left
					if ((arr[i][j] - arr[i + 1][j]) >= 0)
						arr[i + 1][j + 1] = arr[i][j] - arr[i + 1][j];
					else
						arr[i + 1][j + 1] = (arr[i][j] + 100) - arr[i + 1][j];
				}
				else if (arr[i][j] != -1 && arr[i + 1][j + 1] != -1) { // right
					if((arr[i][j] - arr[i + 1][j+1]) >= 0)
						arr[i + 1][j] = arr[i][j] - arr[i + 1][j + 1];
					else
						arr[i + 1][j] = (arr[i][j]+100) - arr[i + 1][j + 1];
				}
			}
		}
	}
}
int main() {
	FILE *inp = fopen("block.inp", "rt");
	FILE *oup = fopen("block.out", "wt");
	int t, n;
	fscanf(inp, "%d", &t);
	while (t--) {
		fscanf(inp, "%d\n", &n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < i + 1; j++)
				fscanf(inp, "%d", &arr[i][j]); // 입력
		block(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < i + 1; j++) {
				fprintf(oup, "%d", arr[i][j]); // 출력
				if(i!=j)
					fprintf(oup, " ");
			}
			fprintf(oup, "\n");
		}
	}
	return 0;
}