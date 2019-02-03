#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

char arr[6];
char A[7] = "000000";
char B[7] = "001111";
char C[7] = "010011";
char D[7] = "011100";
char E[7] = "100110";
char F[7] = "101001";
char G[7] = "110101";
char H[7] = "111010";
int a, b, c, d, e, f, g, h;
void answer(FILE *oup) {
	for (int i = 0; i < 6; i++) {
		if (arr[i] != A[i]) a++;
		if (arr[i] != B[i]) b++;
		if (arr[i] != C[i]) c++;
		if (arr[i] != D[i]) d++;
		if (arr[i] != E[i]) e++;
		if (arr[i] != F[i]) f++;
		if (arr[i] != G[i]) g++;
		if (arr[i] != H[i]) h++;
	}
	if (a < 2) fprintf(oup, "A");
	else if (b < 2) fprintf(oup, "B");
	else if (c < 2) fprintf(oup, "C");
	else if (d < 2) fprintf(oup, "D");
	else if (e < 2) fprintf(oup, "E");
	else if (f < 2) fprintf(oup, "F");
	else if (g < 2) fprintf(oup, "G");
	else if (h < 2) fprintf(oup, "H");
	else fprintf(oup, "X");

	a = 0; b = 0; c = 0; d = 0; e = 0; f = 0; g = 0; h = 0;
}
int main() {
	FILE *inp = fopen("mail.inp", "rt");
	FILE *oup = fopen("mail.out", "wt");

	int t, n;
	fscanf(inp, "%d", &t);
	while (t--) {
		fscanf(inp, "%d\n", &n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 6; j++)
				fscanf(inp, "%c", &arr[j]);
			answer(oup);
			memset(arr, 0, sizeof(arr));
		}
		fprintf(oup, "\n");
	}
	return 0;
}