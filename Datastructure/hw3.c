#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable :4996)
typedef struct CNode { // 원형
	int code;
	struct CNode *link;
}CNode;

CNode *Chead;

void addLastCNode(int code) { //원형
	CNode *newnode = (CNode*)malloc(sizeof(CNode));
	CNode *p;
	newnode->code = code;
	if (Chead == NULL) {
		Chead = newnode;
		newnode->link = newnode;
	}
	p = Chead;
	while (p->link != Chead)
		p = p->link;
	p->link = newnode;
	newnode->link = Chead;
}
//-------------------------------------------------------------원형연결리스트
typedef struct Node {
	char data;
	struct Node *link;
}Node;

Node *top, *front, *rear;

void push(char data) { //Stack
	Node *newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;
	newnode->link = top;
	top = newnode;
}
char pop() { //Stack
	Node *temp = top;
	char data;
	if (top == NULL)
		return 0;
	data = top->data;
	top = top->link;
	free(temp);
	return data;
}
//-----------------------------------------------------------스택
void enQueue(char data) { //Queue
	Node *newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;
	newnode->link = NULL;
	if (front == NULL) {
		front = newnode;
		rear = newnode;
	}
	else {
		rear->link = newnode;
		rear = newnode;
	}
}
char deQueue(int num) { //Queue
	Node *p = front;
	char data;
	if (front == NULL || rear == NULL)
		return 0;
	else {
		data = front->data;
		front = front->link;
		if (front == NULL)
			rear = NULL;
		free(p);
		if (data == ' ')
			return data;
		if (data >= 'A' && data <= 'Z') {
			data -= num;
			if (data < 'A')
				return data + 26;
		}
		else if (data >= 'a' && data <= 'z') {
			data -= num;
			if (data < 'a')
				return data + 26;
		}
		return data;
	}
}
//-----------------------------------------------------------큐
int main() {
	FILE *inp = fopen("hw3.inp", "rt");
	FILE *oup = fopen("hw3.out", "wt");
	char data, result;
	int Line = 0;
	while (1) {
		if (Line > 1)
			break;
		fscanf(inp, "%c", &data);
		if (data == '*') {
			break;
		}
		if (Line == 0) {
			if (data == '\n') {
				Line++;
				continue;
			}
			push(data);
		}
		else if (Line == 1) {
			if (data == '\n') {
				Line++;
				continue;
			}
			enQueue(data);
		}
	}
	while (top != NULL) { // pop
		result = pop();
		fprintf(oup, "%c", result);
	}
	fprintf(oup, "\n");
	while (1) { // code입력
		fscanf(inp, "%c", &data);
		if (data == '\n')
			break;
		addLastCNode(data - '0');
	}
	while (front != NULL) { // deQueue
		result = deQueue(Chead->code);
		fprintf(oup, "%c", result);
		if (result != ' ')
			Chead = Chead->link;
	}
	fprintf(oup, "\n");
	fprintf(oup, "*");
	return 0;
}