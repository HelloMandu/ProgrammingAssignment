#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#pragma warning(disable :4996)


int N(int num) {
	return num;
}

int Log(int num) {
	return log(num) / log(2);
}

int Nlogn(int num) {
	return num * Log(num);
}

int Two_2(int num) {
	return pow(2, num);
}

int Nfac(int num) {
	if (num <= 1)
		return 1;
	return num * Nfac(num - 1);
}

int main() {
	int num = 5;
	float *big_o;
	FILE *input_fp = fopen("hw1.inp", "rt");
	FILE *output_fp = fopen("hw1.out", "wt");
	char jump;

	if ((input_fp = fopen("hw1.inp", "rt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "hw1.inp");
	}

	if ((output_fp = fopen("hw1.out", "wt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "hw1.out");
	}

	if ((big_o = (float*)malloc(sizeof(float)*num)) == NULL)
	{
		fprintf(stderr, "memory allocation error\n");
	}

	while (1)
	{
		fscanf(input_fp, "%d", &num);
		fscanf(input_fp, "%c", &jump);

		if (jump == '*') {
			fprintf(output_fp, "*");
			break;
		}

		big_o[0] = N(num);
		big_o[1] = Log(num);
		big_o[2] = Nlogn(num);
		big_o[3] = Two_2(num);
		big_o[4] = Nfac(num);
		fprintf(output_fp, "1)%d 2)%d 3)%d 4)%d 5)%d\n", (int)big_o[0], (int)big_o[1], (int)big_o[2], (int)big_o[3], (int)big_o[4]);
	}

	fclose(input_fp);
	fclose(output_fp);
	free(big_o);
	return 0;
}
