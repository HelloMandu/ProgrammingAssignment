#include<iostream>
#include<fstream>
#include <queue>
#pragma warning(disable : 4996)
using namespace std;
typedef long long lint;

lint add (priority_queue< lint, vector<lint>, greater<lint> > *heap) {
	lint cost = 0; // 결과 값
	while (true) {
		lint num1 = heap->top(); heap->pop();
		lint num2 = heap->top(); heap->pop(); // 제일 작은 수 2개를 뽑는다
		cost += num1 + num2; // 결과에 더함
		if (!heap->empty()) // 비어있지 않을 때
			heap->push(num1 + num2); // 두 개 더한 값을 넣는다
		else // 비었을 때
			return cost;
	}
}

int main() {
	ifstream inp("add.inp");
	ofstream out("add.out");
	int n, num;
	priority_queue< lint, vector<lint>, greater<lint> > heap; // 최소힙
	while (true) {
		inp >> n;
		if (!n) break;
		for (int i = 0; i < n; i++) {
			inp >> num;
			heap.push(num); // 삽입
		}
		out << add(&heap) << "\n";
	}
	return 0;
}