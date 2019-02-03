#include<stdio.h>
#pragma warning(disable : 4996)

int dice[10000][6];

int setceiling(int floor, int row) { // 바닥설정
	int i;
	for (i = 0; i < 6; i++) { // 바닥이 어디있는지 찾는다
		if (floor == dice[row][i]) {
			break;
		}
	}
	switch (i) { // 바닥여부
	case 0:
		return dice[row][5];
	case 1:
		return dice[row][3];
	case 2:
		return dice[row][4];
	case 3:
		return dice[row][1];
	case 4:
		return dice[row][2];
	case 5:
		return dice[row][0];
	}
}

int sum(int t, int surface) { // dice배열
	int max = 0, result = 0; // 최댓값, 결과값
	int ceiling, floor; // 천장, 바닥
	int i = 0, j = 0;
	floor = dice[0][surface]; // 초기바닥설정
	ceiling = setceiling(floor, i); // 초기천장설정
	for (i = 0; i < t; i++) {
		for (j = 0; j < 6; j++) {
			if (dice[i][j] != ceiling && dice[i][j] != floor) { // 천장과 바닥이 아닐 때
				if (max < dice[i][j]) // 최댓값 설정
					max = dice[i][j];
			}
		}
		result += max; // 결과값 설정
		floor = ceiling; // 바닥설정
		ceiling = setceiling(floor, i+1); // 천장설정
		max = 0;
	}
	return result;
}

int max(int result[]) {
	int max = 0;
	for (int i = 0; i < 6; i++) {
		if (max < result[i])
			max = result[i];
	}
	return max;
}

int main() {
	FILE *inp = fopen("dice.inp", "rt");
	FILE *out = fopen("dice.out", "wt");
	int t;
	int result[6]; // 결과6개저장
	fscanf(inp, "%d\n", &t);
	for (int i = 0; i < t; i++) {
		fscanf(inp, "%d %d %d %d %d %d\n",
		&dice[i][0], &dice[i][1], &dice[i][2], &dice[i][3], &dice[i][4], &dice[i][5]);
	}
	for (int i = 0; i < 6; i++)
		result[i] = sum(t, i); // 결과 6개 저장
	
	fprintf(out, "%d", max(result)); // 6개중 가장 큰 수 출력

	return 0;
}