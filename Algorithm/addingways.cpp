#include<fstream>
#include<cstring>
#define MOD 1000000007
using namespace std;

long long dp[301][301];

int main() {
	ifstream inp("addingways.inp");
	ofstream out("addingways.out");
	int N, K;
	while (true) {
		memset(dp, 0, sizeof(dp));
		inp >> N >> K;
		if (N == 0 && K == 0) {
			return 0;
		}
		for (int i = 1; i <= N; i++) {
			dp[1][i] = 1;
			dp[i][i] = 1;
		}
		for (int i = 2; i <= K; i++) {
			for (int j = i + 1; j <= N; j++) {
				for (int k = 1; k <= i; k++) {
					dp[i][j] = (dp[i][j] + dp[k][j - i]) % MOD;
				}
			}
		}
		out << dp[K][N] << '\n';
	}
	return 0;
}