#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 100
typedef struct { // 히프에 대한 1차원 배열과 히프 원소의 갯수를 구조체로 묶어서 선언
	int heap[MAX_ELEMENT];
	int heap_size;
} heapType;

heapType* createHeap() // 공백 히프를 생성하는 연산
{
	heapType *h = (heapType *)malloc(sizeof(heapType));
	h->heap_size = 0;
	return h;
}

void insertHeap(heapType *h, int item) // 히프에item을 삽입하는 연산
{
	int i;
	h->heap_size = h->heap_size + 1;
	i = h->heap_size;
	while ((i != 1) && (item > h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}
int deleteHeap(heapType *h) // 히프의 루트를 삭제하여 반환하는 연산
{
	int parent, child;
	int item, temp;
	item = h->heap[1];
	temp = h->heap[h->heap_size];
	h->heap_size = h->heap_size - 1;
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child]) < h->heap[child + 1])
			child++;
		if (temp >= h->heap[child]) break;
		else {
			h->heap[parent] = h->heap[child];
			parent = child;
			child = child * 2;
		}
	}
	h->heap[parent] = temp;
	return item;
}

void printHeap(heapType *h) // 1차원 배열 히프의 내용을 출력하는 연산
{
	int i;
	printf("Heap : ");
	for (i = 1; i <= h->heap_size; i++)
		printf("[%d] ", h->heap[i]);
}

void main()
{
	int i, n, item;
	heapType *heap = createHeap();
	insertHeap(heap, 10);
	insertHeap(heap, 45);
	insertHeap(heap, 19);
	insertHeap(heap, 11);
	insertHeap(heap, 96);

	printHeap(heap);
	n = heap->heap_size;
	for (i = 1; i <= n; i++) {
		item = deleteHeap(heap);
		printf("\n delete : [%d] ", item);
	}
	getchar();
}