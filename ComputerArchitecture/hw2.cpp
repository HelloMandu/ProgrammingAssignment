#include<iostream>
#include<string>
#define SIZE 8
#define MSB 0
using namespace std;

bool Check_Bit(char bit) {//bit가 0이 아닐 때 false, 0일 때 true를 반환 
	return (bit - '0') ? false : true;
}

void Carry_binary_number(string &binary_number) { // 1의보수 -> 2의 보수
	int carry = 1; // carry를 초기화
	for (int i = binary_number.length() - 1; i >= MSB; i--) {
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

string Complement_binary_number(string &binary_number) { // 2진수에 역수를 취함
	string Real_binary_number; // 보수를 취할 2진수
	for (int i = MSB; i < binary_number.length(); i++) {
		if (Check_Bit(binary_number[i])) // bit가 0일때
				Real_binary_number += '1';
		else // bit가 1일때
				Real_binary_number += '0';
	}
	Carry_binary_number(Real_binary_number);
	return Real_binary_number; // 2의보수 취한 값을 반환
}

string Binarization(int num) { // 입력받은 10진수를 2진수로 바꿈
	bool sign = true; // true = 양수 false = 음수
	if (num < 0) {
		num *= -1; // num이 음수일 때 역수를 취함
		sign = false; // 음수 표시
	}
	string Binary_number = "00000000"; // 원래의 2진수
	for (int i = SIZE - 1; i >= MSB; i--) {
		Binary_number[i] = num % 2 + '0';
		num /= 2;
	}
	return sign ? Binary_number : Complement_binary_number(Binary_number); // 양수면 그래도 출력, 음수면 역으로 출력
}

void Shift_Left(string &binary_number, int num) { // 왼쪽 시프트
	for (int i = 0; i < num; i++) {
		binary_number += '0';
		binary_number.erase(MSB, 1);
	}
}

void Shift_Right(string &binary_number, int num) { // 오른쪽 시프트
	for (int i = 0; i < num; i++) {
		binary_number = '0' + binary_number;
		binary_number.erase(binary_number.length() - 1, binary_number.length());
	}
}

void Add_binary_number(string &result, string &multiplicand) {
	int carry = 0; // 초기의 carry는 0
	for (int i = SIZE * 2 - 1; i >= MSB; i--) {
		if (result[i] == '0' && multiplicand[i] == '0') { // 둘다 0일 때
			if (carry) { // carry가 있을 떄
				result[i] = '1';
				carry = 0;
			}
			else // carry가 없을 때
				result[i] = '0';
		}
		else if (result[i] == '1' && multiplicand[i] == '1') {// 둘다 1일 때
			if (carry) { // carry가 있을 때
				result[i] = '1';
				carry = 1;
			}
			else {// carry가 없을 때
				result[i] = '0';
				carry = 1;
			}
		}
		else { // 둘중 하나만 1일 때
			if (carry) { // carry가 있을 때
				result[i] = '0';
				carry = 1;
			}
			else // carry가 없을 때
				result[i] = '1';
		}
	}
}

string Shift_Multiply(int num1, int num2) {
	bool sign = (num1 * num2 > 0) ? true : false; // 양수, 음수
	string multiplicand, multiplier; // 피승수, 승수
	string result = "0000000000000000"; // 결과값이 될 누적부분곱
	multiplicand = Binarization(num1); multiplier = Binarization(num2); // 피승수와 승수를 2진수화
	if (!Check_Bit(multiplicand[MSB]))  // 피승수가 음수일 때 보수를 취함
		multiplicand = Complement_binary_number(multiplicand);
	if (!Check_Bit(multiplier[MSB])) // 승수가 음수일 때 보수를 취함
		multiplier = Complement_binary_number(multiplier);
	multiplicand += "00000000"; // 피승수를 16bit로 증가
	for (int i = SIZE - 1; i >= MSB; i--) { // 승수를 오륵쪽시프트한 것과 같음
		if (!Check_Bit(multiplier[i])) // 비트가 0아닐 때
			Add_binary_number(result, multiplicand); // 누적곱을 더함
		Shift_Right(result, 1); // 오른쪽으로 1칸 shift
	}
	return sign ? result : Complement_binary_number(result); // 음수일 때 보수를 반환
}

int Check_Booth(string &multiplier, int i) {
	if (multiplier[i - 1] == '0') // 0, 1인 경우
		return multiplier[i] == '0' ? 0 : 1;
	else // 2, 3인 경우
		return multiplier[i] == '0' ? 2 : 0;
}

string Booth_Algorithm(int num1, int num2) {
	string multiplicand, multiplier; // 피승수, 승수
	string result = "0000000000000000"; // 결과값이 될 누적부분곱
	string complement_binary_number;
	multiplicand = Binarization(num1); multiplier = Binarization(num2); // 피승수와 승수를 2진수화
	multiplier += '0'; // 추가비트를 추가
	if(num1 > 0) // 피승수가 양수일 때
		multiplicand = "00000000" + multiplicand; // 피승수를 16bit로 증가
	else // 피승수가 음수일 때
		multiplicand = "11111111" + multiplicand; // 피승수를 16bit로 증가
	for (int i = SIZE; i > MSB; i--) {
		switch (Check_Booth(multiplier, i)) { // Booth알고리즘 연산
		case 0: // 피승수를 왼쪽시프트 - 0 0 || 1 1
			Shift_Left(multiplicand, 1);
			break;
		case 1: // 피승수를 누적부분곱에 더한 후 피승수를 왼쪽 시프트 - 0 1
			Add_binary_number(result, multiplicand);
			Shift_Left(multiplicand, 1);
			break;
		case 2: // 피승수를 누적부분곱에 뺀 후 피승수를 왼쪽 시프트 - 1 0
			complement_binary_number = Complement_binary_number(multiplicand);
			Add_binary_number(result, complement_binary_number);
			Shift_Left(multiplicand, 1);
			break;
		}
	}
	return result;
}

int main() {
	int multiplicand, multiplier; // 입력받을 십진수 2개
	while (true) {
		cout << "10진수 2개 입력(종료 : 128 128) : ";
		cin >> multiplicand >> multiplier;
		if (multiplicand == 128 && multiplier == 128) {
			cout << "프로그램을 종료합니다\n";
			break;
		}
		else if (multiplicand > 127 || multiplicand < -127 || multiplier > 127 || multiplier < -127) // 범위를 벗어나는 경우 Overflow
			cout << "Overflow 발생\n\n";
		else {
			cout << '\n' << "덧셈알고리즘(2) : " << Shift_Multiply(multiplicand, multiplier) << " - 2의 보수형식\n\n";
			cout << "Booth 알고리즘 :  " << Booth_Algorithm(multiplicand, multiplier) << " - 2의 보수형식\n\n";
		}
	}
	return 0;
}