#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define QSIZE 5
#pragma warning(disable:4996)

typedef struct Person {
	const char *name;
	int mytall, myintelligence, mymoney;
	int yourTall, yourIntelligence, yourMoney;
}People;

typedef struct Queue {
	int start, end;
	Person peoples[QSIZE];
}Queue;

int allmatchcnt = 0;

Queue *Makequeue() {
	Queue *newQueue = (Queue*)malloc(sizeof(Queue));
	newQueue->start = 0;
	newQueue->end = 0;
	return newQueue;
}
int Empty(Queue *queue) {
	return queue->start == queue->end;
}
int Full(Queue *queue) {
	return ((queue->end + 1) % QSIZE) == queue->start;
}
void pushQueue(Queue *queue, Person people) {
	if (!Full(queue)) {
		queue->peoples[queue->end] = people;
		queue->end = (queue->end + 1) % QSIZE;
	}
}
void popQueue(Queue *queue) {
	if (!Empty(queue)) {
		queue->start = (queue->start + 1) % QSIZE;
	}
}
Person peek(Queue *queue) {
	if (!Empty(queue)) {
		return queue->peoples[queue->start];
	}
}

Person *makePeople(const char *name, int tall, int intelligence, int money, int hTall, int hIntelligence, int hMoney) {
	Person *newPeople = (Person*)malloc(sizeof(Person));
	newPeople->name = name;
	newPeople->mytall = tall; newPeople->myintelligence = intelligence; newPeople->mymoney = money;
	newPeople->yourTall = hTall; newPeople->yourIntelligence = hIntelligence; newPeople->yourMoney = hMoney;
	return newPeople;
}

int canMatching(Person *man, Person *woman) {
	if (man->mytall == woman->yourTall && man->yourTall == woman->mytall) {
		if (man->myintelligence == woman->yourIntelligence && man->yourIntelligence == woman->myintelligence) {
			if (man->mymoney == woman->yourMoney && man->yourMoney == woman->mymoney) {
				return 1;
			}
		}
	}
	return 0;
}

void meeting(Queue *male, Queue *female) {
	if (!Empty(male) && !Empty(female)) {
		Person man, woman;
		man = peek(male); woman = peek(female);
		if (canMatching(&man, &woman)) {
			printf("%s & %s MATCHING\n", man.name, woman.name);
			popQueue(male); popQueue(female);
			allmatchcnt++;
		}
		else {
			printf("No!\n");
			if (rand() % 2) {
				popQueue(male);
				pushQueue(male, man);
			}
			else {
				popQueue(female);
				pushQueue(female, woman);
			}
		}
	}
	else {
		printf("¸ÅÄª ºÒ°¡\n");
	}
}

Person *man[QSIZE], *woman[QSIZE];

const char *mNames[QSIZE] = { "Steve", "James", "Peter", "Henry", "Charlse" };
const char *wNames[QSIZE] = { "Dana", "Hanna", "Sally", "Anna", "Nina" };

int main() {

	srand(time(NULL));

	man[0] = makePeople(mNames[0], 165, 100, 0, 155, 100, 0);
	man[1] = makePeople(mNames[1], 170, 105, 1000, 160, 105, 1000);
	man[2] = makePeople(mNames[2], 175, 110, 10000, 165, 110, 10000);
	man[3] = makePeople(mNames[3], 180, 115, 100000, 170, 115, 100000);
	man[4] = makePeople(mNames[4], 185, 120, 1000000, 175, 120, 1000000);
	woman[0] = makePeople(wNames[0], 175, 120, 1000000, 185, 120, 1000000);
	woman[1] = makePeople(wNames[1], 170, 115, 100000, 180, 115, 100000);
	woman[2] = makePeople(wNames[2], 165, 110, 10000, 175, 110, 10000);
	woman[3] = makePeople(wNames[3], 160, 105, 1000, 170, 105, 1000);
	woman[4] = makePeople(wNames[4], 155, 100, 0, 165, 100, 0);

	Queue *male = Makequeue(), *female = Makequeue();
	int maleCnt = 0, femaleCnt = 0;
	while (true) {
		if (allmatchcnt == 5) {
			break;
		}
		if ((rand() % 3) == 0) {
			pushQueue(male, *man[maleCnt % QSIZE]);
			maleCnt++;
		}
		else if ((rand() % 3) == 1) {
			pushQueue(female, *woman[femaleCnt % QSIZE]);
			femaleCnt++;
		}
		else {
			meeting(male, female);
		}
	}
	printf("¤µ¤¡\n");
	return 0;
}