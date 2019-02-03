#include<stdio.h>
#include<math.h>
#define MAX 100
#pragma warning(disable:4996)

int Hash_Table[MAX]; // 해쉬테이블 선언

int Hash_index(int key, int N, double Real_number) { // 해쉬 index를 계산
	double cal = key * Real_number; // 인덱스 값 * 실수
	int temp = (int)cal; // 소수점 값을 계산하기 위한 임시값
	cal -= temp; //소수점 값만을 계산
	cal = floorf(cal * 100) / 100; // 소수점 2번째 자리까지 버림
	return (int)(N * cal); // index값을 계산
}

void Hashing(int key, int N, double Real_number) {
	int index = Hash_index(key, N, Real_number); // 해쉬 계산
	if (Hash_Table[index] != 0) { // 충돌이 발생했을 때
		while (1) {
			if (index == N - 1 && Hash_Table[index] != 0)
				index %= N - 1; //  N-1번 자리가 찼으면 모드를 사용해 0으로 다시 이동
			if (Hash_Table[index] == 0) { // Hash_Table에 저장
				Hash_Table[index] = key;
				return;
			}
			index++;
		}
	}
	// 충돌이 없는 경우
	Hash_Table[index] = key; // Hash_Table에 저장
}

int main() {
	FILE *inp = fopen("hw2.inp", "r");
	FILE *out = fopen("hw2.out", "w");
	if (inp == NULL) fprintf(stderr, "can't open %s\n", "hw2.inp");
	if (out == NULL) fprintf(stderr, "can't open %s\n", "hw2.out");
	int N; // 해쉬테이블의 크기
	double Real_number; // 실수값
	int key; // Hash_Table에 넣을 수
	fscanf(inp, "%d%lf", &N, &Real_number);
	while (fscanf(inp, "%d", &key))
		Hashing(key, N, Real_number); // 해쉬함수실행
	for (int i = 0; i < N; i++) {
		if (Hash_Table[i] != 0) // 0이 아닌 경우 출력
			fprintf(out, "[%d,%d]\n", i, Hash_Table[i]);
	}
	fprintf(out, "*");
	fclose(inp); fclose(out);
	return 0;
}