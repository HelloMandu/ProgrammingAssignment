#include<stdio.h>
#pragma warning(disable : 4996)
typedef long long lint;

int Numberofterms(lint A, lint limit) {
	int cnt = 1;
	while (1) {
		if (A == 1) // A = 1ÀÏ¶§
			return cnt;
		else if (A % 2 == 0) { // Â¦¼öÀÏ¶§
			A /= 2;
			cnt++;
		}
		else { // È¦¼öÀÏ¶§
			A = A * 3 + 1;
			if (A > limit) // 
				return cnt;
			cnt++;
		}
	}
}

int main() {
	FILE *inp = fopen("sequence.inp", "rt");
	FILE *out = fopen("sequence.out", "wt");
	lint A, limit;
	int i = 1;
	while (fscanf(inp, "%lld %lld\n", &A, &limit)) {
		if (A < 0 && limit < 0)
			break;
		fprintf(out, "Case %d: A = %lld, limit = %lld, number of terms = %d\n", i++, A, limit, Numberofterms(A, limit));
	}
	return 0;
}