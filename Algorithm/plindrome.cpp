#include <fstream>
#include <string>
using namespace std;
int LCS[1000][1000];

string reversestring(string arr) {

	string rra;
	for (int i = 0; i < arr.size(); i++) {
		rra[i] = arr[arr.size() - 1];
	}
	return rra;

}

int funtion(string arr, string rra) {

	


}

int main() {

	ifstream finp("plindrome.inp");
	ofstream fout("plindroem.out");

	int testcase, result;
	string arr;
	string rra;

	finp >> testcase;

	for (int i = 0; i < testcase; i++) {

		memset(LCS, 0, sizeof(LCS));
		finp >> arr;
		rra = reversestring(arr);
		result = funtion(arr, rra);
		fout << result << endl;

	}

	return 0;
}