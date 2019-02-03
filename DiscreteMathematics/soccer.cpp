#include<stdio.h>
#include<string.h>
#pragma warning(disable : 4996)

typedef struct team {
	int victory = 0; // 승점
	int GoalPoint = 0; // 골득실
	int AwayGoal = 0; // 원정득점
	int Rank = 0; // 순위
}Team;

void VictoryPoint(Team *Away, Team *Home, int GoalA, int GoalH) {
	if (GoalA < GoalH) { // 홈팀승리
		Home->victory += 3;
		Home->GoalPoint += GoalH - GoalA;
		Away->GoalPoint += GoalA - GoalH;
	}
	else if (GoalA == GoalH) { // 무승부
		Home->victory++;
		Away->victory++;
	}
	else { // 원정팀승리
		Away->victory += 3;
		Home->GoalPoint += GoalH - GoalA;
		Away->GoalPoint += GoalA - GoalH;
	}
	Away->AwayGoal += GoalA; //원정득점
}

void Rank(Team team[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (team[i].victory < team[j].victory) // 승점이 높은 팀이 있을 때
				team[i].Rank++; // 랭크++
			else if (team[i].victory > team[j].victory) // 승점이 높은 팀이 있을 때
				team[j].Rank++; // 랭크++

			if (team[i].victory == team[j].victory) {// 승점이 같은 팀이 있을 때
				if (team[i].GoalPoint != team[j].GoalPoint) { // 골득실 계산
					if (team[i].GoalPoint < team[j].GoalPoint)
						team[i].Rank++;
					else
						team[j].Rank++;
				}
				else if (team[i].AwayGoal != team[j].AwayGoal) { // 원정골계산
					if (team[i].AwayGoal < team[j].AwayGoal)
						team[i].Rank++;
					else
						team[j].Rank++;
				}
			}
		}
	}
}
int main() {
	FILE *inp = fopen("soccer.inp", "rt");
	FILE *out = fopen("soccer.out", "wt");
	Team team[40];
	int t;
	int n, k;
	int Home, Away, bar, GoalH, GoalA;
	fscanf(inp, "%d\n", &t);
	for (int i = 1; i <= t; i++) {
		fscanf(inp, "%d %d\n", &n, &k);
		for (int i = 0; i < n * (n - 1) * k; i++) {
			fscanf(inp, "%d%c%d %d %d", &Away, &bar, &Home, &GoalA, &GoalH);
			VictoryPoint(&team[Away-1], &team[Home-1], GoalA, GoalH); // 경기결과 저장
		}
		Rank(team, n); // 순위
		fprintf(out, "Test Case #%d:", i);
		for(int i = 0; i < n; i++)
			fprintf(out, " %d", team[i].Rank+1);
		fprintf(out, "\n");

		memset(team, 0, sizeof(team));
	}
	return 0;
}