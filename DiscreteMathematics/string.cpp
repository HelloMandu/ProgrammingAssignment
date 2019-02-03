#include<stdio.h>
#include<string.h>
#pragma warning(disable : 4996)

int main()
{
	FILE * inp = fopen("string.inp", "rt");
	FILE * oup = fopen("string.out", "wt");

	int test;
	char arr[10000] = { 0, };
	int i = 0;
	int ABA = 0, ABK = 0, BAB = 0, KBA = 0;

	fscanf(inp, "%d", &test);

	while (test--)
	{
		fscanf(inp, "%s", arr);
		while (arr[i] != 0)
		{
			if (arr[i] == 'A')
			{
				if (arr[i + 1] == 'B')
				{
					if (arr[i + 2] == 'A')
						ABA++;
					else if (arr[i + 2] == 'K')
						ABK++;
				}
			}
			else if (arr[i] == 'B')
			{
				if (arr[i + 1] == 'A')
				{
					if (arr[i + 2] == 'B')
						BAB++;
				}
			}
			else if (arr[i] == 'K')
			{
				if (arr[i + 1] == 'B')
				{
					if (arr[i + 2] == 'A')
						KBA++;
				}
			}
			i++;
		}
		memset(arr, 0, sizeof(arr));
		fprintf(oup, "%d %d %d %d\n", ABA, ABK, BAB, KBA);
		ABA = 0, ABK = 0, BAB = 0, KBA = 0;
		i = 0;
	}
	return 0;
}