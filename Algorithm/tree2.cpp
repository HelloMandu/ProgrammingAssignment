#include<fstream>
#include<vector>
#define FindRoot(form, n) form > 0 ? n - 1 : 0  //루트가 어디있는지 찾음
#define Lsize(root, begin) root - begin // 왼쪽 자식의 갯수를 구함
#define Rsize(root, finish) finish - root // 오른쪽 자식의 갯수를 구함
using namespace std;

ifstream inp("tree2.inp");
ofstream out("tree2.out");

vector<int> pre, ino, post;

void INPUT(vector<int> &arr, int n) { // 입력받음
	int key;
	arr.resize(n); // n사이즈만큼 할당
	for (int i = 0; i < n; i++) {
		inp >> key;
		arr[i] = key;
	}
}

int Find_inorder_root(vector<int> &arr, int root_index, int begin, int finish) { // 중위 순회에서 루트의 index값을 반환
	for (int i = begin; i <= finish; i++) { // 중위 순회의 루트인덱스를 찾음
		if (ino[i] == arr[root_index])
			return i;
	}
	return root_index;
}

void Find_Postorder(int pre_root_index, int begin, int finish) { // postorder을 찾음
	int ino_root_index = Find_inorder_root(pre, pre_root_index, begin, finish); // 중위 순회의 루트인덱스를 찾음
	if (begin < finish) {
		int L_size = Lsize(ino_root_index, begin), R_size = Rsize(ino_root_index, finish); // 왼쪽사이즈와 오른쪽사이즈
		int L_child = pre_root_index + 1, R_child = pre_root_index + L_size + 1; // 왼쪽자식과 오른쪽자식
		if (L_size > 0) // 왼쪽자식이 있을시
			Find_Postorder(L_child, begin, ino_root_index - 1); // L위치를 루트로
		if (R_size > 0) // 오른쪽자식이 있을시
			Find_Postorder(R_child, ino_root_index + 1, finish); // R위치를 루트로
	}
	out << ino[ino_root_index] << '\n';
}

void Find_Preorder(int post_root_index, int begin, int finish) { // preorder을 찾음
	int ino_root_index = Find_inorder_root(post, post_root_index, begin, finish); // 중위 순회의 루트인덱스를 찾음
	out << ino[ino_root_index] << '\n';
	if (begin < finish) {
		int L_size = Lsize(ino_root_index, begin), R_size = Rsize(ino_root_index, finish); // 왼쪽사이즈와 오른쪽사이즈
		int L_child = post_root_index - R_size - 1, R_child = post_root_index - 1; // 왼쪽자식과 오른쪽자식
		if (L_size > 0) // 왼쪽자식이 있을시
			Find_Preorder(L_child, begin, ino_root_index - 1); // L위치를 루트로
		if (R_size > 0) // 오른쪽자식이 있을시
			Find_Preorder(R_child, ino_root_index + 1, finish); // R위치를 루트로
	}
}

int main() {
	int n, type; // 정점의 수, 순회 type - pre : -1, in : 0, post : 1
	int form = 0, two = 2; // 어떤타입이 들어왓는지 형식을 정함
	inp >> n;
	while (two--) { // 두개의 순회결과를 받음
		inp >> type;
		form += type;
		switch (type) {
		case -1: //전위입력
			INPUT(pre, n);
			break;
		case 0: // 중위입력
			INPUT(ino, n);
			break;
		case 1: // 후위입력
			INPUT(post, n);
			break;
		}
	}
	int root = FindRoot(form, n); // 루트를찾음
	if (form > 0)
		Find_Preorder(root, 0, n - 1);
	else
		Find_Postorder(root, 0, n - 1);
	inp.close(); out.close();
	return 0;
}