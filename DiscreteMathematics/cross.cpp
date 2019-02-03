#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)
int arr1[10001];
int arr2[10001];
int main() {
	FILE *inp = fopen("cross.inp", "rt");
	FILE *oup = fopen("cross.out", "wt");

	int test, n, input;
	int result = 0;
	fscanf(inp, "%d\n", &test);
	for (int t = 1; t <= test; t++) {
		fscanf(inp, "%d\n", &n);
		for (int i = 1; i <= n; i++) {
			fscanf(inp, "%d", &input);
			arr1[input] = i; // 교차점의 위치를 arr1[index]값에 저장
		}
		for (int i = 1; i <= n; i++) {
			fscanf(inp, "%d", &input);
			arr2[input] = i; // 교차점의 위치를 arr2[index]값에 저장
		}
		for (int i = 1; i < n; i++) {
			for (int j = i + 1; j <= n; j++) {
				if ((arr1[i] < arr1[j] && arr2[i] > arr2[j]) || (arr1[i] > arr1[j] && arr2[i] < arr2[j])) // 교차되는 경우
					result++;
			}
		}
		fprintf(oup, "Case %d: %d\n", t, result);
		result = 0;
		memset(arr1, 0, sizeof(arr1));
		memset(arr2, 0, sizeof(arr2));
	}
	return 0;
}