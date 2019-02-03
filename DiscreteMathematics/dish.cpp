#include<stdio.h>
#include<string.h>
#pragma warning(disable : 4996)

char arr[1000];
int main()
{
	FILE *inp = fopen("dish.inp", "rt");
	FILE *out = fopen("dish.out", "wt");

	int t;
	int n; 
	int i;
	int length = 10;

	fscanf(inp, "%d", &t);

	while (t--)
	{
		fscanf(inp,"%d", &n);
		fscanf(inp, "%s", arr);
		for (i = 1; i < n; i++)
		{
			if (arr[i] == arr[i-1])
				length += 5;
			else if (arr[i] != arr[i-1])
				length += 10;
		}
		fprintf(out, "%d\n", length);
		memset(arr, 0, sizeof(arr)); //arr배열 0으로 초기화
		length = 10;//length 10으로 초기화
		i = 1;
	}

	return 0;
}