#include<fstream>
#include<string>
#define surface 6
using namespace std;

int dice[surface];

typedef struct Pose {
	int top; // 윗면
	int front; // 앞면
}Pose;//자세

typedef struct Position {
	int x = 0; // x좌표
	int y = 0; // y좌표
}Position;//위치

Pose Dice_index(int top, int front) { // 주사위 top, front의 index를 반환
	Pose temp;
	for (int i = 0; i < surface; i++) {
		if (dice[i] == top)
			temp.top = i;
		else if (dice[i] == front)
			temp.front = i;
	}
	return temp;
}

int Face_to_face(int n){ // 반대편에 있는 수를 반환
	switch (n) {
	case 0: return 2;// 0 - 2
	case 1: return 4;// 1 - 4
	case 3: return 5;// 3 - 5
	case 2: return 0;// 3 - 0
	case 4: return 1;// 4 - 1
	case 5: return 3;// 5 - 2
	}
}

int Set_RightorLeft(int top, int front) { // 우측 값 또는 좌측 값 return
		if (top == 0 && front == 1 || top == 1 && front == 2 || top == 2 && front == 4 || top == 4 && front == 0) 
			return 3;
		else if (top == 0 && front == 5 || top == 5 && front == 2 || top == 2 && front == 3 || top == 3 && front == 0) 
			return 1;
		else if (top == 0 && front == 3 || top == 3 && front == 2 || top == 2 && front == 5 || top == 5 && front == 0) 
			return 4;
		else if (top == 1 && front == 5 || top == 5 && front == 4 || top == 4 && front == 3 || top == 3 && front == 1) 
			return 2;
		else if (top == 1 && front == 3 || top == 3 && front == 4 || top == 4 && front == 5 || top == 5 && front == 1) 
			return 0;
		else
			return 5;
}

void N_Update(Pose *pose) { // 북
	int temp = pose->top;
	pose->top = pose->front;
	pose->front = Face_to_face(temp);
}
void W_Update(Pose *pose) { // 서
	int right = Set_RightorLeft(pose->top, pose->front);
	pose->top = right;
}
void S_Update(Pose *pose) { // 남
	int temp = pose->top;
	pose->top = Face_to_face(pose->front);
	pose->front = temp;
}
void E_Update(Pose *pose) { // 동
	int left = Set_RightorLeft(pose->front, pose->top);
	pose->top = left;
}

void Dice_Update(Pose *pose, Position *position, char direction) { // 다이스 정보를 update
	switch (direction) {
	case 'N':
		position->y++;
		N_Update(pose);
		return;
	case 'W':
		position->x--;
		W_Update(pose);
		return;
	case 'S':
		position->y--;
		S_Update(pose);
		return;
	case 'E':
		position->x++;
		E_Update(pose);
		return;
	}
}

int main() {
	ifstream inp("die.inp");
	ofstream out("die.out");
	int t, n; // 총 테스트 케이스, 
	inp >> t;
	while (t--) {
		Position position; Pose pose; // 위치정보, 자세정보
		string direct; // 방향정보
		int top, front;
		for (int i = 0; i < surface; i++)
			inp >> dice[i]; // dice의 정보를 입력
		inp >> top >> front >> n >>direct; // top, front, 반복 수, 문자열
		pose = Dice_index(top, front);
		for(int i = 0; i < n; i++)
			Dice_Update(&pose, &position, direct[i]); // 한 칸씩 이동
		out << position.x << ' ' << position.y << ' ' << dice[pose.top] << ' ' << dice[pose.front] << '\n';
	}
	return 0;
}