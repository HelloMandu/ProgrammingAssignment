#include<fstream>
#include<cstdlib>
using namespace std;

int arr[100001];
long long result;
void MergeTwoArea(int arr[], int left, int mid, int right) {
	int fIdx = left, rIdx = mid + 1;
	int *sortArr = (int*)malloc(sizeof(int)*(right + 1));
	int sIdx = left;
	while (fIdx <= mid && rIdx <= right) {
		if (arr[fIdx] <= arr[rIdx]) {
			sortArr[sIdx] = arr[fIdx++];
		}
		else {
			sortArr[sIdx] = arr[rIdx++];
			result += (mid - fIdx + 1);
		}
		sIdx++;
	}
	if (fIdx > mid) {
		for (int i = rIdx; i <= right; i++, sIdx++) {
			sortArr[sIdx] = arr[i];
		}
	}
	else {
		for (int i = fIdx; i <= mid; i++, sIdx++) {
			sortArr[sIdx] = arr[i];
		}
	}
	for (int i = left; i <= right; i++) {
		arr[i] = sortArr[i];
	}
	free(sortArr);
}

void MergeSort(int arr[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		MergeSort(arr, left, mid);
		MergeSort(arr, mid + 1, right);
		MergeTwoArea(arr, left, mid, right);
	}
}

int main() {
	ifstream inp("inv.inp");
	ofstream out("inv.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		int n;
		result = 0;
		inp >> n;
		for (int i = 0; i < n; i++) {
			inp >> arr[i];
		}
		MergeSort(arr, 0, n - 1);
		out << result << '\n';
	}
	inp.close(); out.close();
	return 0;
}