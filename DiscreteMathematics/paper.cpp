#include<stdio.h>
#include<string.h>
#pragma warning(disable : 4996)
int row[50][50], col[50][50]; // 행, 열

int paper(int n, int m) {
	int result = 0;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < m - 1; j++) {
			result = row[i][j] + col[i][j] + row[i][j + 1] + col[i + 1][j]; // 주변 접힘 검사
			if (result % 2 == 1) // 3개 모두 다를 때
				result = 0;
			else
				return 0; // 아닐 때
		}
	}
	return 1;
}

int main() {
	FILE *inp = fopen("paper.inp", "rt");
	FILE *out = fopen("paper.out", "wt");
	int t;
	int n, m;
	fscanf(inp, "%d\n", &t);
	while (t--) {
		fscanf(inp, "%d %d\n", &n, &m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m - 1; j++)
				fscanf(inp, "%d", &col[i][j]); // 세로 입력
		for (int i = 0; i < n - 1; i++)
			for (int j = 0; j < m; j++)
				fscanf(inp, "%d", &row[i][j]); // 가로 입력
		fprintf(out, "%d ", paper(n, m));
		memset(row, 0, sizeof(row));
		memset(col, 0, sizeof(col));
	}
	return 0;
}