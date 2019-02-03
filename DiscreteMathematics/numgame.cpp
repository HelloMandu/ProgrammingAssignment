#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

vector<char *> bucket;

void setbucket() {
	for (char i1 = '1'; i1 <= '9'; i1++) {
		for (char i2 = '1'; i2 <= '9'; i2++) {
			if (i1 == i2) continue; // 천의자리와 백의자리가 같을 때 
			for (char i3 = '1'; i3 <= '9'; i3++) {
				if (i1 == i3 || i2 == i3) continue; // 백의자리와 십의자리가 같을 때
				for (char i4 = '1'; i4 <= '9'; i4++) {
					if (i1 == i4 || i2 == i4 || i3 == i4) continue; // 십의자리와 일의 자리가 같을 때
					char *temp = new char[5];
					temp[0] = i1; temp[1] = i2; temp[2] = i3; temp[3] = i4; temp[4] = '\0';
					bucket.push_back(temp); // 버킷에 삽입
				}
			}
		}
	}
}

int StrikeCheck(char *bucketnum, char *strike) {
	int check = 0;
	for (int i = 0; i < 4; i++) {
		if (bucketnum[i] == strike[i]) check++;
	}
	return check;
}
int BallCheck(char *bucketnum, char *ball) {
	int check = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j)
				continue; // strike일 때
			else if (bucketnum[i] == ball[j])
				check++; // ball일때
		}
	}
	return check;
}

void numgame(char *num, int strike, int ball) {
	vector<char *> newBucket;
	for (int i = 0; i < bucket.size(); i++) {
		if (StrikeCheck(bucket[i], num) == strike && BallCheck(bucket[i], num) == ball)
			newBucket.push_back(bucket[i]);
	}
	bucket.clear(); // 메모리 삭제
	bucket = newBucket;
}

int main() {
	ifstream inp("numgame.inp");
	ofstream out("numgame.out");
	int t, k;
	char *num = new char[5]; // 숫자
	int strike, ball; // 스크라이트, 볼
	inp >> t;
	while (t--) {
		inp >> k;
		setbucket(); //버킷 초기화
		while (k--) {
			inp >> num >> strike >> ball;
			numgame(num, strike, ball);
		}
		if (bucket.size() <= 6) { // 가능한 수가 6개 이하일 때
			out << bucket.size() << "\n";
			for (int i = 0; i < bucket.size(); i++)
				out << bucket[i] << "\n";
		}
		else { // 6개 이상일 떄
			out << bucket.size() << "\n";
			for (int i = 0; i < 3; i++)
				out << bucket[i] << "\n";
			for (int i = 3; i > 0; i--) {
				out << bucket[bucket.size() - i] << "\n";
			}
		}
		bucket.clear();
	}
	inp.close();
	out.close();
	return 0;
}