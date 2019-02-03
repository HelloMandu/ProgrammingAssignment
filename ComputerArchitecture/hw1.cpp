#include<iostream>
#include<string>
#include<math.h>
using namespace std;
#define SIZE 8 // 8bit
#define MSB 0 // 부호비트

bool Check_Bit(char bit)  {//bit가 0이 아닐 때 false, 0일 때 true를 반환 
	return (bit - '0') ? false : true;
}

int BinarytoDecimal(string &binary_number, int size) { // 2진수를 10진수로 계산
	int result = 0;
	for (int i = 0; i < size; i++)
		result += (binary_number[SIZE - (i + 1)] - '0') * (int)pow(2, i); // bit * 2^i
	return result;
}

string Complement_binary_number(string &binary_number) { // 2진수에 역수를 취함
	string Real_binary_number; // 보수를 취할 2진수
	for (int i = 0; i < SIZE; i++) {
		if (Check_Bit(binary_number[i])) // bit가 0일때
			Real_binary_number += '1';
		else // bit가 1일때
			Real_binary_number += '0';
	}
	return Real_binary_number; // 보수 취한 값을 반환
}

void Carry_binary_number(string &binary_number) { // 1의보수 -> 2의 보수
	int carry = 1; // carry를 초기화
	for (int i = SIZE - 1; i >= 0; i--) {
		if ((binary_number[i] + carry) - '0' == 2) { // carry인 경우
			binary_number[i] = 0 + '0';
			carry = 1;
		}
		else {  // carry가 아닌 경우
			binary_number[i] = (binary_number[i] + carry);
			carry = 0;
			break; // carry가 없으므로 break;
		}
	}
}

int Sign_bit(string &binary_number) { // 부호와 크기 방식
	int result;
	result = BinarytoDecimal(binary_number, SIZE - 1); // 2진수 -> 10진수 부호비트를 제외
	return Check_Bit(binary_number[MSB]) ? result : result * -1; // 결과를 출력
	//부호비트가 0일때 양수, 1일때 음수를 출력
}

int One_Complement(string &binary_number) { // 1의 보수 방식
	int result;
	if (Check_Bit(binary_number[MSB])) // MSB부호가 0일 때
		result = BinarytoDecimal(binary_number, SIZE); // 2진수를 계산
	else { // MSB부호가 1일 때
		string Real_binary_number = Complement_binary_number(binary_number); // 보수를 취한 2진수
		result = BinarytoDecimal(Real_binary_number, SIZE);  // 2진수 -> 10진수
		result *= -1;  // MSB부호가 1이므로 *-1
	}
	return result; // 결과를 출력
}

int Two_Complement(string &binary_number) { // 2의 보수 방식
	int result;
	if (Check_Bit(binary_number[MSB])) // MSB부호가 0일 때
			result = BinarytoDecimal(binary_number, SIZE); // 2진수를 계산
	else { // MSB가 1일 때
		string Real_binary_number = Complement_binary_number(binary_number); // 보수를 취한 2진수
		Carry_binary_number(Real_binary_number); // 1의 보수 -> 2의 보수
		result = BinarytoDecimal(Real_binary_number, SIZE); // 2진수 -> 10진수
		result *= -1; // MSB가 1이므로 역수를 취함
	}
	return result; // 결과를 출력
}

bool Check_binary_number(string &binary_number) { // 입력값이 제대로 들어왔는지 확인
	for (int i = 0; i < SIZE; i++) {
		if (binary_number[i] != '0' && binary_number[i] != '1') // 0 또는 1이 안들어 왔을 시
			return false;
	}
	return true; // 값이 제대로 들어 왔을 시
}

int main() {
	string binary_number; // 8bit사이즈를 저장할 배열 선언
	while (true) {
		cout << "2진수 값을 입력해주세요(종료:0) : ";
		cin >> binary_number; // 숫자 하나씩 입력
		if (binary_number == "0") { // binary_number 0을 입력시 종료
			cout << "\n프로그램을 종료합니다\n";
			break;
		}
		else if (binary_number.length() != SIZE || !Check_binary_number(binary_number)) // 값이 제대로 들어왓는지 확인
			cout << "\n8bit 2진수를 입력해주세요.\n\n";
		else { // 값이 제대로 들어 왔을 시
			cout << "\n2진수\n";
			cout << "1) 부호-크기 방식 : " << binary_number <<  "\n";
			if (Check_Bit(binary_number[MSB])) { // 입력 수가 양수 일때
				cout << "2)  1의 보수 방식 : " << binary_number << "\n";
				cout << "3)  2의 보수 방식 : " << binary_number << "\n\n";
			}
			else { // 입력 수가 음수 일때
				cout << "2)  1의 보수 방식 : " << binary_number << "\n";
				string Real_binary_number = Complement_binary_number(binary_number); // 1의 보수를 취함
				cout << "   보수를 취한 값 : " << Real_binary_number << "\n";
				cout << "3)  2의 보수 방식 : " << binary_number << "\n";
				Carry_binary_number(Real_binary_number); // 1의 보수 + 1
				cout << "   보수를 취한 값 : " << Real_binary_number << "\n\n";
			}
			cout << "10진수\n";
			cout << "1) 부호-크기 방식 : " << Sign_bit(binary_number) << "\n";
			cout << "2)  1의 보수 방식 : " << One_Complement(binary_number) << "\n";
			cout << "3)  2의 보수 방식 : " << Two_Complement(binary_number) << "\n\n";
		}
	}
	return 0;
}