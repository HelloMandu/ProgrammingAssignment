#include<fstream>
#include<string>
using namespace std;

bool Check_Question_mark(string good, char Qidx) { // ?조건에 맞는 경우
	for (int i = 0; i < good.length(); i++) {
		if (good[i] == Qidx) // 조건에 맞는 알파벳이 있을시
			return true;
	}
	return false;
}

bool Check_Star_mark(string good, string Q, int index, int starlength) {// *조건에 맞는 경우 거꾸로 계산
	int check = 0; // 조건확인
	for (int i = 0; i < good.length(); i++) {
		for (int j = index; j < index + starlength; j++) {
			if (good[i] == Q[j]) // good에 있는 문자인지 체크
				check++;
		}
	}
	if (check < starlength) // 하나이상이 좋은 문자가 아닐 때
		return true;
	else
		return false;
}

bool Question(string good, string P, string Q) {
	for (int i = 0; i < P.length(); i++) {
		if (P[i] == '?') { // ?인 경우
			if (!Check_Question_mark(good, Q[i])) // ?를 봣을 때 틀린 경우
				return false;
		}
		else if (P[i] == '*') { // *인경우 거꾸로 계산
			int starlength = (Q.length() - P.length()) + 1; // *문자열의 길이
			if (!Check_Star_mark(good, Q, i, starlength) && starlength != 0) // ?를 봣을 때 틀린 경우
				return false;
			if (starlength != 0)
				Q.erase(i, starlength - 1); // *부분의 문자열을 지운다 하나의 index만 남겨두고 지운다
			else
				Q.insert(i, "*");
		}
		else if (P[i] != Q[i]) // 비교가능한 두 문자가 다를 때
			return false;
	}
	return true; // *이없고 ?와 문자의 경우가 맞는 경우
}

int main() {
	ifstream inp("exam.inp");
	ofstream out("exam.out");
	int testcase, query;
	string good, P, Q;
	inp >> testcase;
	for (int i = 1; i <= testcase; i++) {
		inp >> good; // 좋은문자
		inp >> P; // ?, * 포함한 문자열
		inp >> query; // 질의어 수
		out << "Test Case: #" << i << endl;
		while (query--) {
			inp >> Q; // 질의어
			if (Question(good, P, Q))
				out << "Yes" << endl;
			else
				out << "No" << endl;
		}
	}
	inp.close();
	out.close();
	return 0;
}