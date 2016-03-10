// facebook hacker cup round 3 2016

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <assert.h>

using namespace std;

int M, N, K;

int dp[2][100][2][100][1001];
vector<string> matrix(100);

int Calc(int isCol, int idx, int isUp, int subIdx, int k);

int CommonCalc(bool currUp, int isCol, int idx, int isUp, int subIdx, int k)
{
	int r = 0;
	if (isUp) {
		r = Calc(isCol, idx, currUp, subIdx+1, k);
		if (k > 0) {
			r = min(r, Calc(isCol, idx, !currUp, subIdx+1, k-1));
		}
	}
	else {
		assert(subIdx > 0);
		if (!currUp)
			r = Calc(isCol, idx, currUp, subIdx+1, k);
		else
			r = 1 + Calc(isCol, idx, currUp, subIdx+1, k);
		if (k > 0) {
			if (!currUp)
				r = min(r, 1+Calc(isCol, idx, !currUp, subIdx+1, k-1));
			else
				r = min(r, Calc(isCol, idx, !currUp, subIdx+1, k-1));
		}
	}
	return r;
}

int Calc(int isCol, int idx, int isUp, int subIdx, int k)
{
	if (!isCol) {

		if (idx == M)
			return Calc(1, 0, 1, 0, k);
		if (subIdx == N) 
			return Calc(0, idx+1, 1, 0, k);

		int &r = dp[isCol][idx][isUp][subIdx][k];
		if (r != -1)
			return r;

		bool currUp = (matrix[idx][subIdx] == 'A' || matrix[idx][subIdx] == 'D');
		r = CommonCalc(currUp, isCol, idx, isUp, subIdx, k);
		return r;
	}

	if (idx == N)
		return 0;
	if (subIdx == M) 
		return Calc(1, idx+1, 1, 0, k);

	int &r = dp[isCol][idx][isUp][subIdx][k];
	if (r != -1)
		return r;

	bool currUp = (matrix[subIdx][idx] == 'A' || matrix[subIdx][idx] == 'B');
	r = CommonCalc(currUp, isCol, idx, isUp, subIdx, k);
	return r;
}

int main()
{

	int T;

	cin >> T;

	for (int i = 0; i < T; i++) {

		cin >> M >> N >> K;

		for (int j = 0; j < M; j++) {
			cin >> matrix[j];
		}

		int maxRC = max(M, N);

		for (int j = 0; j <= 1; j++) {
			for (int k = 0; k < maxRC; k++) {
				for (int l= 0; l <=1; l++) {
					for (int m = 0; m < maxRC; m++) {
						for (int n = 0; n <= K; n++) {
							dp[j][k][l][m][n] = -1;
						}
					}
				}
			}
		}

      cout << "Case #" << i+1 << ": " << Calc(0, 0, 1, 0, K) << endl;
   }
 
   return 0;
}
