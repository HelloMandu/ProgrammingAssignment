#include<fstream>
#include<vector>
#include<algorithm>
#define Year 372
#define Month 31
#define Start true
#define End false
using namespace std;

typedef struct Date {
	bool type; // start : true, end : false
	int year; // 년
	int month; // 월
	int day; // 일
}Date;

int Allday(Date time) { // 사건의 시작, 끝의 총 일수를 반환함
	return time.year * Year + time.month * Month + time.day;
}

bool compare(Date &event1, Date &event2) { // sort 비교함수
	int Event1 = Allday(event1), Event2 = Allday(event2);
	if (Event1 == Event2) // 날짜가 같을 때 end가 start보다 앞에오도록
		return event1.type < event2.type;
	else
		return Event1 < Event2;
}

int timeline(vector<Date> &event) {
	int result = 0, row = 0; // 최대 row의 수, 현재 row의 수
	for (int i = 0; i < event.size(); i++) {
		row = (event[i].type == Start) ? row + 1 : row - 1; // start : +1, end : -1
		if (result < row) // 행의 갯수를 갱신
			result = row;
	}
	return result;
}

int main() {
	ifstream inp("timeline.inp");
	ofstream out("timeline.out");
	int t, n; // 총 테스트 케이스, 사건의 수
	int year, month, day;
	char dot;
	inp >> t;
	while (t--) {
		vector<Date> event; Date input;
		inp >> n; 
		event.reserve(n * 2); // start + end
		while (n--) {
			inp >> input.year >> dot >> input.month >> dot >> input.day;
			input.type = Start; event.push_back(input); // Start
			inp	>> input.year >> dot >> input.month >> dot >> input.day;
			input.type = End; event.push_back(input); // End
		}
		sort(event.begin(), event.end(), compare); // 사건들을 시작일을 기준으로 정렬
		out << timeline(event) << '\n';
	}
	return 0;
}