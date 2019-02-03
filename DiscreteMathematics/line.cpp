#include<stdio.h>
#include<math.h>
#include<string.h>
#pragma warning(disable : 4996)

typedef struct Person {
	int k = 0; // 결괏값
	int max = 1000000000; // 최대
	int min = 0; // 최소
	int count = 0; // 검사한 횟수
}Person;

int sequence(int A, int n) {
	if (A == 2)
		return 1;
	else
		return n + sequence(A - 1, n + 1);
}

int setsequence(int A) {
	if (A == 1)
		return 0;
	else
		return sequence(A, 1);
}

void line(Person *person, int Q, int A) {

	if (person->k != 0)
		return;
	int k;
	double mink, maxk;
	double minNum, maxNum;

	if (A == 1) {
		minNum = 1;
		maxNum = 0;
	}
	else {
		minNum = setsequence(A); // 상수 설정
		maxNum = setsequence(A + 1) - 1;
	}
		mink = (Q - maxNum) / A; // 최소k값
		maxk = (Q - minNum) / (A - 1); // 최대k값
		mink = ceil(mink); maxk = floor(maxk); // 최솟값, 최댓값 반올림

	if (person->min < mink) // 최솟값 저장
		person->min = mink;
	if (person->max > maxk) // 최댓값 저장
		person->max = maxk;
	if (person->min == person->max)
		person->k = person->min;
	person->count++; // 연산식 계산
}

int main() {
	FILE *inp = fopen("line.inp", "rt");
	FILE *out = fopen("line.out", "wt");
	int t, m; // testcase, Question
	int Q, A; // PeopleNum, Line
	Person person;
	fscanf(inp, "%d\n", &t);
	while (t--) {
		fscanf(inp, "%d\n", &m);
		while (m--) {
			fscanf(inp, "%d %d\n", &Q, &A);
			line(&person, Q, A); // 정보 업데이트
		}
		if (person.k != 0)
			fprintf(out, "%d %d\n", person.count, person.k);
		else
			fprintf(out, "-1\n");
		memset(&person, 0, sizeof(person));
		person.max = 1000000000;
	}
	
	return 0;
}