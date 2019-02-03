#include<stdio.h>

int type1(int n, int m, int start, int len) {
	int a = len / m, b = len % m;
	if (b == 0) { // 나머지가 0인 경우
		a -= 1; b = m;
	}
	switch (start) {
	case 1:
		if (a % 2 == 0)
			return a * m + b; //i=n-1-b, j=a; 배열 인덱스를 통해 그 안의 수를 구하는거라 1 더해줌
		else
			return a * m + m - b + 1; //i=a, j=m-b;
	case 2:
		if (a % 2 == 0)
			return a * m + m - b + 1; //i=a, j=m-b;
		else
			return a * m + b; //i=a, j=b-1;
	case 3:
		if (a % 2 == 0)
			return (n - 1 - a)*m + m - b + 1; //i=n-1-a, j=m-b;
		else
			return (n - 1 - a)*m + b; //i=n-1-a, j=b-1;
	case 4:
		if (a % 2 == 0)
			return (n - 1 - a)*m + b; //i=n-1-a, j=b-1;
		else
			return (n - 1 - a)*m + m - b + 1; //i=n-1-a, j=m-b;
	}
}

int type2(int n, int m, int start, int len) {
	int a = len / n, b = len % n;
	if (b == 0) { // 나머지가 0인 경우
		a -= 1; b = n;
	}
	switch (start) {
	case 1:
		if (a % 2 == 0)
			return (b - 1)*m + a + 1; //i=b-1, j=a; (n - 1 - b)*m + a + 1; 배열 인덱스를 통해 그 안의 수를 구하는거라 1 더해줌
		else
			return (n - b)*m + a + 1; //i=n-b, j=a;
	case 2:
		if (a % 2 == 0)
			return (b - 1)*m + m - a; //i=b-1,j=m-1-a;
		else
			return (n - b)*m + m - a; //i=n-b, j=m-1-a;
	case 3:
		if (a % 2 == 0)
			return (n - b)*m + m - a; //i=n-b, j=m-1-a;
		else
			return (b - 1)*m + m - a; //i=b-1, j=m-1-a;
	case 4:
		if (a % 2 == 0)
			return (n - b)*m + a + 1; //i=n-b, j=a;
		else
			return (b - 1)*m + a + 1; //i=b-1, j=a;
	}
}

int main() {
	FILE *inp = fopen("grid1.inp", "r");
	FILE *out = fopen("grid1.out", "w");

	int test;
	fscanf(inp, "%d", &test);

	int n, m, type, start, len;
	int result;

	while (test--) {
		fscanf(inp, "%d %d %d %d %d", &n, &m, &type, &start, &len);
		if (type == 1)
			result = type1(n, m, start, len);
		else
			result = type2(n, m, start, len);
		fprintf(out, "%d\n", result);
	}
	return 0;
}
