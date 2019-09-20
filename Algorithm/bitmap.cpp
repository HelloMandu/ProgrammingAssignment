#include<fstream>
#include<cstdio>
#include<string>
#include<vector>
#pragma warning(disable:4996)
using namespace std;

char map[201][201];
char bit[40001];
int row, col;
char *it;

void input(ifstream &inp, FILE *out, char type) {
	inp >> row >> col;
	if (type == 'B') {
		fprintf(out, "D%4d%4d", row, col);
		for (int i = 0; i < row * col; i++) {
			inp >> bit[i];
		}
	}
	else {
		fprintf(out, "B%4d%4d", row, col);
		string temp;
		int line = 0;
		while(true) {
			inp >> temp;
			for (int j = line * 50; j < line * 50 + temp.length(); j++) {
				bit[j] = temp[j % 50];
			}
			line++;
			if (temp.length() != 50) {
				return;
			}
		}
	}
}

void setMap() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			map[i][j] = bit[(i * col) + j];
		}
	}
}

bool isSame(int y, int x, int row, int col) {
	char &bit = map[y][x];
	for (int i = y; i < y + row; i++) {
		for (int j = x; j < x + col; j++) {
			if (bit != map[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void BtoD(int y, int x, int row, int col, string &result) {
	if (y < y + row && x < x + col) {
		if (isSame(y, x, row, col)) {
			result.push_back(map[y][x]);
			return;
		}
		result.push_back('D');
		int nRow = row % 2 != 0 ? row / 2 + 1 : row / 2;
		int nCol = col % 2 != 0 ? col / 2 + 1 : col / 2;
		BtoD(y, x, nRow, nCol, result);
		BtoD(y, x + nCol, nRow, col / 2, result);
		BtoD(y + nRow, x, row / 2, nCol, result);
		BtoD(y + nRow, x + nCol, row / 2, col / 2, result);
	}
}

void paintBit(int y, int x, int row, int col, char binary, string &result) {
	for (int i = y; i < y + row; i++) {
		for (int j = x; j < x + col; j++) {
			map[i][j] = binary;
		}
	}
}

void DtoB(int y, int x, int row, int col, string &result) {
	if (y < y + row && x < x + col) {
		char ch = *(it++);
		if (ch != 'D') {
			paintBit(y, x, row, col, ch, result);
			return;
		}
		int nRow = row % 2 != 0 ? row / 2 + 1 : row / 2;
		int nCol = col % 2 != 0 ? col / 2 + 1 : col / 2;
		DtoB(y, x, nRow, nCol, result);
		DtoB(y, x + nCol, nRow, col / 2, result);
		DtoB(y + nRow, x, row / 2, nCol, result);
		DtoB(y + nRow, x + nCol, row / 2, col / 2, result);
	}
}

void printResult(FILE *out, string &result, char type) {
	if (type == 'B') {
		for (int i = 0; i < result.length(); i++) {
			if (i % 50 == 0) {
				fprintf(out, "\n");
			}
			fprintf(out, "%c", result[i]);
		}
	}
	else {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (((i * col) + j) % 50 == 0) {
					fprintf(out, "\n");
				}
				fprintf(out, "%c", map[i][j]);
			}
		}
	}
	fprintf(out, "\n");
}

int main() {
	ifstream inp("bitmap.inp");
	FILE *out = fopen("bitmap.out", "w");
	char type; 
	while (inp >> type) {
		string result;
		if (type == '#') {
			inp.close(); fclose(out);
			return 0;
		}
		input(inp, out, type);
		if (type == 'B') {
			setMap();
			BtoD(0, 0, row, col, result);
		}
		else {
			it = bit;
			DtoB(0, 0, row, col, result);
		}
		printResult(out, result, type);
	}
}