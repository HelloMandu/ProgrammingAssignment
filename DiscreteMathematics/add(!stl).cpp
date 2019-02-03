#include<iostream>
#include<fstream>
#pragma warning(disable : 4996)
using namespace std;
typedef long long lint;
#define MAX_ELEMENT 100000

typedef struct { // 히프에 대한 1차원 배열과 히프 원소의 갯수를 구조체로 묶어서 선언
	lint heap[MAX_ELEMENT];
	lint heap_size;
} heapType;

heapType* createHeap() // 공백 히프를 생성하는 연산
{
	heapType *h = (heapType *)malloc(sizeof(heapType));
	h->heap_size = 0;
	return h;
}

void insertHeap(heapType *h, lint item) // 히프에item을 삽입하는 연산
{
	lint i;
	h->heap_size = h->heap_size + 1;
	i = h->heap_size;
	while ((i != 1) && (item < h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}
lint deleteHeap(heapType *h) // 히프의 루트를 삭제하여 반환하는 연산
{
	lint parent, child;
	lint item, temp;
	item = h->heap[1];
	temp = h->heap[h->heap_size];
	h->heap_size = h->heap_size - 1;
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child]) > h->heap[child + 1])
			child++;
		if (temp <= h->heap[child]) break;
		else {
			h->heap[parent] = h->heap[child];
			parent = child;
			child = child * 2;
		}
	}
	h->heap[parent] = temp;
	return item;
}

lint add(heapType *h) {
	lint cost = 0; // 결과 값

	while (true) {
		lint num1 = deleteHeap(h);
		lint num2 = deleteHeap(h); // 제일 작은 수 2개를 뽑는다

		cost += num1 + num2; // 결과에 더함

		if (h->heap_size != 0) // 비어있지 않을 때
			insertHeap(h, num1 + num2); // 두 개 더한 값을 넣는다
		else // 비었을 때
			return cost;
	}

}

int main()
{
	ifstream inp("add.inp");
	ofstream out("add.out");
	int n, num;
	heapType *heap = createHeap();
	while (true) {
		inp >> n;
		if (!n) break;
		for (int i = 0; i < n; i++) {
			inp >> num;
			insertHeap(heap, num); // 삽입
		}
		out << add(heap) << "\n";
	}
	return 0;
}