#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable :4996)
typedef struct TriNode { // 다항식 리스트
	int coef; // 계수
	int expo; // 지수
	struct TriNode *link;
}Node;
Node* createTerm(int coef, int expo) {
	Node *L;
	L = (Node*)malloc(sizeof(Node));
	L->coef = coef;
	L->expo = expo;
	L->link = NULL;
	return L;
}
void addLastTerm(Node *L, int coef, int expo) { // 다항식 생성을 위한 마지막 노드 삽입
	Node *newnode;
	Node *p;
	newnode = (Node*)malloc(sizeof(Node));
	newnode->coef = coef;
	newnode->expo = expo;
	newnode->link = NULL;
	if (L->link == NULL) {
		L->link = newnode;
		return;
	}
	else {
		p = L->link;
		while (p->link != NULL)
			p = p->link;
		p->link = newnode;
	}
}
void addTerm(Node *L, int coef, int expo) { // I: 삽입
	Node *newnode;
	Node *p;
	newnode = (Node*)malloc(sizeof(Node));
	newnode->coef = coef;
	newnode->expo = expo;
	if (L->link == NULL) {
		L->link = newnode;
		newnode->link = NULL;
		return;
	}
	else {
		p = L;
		while (p->link != NULL) {
			if (p->link->expo == expo)
				return;
			else if (p->link->expo < expo) {
				newnode->link = p->link;
				p->link = newnode;
				return;
			}
			p = p->link;
		}
		newnode->link = p->link;
		p->link = newnode;
	}
}
void addPoly(Node *L1, Node *L2, Node *Result) { // 다항식 덧셈
	Node *p1 = L1->link;
	Node *p2 = L2->link;
	int sum;

	while (p1 && p2) {
		if (p1->expo == p2->expo) {
			sum = p1->coef + p2->coef;
			if (sum != 0) addLastTerm(Result, sum, p1->expo);
			p1 = p1->link; p2 = p2->link;
		}
		else if (p1->expo > p2->expo) {
			addLastTerm(Result, p1->coef, p1->expo);
			p1 = p1->link;
		}
		else {
			addLastTerm(Result, p2->coef, p2->expo);
			p2 = p2->link;
		}
	}
	while (p1 != NULL) {
		addLastTerm(Result, p1->coef, p1->expo);
		p1 = p1->link;
	}
	while (p2 != NULL) {
		addLastTerm(Result, p2->coef, p2->expo);
		p2 = p2->link;
	}
}
void DelTerm(Node *L, int expo) { // D: 삭제
	if (L->link == NULL) return;
	Node *pre = L;
	Node *cur = L->link;
	while (cur != NULL) {
		if (cur->expo == expo)
			break;
		pre = cur;
		cur = cur->link;
	}
	if (cur == NULL) {
		return;
	}
	pre->link = cur->link;
	free(cur);
}
void printPoly(Node *L1, Node *L2, Node *Result, FILE *oup) {
	Node *p = L1->link;
	while (p != NULL) {
		fprintf(oup, "%d %d ", p->coef, p->expo);
		p = p->link;
	}
	fprintf(oup, "\n");
	p = L2->link;
	while (p != NULL) {
		fprintf(oup, "%d %d ", p->coef, p->expo);
		p = p->link;
	}
	fprintf(oup, "\n");
	p = Result->link;
	while (p != NULL) {
		fprintf(oup, "%d %d ", p->coef, p->expo);
		p = p->link;
	}
	fprintf(oup, "\n");
	fprintf(oup, "*");
}
int main() {

	FILE *inp = fopen("hw2.inp", "rt");
	FILE *oup = fopen("hw2.out", "wt");

	int coef, expo; // 지수, 계수
	char star; // 연산 I or D or '*'

	Node *L1 = createTerm(0, 0);
	Node *L2 = createTerm(0, 0);
	Node *Result = createTerm(0, 0);

	int Line = 0;

	while (1) {
		fscanf(inp, "%d %d", &coef, &expo);
		fscanf(inp, "%c", &star);

		if (star == '*')
			break;

		if (star == 'I') {
			while (star != '\n') {
				fscanf(inp, "%d %d", &coef, &expo);
				fscanf(inp, "%c", &star);
				if (Line == 0)
					addTerm(L1, coef, expo);
				else if (Line == 1)
					addTerm(L2, coef, expo);
				if (star == '\n') Line++;
			}
			continue;
		}

		else if (star == 'D') {
			while (star != '\n') {
				fscanf(inp, "%d", &expo);
				fscanf(inp, "%c", &star);
				if (Line == 0)
					DelTerm(L1, expo);
				else if (Line == 1)
					DelTerm(L2, expo);
				if (star == '\n') Line++;
			}
			continue;
		}
		if (Line == 0)
			addLastTerm(L1, coef, expo);
		else if (Line == 1)
			addLastTerm(L2, coef, expo);
	}

	addPoly(L1, L2, Result);
	printPoly(L1, L2, Result, oup);
	fclose(inp);
	fclose(oup);
	return 0;
}