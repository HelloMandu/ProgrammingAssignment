#include<fstream>
using namespace std;

int firstArr[100001], secondArr[100001];

int main(){
    ifstream inp("./cross.inp");
    ofstream out("./cross.out");

    int n;
    inp >> n;
    for (int testcase = 1; testcase <= n; testcase++) {
        int result = 0;
        int length;
        inp >> length;
        for(int i = 1; i <= length; i++){
            int number;
            inp >> number;
            firstArr[number] = i;
        }
        for(int i = 1; i <= length; i++){
            int number;
            inp >> number;
            secondArr[number] = i;
        }

        for(int i = 1; i < length; i++){
            int top = firstArr[i];
            int bottom = secondArr[i];
            for(int j = i + 1; j <= length; j++){
                if(top < firstArr[j] && bottom > secondArr[j] || top > firstArr[j] && bottom < secondArr[j]){
                    result++;
                }
            }
        }
        out << "Case "<< testcase << ": "<< result << '\n';
    }


    return 0;
}