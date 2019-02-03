#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<string>
#define YEARS 2201
#define MONTH 13
#define WEEK 7
#define DAY 32

using namespace std;

int abs(int n) {
	if (n > 0) return n;
	return -n;
}

typedef struct Calender {
	int weekDay, exchangeDay, weekCnt; // 무슨 요일인지와 총 일 수, 몇 번째 주인지 저장
}Calender; // 달력 구조체 선언

string weekList[WEEK] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" }; // 일, 월, 화, 수, 목, 금, 토 한 주 요일 정보 저장
Calender calender[YEARS][MONTH][DAY]; // 달력 정보 저장 배열

void CreateCalender() { // 달력 생성 함수
	int totalDay = 1, weekDayCnt = 1; // 총 일 수와 한 주의 몇 번째 날인지
	for (int year = 1; year < YEARS; year++) {
		/* 매년 */
		for (int month = 1; month < MONTH; month++) {
			/* 매월 */
			int weekCnt = 1, wc = 0, minusDay = 0; // 새로운 달이 시작되면 주간 카운트를 1로 초기화, 그리고 월마다 다른 마지막 일 처리 변수 선언
			if (month < 8) {
				/* 8월 전에 적용되는 규칙 */
				if (month % 2 == 0) { // 월 수가 짝수(2,4,6)이면 31일 이하
					if (month == 2) { // 2월 달은 예외 처리
						if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) minusDay = 2; // 윤년 처리
						else minusDay = 3; // 그 외엔 28일까지
					}
					else minusDay = 1;
				}
			}
			else {
				/* 8월 이후에 적용되는 규칙 */
				if (month % 2 == 1) minusDay = 1; // 월 수가 홀수(9, 11)이면 31일 이하
			}
			for (int day = 1; day < DAY - minusDay; day++) {
				/* 매일 */
				calender[year][month][day].exchangeDay = totalDay;
				calender[year][month][day].weekDay = weekDayCnt;
				calender[year][month][day].weekCnt = weekCnt;
				totalDay++; // 총 일 수 하루 늘려줌
				weekDayCnt++; // 요일 카운트를 하나 늘려줌
				wc++;
				if (weekDayCnt % WEEK == 0) // 7일이 지나면 초기화
					weekDayCnt = 0;
				if (wc % WEEK == 0) // 그 달에 그 요일이 몇 번 있었는지 카운팅
					weekCnt++;
			}
		}
	}
}

void split(vector<string> &list, string &date) { // 문자열을 조건에 맞게 잘라냄
	while (date.find('-') != -1) {
		list.push_back(date.substr(0, date.find('-')));
		date = date.substr(date.find('-') + 1);
	}
}

int IndexingType1(string &date) { // 연도-월-일을 인덱싱하여 총 일 수를 반환
	vector<string> list;
	split(list, date);
	int y = atoi(list[0].c_str()), m = atoi(list[1].c_str()), d = atoi(date.c_str());
	return calender[y][m][d].exchangeDay;
}

int IndexingType2(string &date) { // 연도-월-횟수-요일을 인덱싱하여 총 일 수를 반환
	vector<string> list;
	split(list, date);
	int y = atoi(list[0].c_str()), m = atoi(list[1].c_str()), c = atoi(list[2].c_str());
	for (int day = 1; day < DAY && calender[y][m][day].exchangeDay != 0; day++) {
		/* 특정일 이후로 exchangeDay의 값이 0이면 그 달은 더이상 볼 필요가 없음 */
		if (calender[y][m][day].weekCnt == c && weekList[calender[y][m][day].weekDay] == date) {
			/* 몇 번째 주인지와 그 주의 요일까지 완벽하게 같으면 => 그 때의 총 일 수 반환 */
			return calender[y][m][day].exchangeDay;
		}
	}
	return -1; // 완벽하게 같은 데이터가 없으면 => 잘 못 된 입력
}

int main() {
	ifstream inp("calender.inp");
	ofstream out("calender.out");
	CreateCalender(); // 달력 생성
	while (true) {
		int type, dateResult1, dateResult2, result;
		string date1, date2;
		inp >> type;
		if (type == -1) break; // End Input
		inp >> date1 >> date2;
		/* Input Data */
		if (type > 1) dateResult1 = IndexingType2(date1);
		else dateResult1 = IndexingType1(date1);
		if (type % 2 == 1) dateResult2 = IndexingType2(date2);
		else dateResult2 = IndexingType1(date2);
		/* Calculate */
		if (dateResult1 <= 0 || dateResult2 <= 0) result = -1; // 이상한 값이 나오면
		else result = abs(dateResult1 - dateResult2);
		out << result << '\n';
		/* Output Data */
	}
	inp.close();
	out.close();
	return 0;
}