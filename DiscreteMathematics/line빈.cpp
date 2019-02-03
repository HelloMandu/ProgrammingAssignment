#include<stdio.h>
#include<math.h>
#pragma warning(disable : 4996)
#define MAX(a,b) (a > b  ? a: b)
#define min(a,b) (a< b ? a:b)

typedef struct line {
	int q;
	int a;
};
line arr[100]; //m은 최대 100

int main() {

	FILE *input = fopen("line.inp", "r");
	FILE *output = fopen("line.out", "w");

	int k_max, k_min, k;
	int t, m, q, a, b;
	int i;
	int num, add;

	fscanf(input, "%d", &t);
	while (t--) {
		fscanf(input, "%d", &m);
		for (i = 0; i < m; i++)
			fscanf(input, "%d %d", &arr[i].q, &arr[i].a); //line 배열에 모두 받기
		k_max = 1000000000, k_min = 1; //q의 범위 최대 1000000000 최소 1
		for (i = 0; i < m; i++) {
			num = 1, add = 0;
			if (arr[i].a == 1) { //첫 번째 라인일 경우
				k_min = MAX(arr[i].q, k_min); //기존의 min보다 크면 min바꿈. 안 크면 min 그대로
				continue;
			}
			b = arr[i].a; //num구하기 위한 변수
			while (--b) {
				num += add++; //2번째 라인 첫 시작 번호 k+num(1), 3번째 라인 첫 시작 번호 2k+num+1, 4번째 라인 첫 시작 번호 3k+num+2, n번째 라인 첫 시작번호 (n-1)k+num+(n-2)
			}
			k = (arr[i].q - num) / (arr[i].a - 1); //q가 a줄의 제일 처음에 있을 경우, 무조건 내림하면 됨(int로 바뀌면서 알아서 내림처리)
			k_max = min(k, k_max); //기존의 숫자보다 작아야 min<k<MAX 의 MAX 바꿈
			k = ceil((arr[i].q - (num + arr[i].a - 2)) / (double)arr[i].a); //q가 a줄의 제일 끝에 있을 경우, 무조건 올림하면 됨(ceil을 통해 무조건 올림처리)
			k_min = MAX(k, k_min); //기존의 숫자보다 커야 min<k<MAX 의 min 바꿈
			if (k_min == k_max) {
				fprintf(output, "%d %d\n", i + 1, k_min); //배열은 0부터 시작하므로 i+1해주기
				break;
			}
		}
		if (k_min != k_max)
			fprintf(output, "-1\n");
	}
	return 0;
}