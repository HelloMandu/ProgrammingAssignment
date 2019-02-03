#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

void IntervalSort(int shell[], int begin, int end, int interval) {
	int i, j, item;
	for (i = begin + interval; i <= end; i += interval) {
		item = shell[i];
		for (j = i - interval; j >= begin && item < shell[j]; j -= interval)
			shell[j + interval] = shell[j];
		shell[j + interval] = item;
	}
}

void ShellSort(int shell[], int size, FILE *out) {
	int interval = size / 2;
	while (interval >= 1) {
		for (int i = 0; i < interval; i++)
			IntervalSort(shell, i, size - 1, interval);
		for (int t = 0; t < size; t++)
			fprintf(out, "%d ", shell[t]);
		fprintf(out, "\n");
		interval /= 2;
	}
}

void MergeTwoSort(int arr1[], int arr2[], int arr3[], int size1, int size2, FILE *out) { //2원 합병
	int idx1 = 0, idx2 = 0, idx3 = 0;
	while (idx1 <= size1 && idx2 <= size2) {
		if (arr1[idx1] <= arr2[idx2]) // arr1이 더 크거나, 같을때
			arr3[idx3++] = arr1[idx1++];
		else // arr2이 더 클때
			arr3[idx3++] = arr2[idx2++];
	}
	idx3--; // 증가된 idx3를 -1

	if (idx1 > size1) { // arr1이 남앗을 때
		for (int i = idx2; i < size2; i++)
			arr3[idx3++] = arr2[idx2++];
	}
	else { // arr2이 남앗을 때
		for (int i = idx1; i < size1; i++)
			arr3[idx3++] = arr1[idx1++];
	}

	for (int i = 0; i < idx3; i++)
		fprintf(out, "%d ", arr3[i]);
	fprintf(out, "\n*");
}

int main() {
	FILE *inp = fopen("hw1.inp", "r");
	FILE *out = fopen("hw1.out", "w");
	if ((inp = fopen("hw1.inp", "rt")) == NULL) fprintf(stderr, "can't open %s\n", "hw1.inp");
	if ((out = fopen("hw1.out", "wt")) == NULL) fprintf(stderr, "can't open %s\n", "hw1.out");

	char star = 0;
	int arr1[1000], arr2[1000], arr3[1000];
	int size1 = 0, size2 = 0;

	for (int i = 0; star != '\n'; i++, size1++) // 첫번째 배열
		fscanf(inp, "%d%c", &arr1[i], &star);

	ShellSort(arr1, size1, out);
	star = 0;

	for (int i = 0; star != '\n'; i++, size2++) // 두번째 배열
		fscanf(inp, "%d%c", &arr2[i], &star);

	ShellSort(arr2, size2, out);

	MergeTwoSort(arr1, arr2, arr3, size1, size2, out); // 2원 합병

	fclose(inp); fclose(out);
	return 0;
}