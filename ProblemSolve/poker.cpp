#include<fstream>]
#include<algorithm>
#include<string>
#include<cstring>
#define SIZE 7
using namespace std;

struct Card {
	int c, n;
};

Card cards[SIZE];
int allPattern[4], num[14];
int patterns[4][14];

void remakeCard(Card &card, char c, char n) {
	if (n == 'A') { card.n = 1; }
	else if (n == 'T') { card.n = 10; }
	else if (n == 'J') { card.n = 11; }
	else if (n == 'Q') { card.n = 12; }
	else if (n == 'K') { card.n = 13; }
	else { card.n = n - '0'; }

	if (c == 'S') { card.c = 0; }
	else if (c == 'D') { card.c = 1; }
	else if (c == 'H') { card.c = 2; }
	else { card.c = 3; }
}

void init(ifstream &inp) {
	memset(allPattern, 0, sizeof(allPattern));
	memset(patterns, 0, sizeof(patterns));
	memset(num, 0, sizeof(num));
	for (int i = 0; i < SIZE; i++) {
		char c, n;
		inp >> c >> n;
		remakeCard(cards[i], c, n);
		allPattern[cards[i].c]++; num[cards[i].n]++; patterns[cards[i].c][cards[i].n]++;
	}
}

bool isStraight(int num[]) {
	int isFive = 0;
	for (int i = 1; i < 14; i++) {
		if (i == 13) {
			if (num[i] && num[1]) { isFive++; }
		}
		else if (num[i] && num[i + 1]) { isFive++; }
		else { isFive = 0; }
		if (isFive == 4) { return true; }
	}
	return false;
}

bool isStraightFlush() {
	for (int i = 0; i < 4; i++) {
		if (isStraight(patterns[i])) { return true; }
	}
	return false;
}

bool isFourCard() {
	for (int i = 1; i < 14; i++) {
		if (num[i] >= 4) { return true; }
	}
	return false;
}

bool isFullHouse() {
	bool onePair = false, triple = false;
	for (int i = 0; i < 14; i++) {
		if (num[i] >= 2) {
			if (num[i] >= 3) {
				if (!triple) { triple = true; }
				else { onePair = true; }
			}
			else { onePair = true; }
		}
		if (onePair && triple) { return true; }
	}
	return false;
}

bool isFlush() {
	for (int i = 0; i < 4; i++) {
		if (allPattern[i] >= 5) { return true; }
	}
	return false;
}

bool isTriple() {
	for (int i = 1; i < 14; i++) {
		if (num[i] >= 3) { return true; }
	}
	return false;
}

bool isTwoPair() {
	bool flag = false;
	for (int i = 1; i < 14; i++) {
		if (num[i] >= 2) { 
			if (flag) { return true; }
			else { flag = true; }
		}
	}
	return false;
}

bool isOnePair() {
	for (int i = 1; i < 14; i++) {
		if (num[i] >= 2) { return true; }
	}
	return false;
}

string getPedigree() {
	if (isStraightFlush()) { return "Straight Flush"; }
	else if (isFourCard()) { return "Four Card"; }
	else if (isFullHouse()) { return "Full House"; }
	else if (isFlush()) { return "Flush"; }
	else if (isStraight(num)) { return "Straight"; }
	else if (isTriple()) { return "Triple"; }
	else if (isTwoPair()) { return "Two Pair"; }
	else if (isOnePair()) { return "One Pair"; }
	return "Top";
}

int main() {
	ifstream inp("poker.inp");
	ofstream out("poker.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		init(inp);
		out << getPedigree() << '\n';
	}
	return 0;
}
