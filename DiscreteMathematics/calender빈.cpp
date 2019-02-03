#include<stdio.h>
#include<math.h>

FILE *input, *output;

int cal2(int y, int m, int cnt, char date1, char date2) { //횟수와 요일이 나왔을 때 해당 달의 일자를 구하기
	int months[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	char arr[] = "SuMoTuWeThFrSa";
	int i;
	int s_date = 1; //구해야할 일자를 저장할 변수, 달의 시작 날짜는 무조건 1일부터 시작
	int start, total; // start:달의 시작요일 total: 그 달까지의 총 day값

	if (!(y % 4) && y % 100 || !(y % 400))
		months[1]++;

	total = (y - 1 + ((y - 1) / 4) - ((y - 1) / 100) + ((y - 1) / 400) + 1); // 주어진 년도까지의 총 day값 2016년이라면 2015년까지의 총 day를 구한다.
				//(y - 1) / 4:윤년 1일 더하기, (y - 1) / 100:윤년이 아님 1일 빼기, (y - 1) / 400):윤년 1일 더하기

	for (i = 0; i < m - 1; i++)
		total += months[i];

	start = total % 7; // 총 7일이므로 7로 나누게 되면 요일이 나온다 0:일요일~6:토요일
	s_date += (cnt - 1) * 7; // 횟수만큼 7을 더해준다. cnt가 1이면 더해줄 필요가 없다.

	while (arr[(start * 2) % 14] != date1 || arr[(start * 2 + 1) % 14] != date2) { // 요일이 다르다면, 2쌍씩 묶여 있기 때문에 *2해준다.
		s_date++; // 구하는 일자 증가
		start++; // 2쌍씩 묶여 있기 때문에
	}
	if (months[m - 1] < s_date) // 구한 일자가 해당 달 보다 크다면
		return -1; // -1리턴
	return s_date;
}

int cal1(int y, int m, int d) { // 해당 날짜까지의 총 일자 구하기
	int months[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int i;
	int total = 0;

	total = (y - 1) * 365 + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400;

	if (!(y % 4) && y % 100 || !(y % 400))
		months[1]++;

	for (i = 0; i < m - 1; i++)
		total += months[i];

	total += d; // day를 구한다

	return total;
}

int main() {

	input = fopen("input.inp", "r");
	output = fopen("output.out", "w");

	int t = 1;
	int y1, m1, d1, y2, m2, d2, cnt1, cnt2; // cnt는 횟수
	char date1, date2, date3, date4, date5; // date는 날짜 (date1,date2) , (date3,date4) , date5는 필요없는 값 받기
	int t_gap, gap1, gap2, gap3; // 그 날짜까지의 총 day수
	int months[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	while (1) {
		fscanf(input, "%d", &t);
		if (t == -1)
			break;
		switch (t) { //if 너무 많아서
		case 0: {
			fscanf(input, "%d-%d-%d %d-%d-%d", &y1, &m1, &d1, &y2, &m2, &d2);
			if (!(y1 % 4) && y1 % 100 || !(y1 % 400))  // 4로 나눠 떨어지고 100으로 나눠 떨어지지 않으면서 400으로 나눠 떨어진다면
				months[1]++; // 윤년 체크
			if (d1 > months[m1 - 1]) { // d1이 m1의 최대 날짜보다 크면
				fprintf(output, "-1\n");
				continue;
			}
			gap1 = cal1(y1, m1, d1); // 첫번째 날짜
			months[1] = 28; // 다시 28로 초기화 해준다
			if (!(y2 % 4) && y2 % 100 || !(y2 % 400))
				months[1]++;
			if (d2 > months[m2 - 1]) {
				fprintf(output, "-1\n");
				continue;
			}
			gap2 = cal1(y2, m2, d2); // 두번째 날짜
			t_gap = gap1 - gap2; // 두 날짜 사이의 간격
			break;
		}
		case 1: {
			fscanf(input, "%d-%d-%d %d-%d-%d-%c%c%c", &y1, &m1, &d1, &y2, &m2, &cnt2, &date3, &date4, &date5); // date5는 쓸모 없다
			if (!(y1 % 4) && y1 % 100 || !(y1 % 400))
				months[1]++;
			if (d1 > months[m1 - 1]) {
				fprintf(output, "-1\n");
				continue;
			}
			gap2 = cal2(y2, m2, cnt2, date3, date4); // day구하기
			if (gap2 == -1) { // 구한 day가 -1이라면 -1출력
				fprintf(output, "-1\n");
				continue;
			}
			t_gap = cal1(y1, m1, d1) - cal1(y2, m2, gap2);
			break;
		}
		case 2: {
			fscanf(input, "%d-%d-%d-%c%c%c %d-%d-%d", &y1, &m1, &cnt1, &date1, &date2, &date5, &y2, &m2, &d2); // date5는 쓸모 없다
			if (!(y2 % 4) && y2 % 100 || !(y2 % 400))
				months[1]++;
			if (d2 > months[m2 - 1]) {
				fprintf(output, "-1\n");
				continue;
			}
			gap1 = cal2(y1, m1, cnt1, date1, date2);
			if (gap1 == -1) {
				fprintf(output, "-1\n");
				continue;
			}
			t_gap = cal1(y1, m1, gap1) - cal1(y2, m2, d2);
			break;
		}
		case 3: {
			fscanf(input, "%d-%d-%d-%c%c%c %d-%d-%d-%c%c%c", &y1, &m1, &cnt1, &date1, &date2, &date5, &y2, &m2, &cnt2, &date3, &date4, &date5);
			gap1 = cal2(y1, m1, cnt1, date1, date2);
			gap2 = cal2(y2, m2, cnt2, date3, date4);
			if (gap1 == -1 || gap2 == -1) {
				fprintf(output, "-1\n");
				continue;
			}
			t_gap = cal1(y1, m1, gap1) - cal1(y2, m2, gap2);
			break;
		}
		}
		fprintf(output, "%d\n", abs(t_gap));
		months[1] = 28;
	}
	return 0;
}