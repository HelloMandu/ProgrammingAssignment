#include<stdio.h>
#include<stdlib.h>
#define m_ary 10 // 10진 트라이
#define record 4 // 레코드길이 || 높이
#pragma warning(disable:4996)

int Nodesize = 1; // 노드의 개수를 저장 (루트포함)

typedef struct Node {
	int check_leaf; // 리프인지 체크
	char trie[record]; // 경로를 저장
	char address[record]; // 저장주소
	struct Node *next[m_ary]; // 자식노드를 가리킬 배열
}Node;

typedef struct TrieTree { // 트리의 루트노드 설정
	Node *root;
}TrieTree;

Node *createNode() { // 새로운 노드 생성
	Node *newNode = (Node*)malloc(sizeof(Node));
	for (int i = 0; i < m_ary; i++)
		newNode->next[i] = NULL;
	return newNode;
}

void InsertAddress(Node *leaf, char trie[], char address[]) { // 리프노드 : 주소값을 저장
	leaf->check_leaf = 1; // 체크노드임을 저장
	for (int i = 0; i < record; i++) // 키값을 저장
		leaf->address[i] = address[i];
	for (int i = 0; i < record; i++) // 경로값을 저장
		leaf->trie[i] = trie[i];
		Nodesize--; // 리프아래에 삽입된 노드--
}

void InsertTrie(TrieTree *Trie, char trie[], char address[]) { // 키값을 삽입
	Node *child = Trie->root;
	for (int i = 0; i < record; i++) {
		if (!child->next[trie[i] - '0']) { // 자식노드가 없을 때 새로운 노드를 생성
			child->next[trie[i] - '0'] = createNode();
			Nodesize++; // 노드개수++
		}
		child = child->next[trie[i] - '0']; // 노드가 있을 때
	}
	// 마지막 주소를 저장
	InsertAddress(child, trie, address); 
}

int Check_Wild_Card(char wild_card[]) { // 와일드카드타입을 정함
	for (int i = 0; i < record; i++) {
		if (wild_card[i] == '*') // 와일드카드가 들어왔을시
			return 1;
	}
	return 0; // 와일드카드가 없을시
}

int address_check(Node *child, char wild_card[]) { // 내가 찾는 레코드인지 체크
	for (int i = 0; i < record; i++) {
		if (child->trie[i] != wild_card[i]) // 하나라도 틀릴시
			return 0;
	}
	return 1; // 모두 맞을 시
}

void Print_Wild_Card(Node *child, FILE *out) { // 와일드카드가 있을 때 출력
	int recordCount = 0;
	for (int i = 0; i < m_ary; i++) {
		if (child->next[i] != NULL) { // NULL이 아닐때
			if (child->next[i]->check_leaf != 1) { // 리프도달
					Print_Wild_Card(child->next[i], out);
			}
			else { // 리프의 값을 출력
				for (int j = 0; j < record; j++)
					fprintf(out, "%c", child->next[i]->trie[j]);
				fprintf(out, " %d ", ++recordCount);
				for (int j = 0; j < record; j++)
					fprintf(out, "%c", child->next[i]->address[j]);
				fprintf(out, " ");
			}
			
		}
	}
}

void PrintTrie(TrieTree *Trie, char wild_card[], char address[], FILE *out) { // 트라이 출력
	Node *parent = NULL;
	Node *child = Trie->root; // 루트;
	for (int i = 0; i < record && wild_card[i - 1] != '*'; i++) {
		if (child == NULL) { // 해당경로가 존재하지 않을시
			fprintf(out, "no\n");
			return;
		}
		if (wild_card[i] != '*') {
			parent = child;
			child = parent->next[wild_card[i] - '0']; // 자식 설정
		}
	}
	if (Check_Wild_Card(wild_card)) { // record가 있는 경우
		Print_Wild_Card(child, out); // child기준
		fprintf(out, "\n");
	}
	else { // record가 없는 경우 
		int recordCount = 0;
		for (int i = 0; i < m_ary; i++) {
			if (parent->next[i] != NULL) {// NULL이 아닌 경우
				if (address_check(parent->next[i], wild_card)) // 주소가 맞는지 확인
					break; // 주소가 맞으면 위치를 찼았으므로 break;
				recordCount++;
			}
		}
		if(child == NULL)
			fprintf(out, "no\n");
		else {
			for (int i = 0; i < record; i++)
				fprintf(out, "%c", child->trie[i]);
			fprintf(out, " %d ", ++recordCount);
			for (int i = 0; i < record; i++)
				fprintf(out, "%c", child->address[i]);
			fprintf(out, "\n");
		}
	}
}

int main() {
	FILE *inp = fopen("hw4.inp", "r");
	FILE *out = fopen("hw4.out", "w");
	if (inp == NULL) fprintf(stderr, "can't open %s\n", "hw3.inp");
	if (out == NULL) fprintf(stderr, "can't open %s\n", "hw3.out");
	char bracket; // 괄호
	TrieTree *Trie = (TrieTree*)malloc(sizeof(TrieTree));
	Trie->root = createNode(); // 트라이트리의 루트노드 생성
	char trie[record], address[record]; // 실제레코드와, 저장된 주소값
	while (1) { // 첫번째 줄 입력
		fscanf(inp, "%c", &bracket); // (
		for (int i = 0; i < record; i++)
			fscanf(inp, "%c", &trie[i]); // 레코드를 입력받음
		fscanf(inp, "%c", &bracket);// ,
		for (int i = 0; i < record; i++)
			fscanf(inp, "%c", &address[i]); // 주소값을 입력받음
		fscanf(inp, "%c", &bracket); // )
		InsertTrie(Trie, trie, address); // 트라이삽입
		fscanf(inp, "%c", &bracket); // ' '
		if (bracket == '\n')
			break;
	}
	fprintf(out, "%d\n", Nodesize); // 노드의 개수를 출력
	while (1) {
		char wild_card[record]; // 와일드 카드
		for (int i = 0; i < record && wild_card[i - 1] != '*'; i++)
			fscanf(inp, "%c", &wild_card[i]); // 레코드를 입력받음
		PrintTrie(Trie, wild_card, address, out);
		fscanf(inp, "%c", &bracket); // ' '
		if (bracket == '\n')
			break;
	}
	fprintf(out, "*");
	fclose(inp); fclose(out);
	return 0;
}