// facebook hacker cup round 2 2016
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>
#include <iomanip>
#include <limits.h>
 
using namespace std;

int K, P;
int cost[1000][30];
int root;
int dp[1000][31][31];
int M[30][30];
 
struct Elem {
	int idx;
	bool isX;
	int parentIdx;

	Elem(int i, bool b, int p) : idx(i) , isX(b) , parentIdx(p) {}
};

int hungarian(int N)
{
   int C = 0;
 
   // we seek to minimize the number of point we give away
   for (int i = 0; i < N; i++) {
      int m = INT_MAX;
      for (int j = 0; j < N; j++)
         m = min(m, M[i][j]);
      C += m;
      for (int j = 0; j < N; j++)
         M[i][j] -= m;
   }
 
   for (int i = 0; i < N; i++) {
      int m = INT_MAX;
      for (int j = 0; j < N; j++)
         m = min(m, M[j][i]);
      C += m;
      for (int j = 0; j < N; j++)
         M[j][i] -= m;
   }
 
   int MX[30];
   int MY[30];
 
   for (int i = 0; i < N; i++)
      MX[i] = MY[i] = -1;
 
   int matchCount = 0;
 
   while (matchCount < N) {
 
      queue<Elem> Q;
 
      vector<bool> S(N, false);
      vector<bool> T(N, false);
      vector<bool> VS(N, false);
      vector<bool> VT(N, false);
      int PX[30];
      int PY[30];
 
      for (int i = 0; i < N; i++) {
         PX[i] = PY[i] = -1;
         if (MX[i] == -1) {
				S[i] = true;
            Q.push(Elem(i, true, -1));
         }
      }
 
      int freeY = -1;
 
start:
      while (!Q.empty()) {
         Elem x = Q.front();
         Q.pop();
 
			if (x.isX) {
				if (VS[x.idx])
            	continue;
				VS[x.idx] = true;
				PX[x.idx] = x.parentIdx;
				S[x.idx] = true;	
				for (int i = 0; i < N; i++) {
					if (M[x.idx][i] == 0 && MX[x.idx] != i)
						Q.push(Elem(i, false, x.idx));
				}
			}
			else {
				if (VT[x.idx])
            	continue;
				VT[x.idx] = true;
				PY[x.idx] = x.parentIdx;
				if (MY[x.idx] == -1) {
					freeY = x.idx;
					break;
				}
				else {
					T[x.idx] = true;
					Q.push(Elem(MY[x.idx], true, x.idx));
				}
			}
      }
 
      int count = 0;
      int curr = freeY;
      if (freeY != -1) {
         // augment match path to matches;
 
         while (curr != -1) {
 
            int prev = (count %2 == 0 ? PY[curr] : PX[curr]);
            if (prev == -1)
               break;
 
            if (count %2 == 0) {
               MY[curr] = prev;
               MX[prev] = curr;
            }
 
            curr = prev;
            count++;
         }
         matchCount++;
         continue;
      }

  		int theta = INT_MAX;

      for (int i = 0; i < N; i++)  {
         for (int j = 0; j < N; j++) {
            if (S[i] && !T[j])
               theta = min(theta, M[i][j]);
         }
      }
 
      for (int i = 0; i < N; i++)  {
         for (int j = 0; j < N; j++) {
				if (S[i])
               M[i][j] -= theta;
				if (T[j])
               M[i][j] += theta;
				else if (S[i] && M[i][j] == 0) {
					Q.push(Elem(j, false, i));
				}
         }
      }
 
      for (int i = 0; i < N; i++)  {
			if (S[i])
				C += theta;
			if (T[i])
				C -= theta;
		}
		goto start;
   }
 
   return C;
}

int Calc(vector<vector<int> > &tree, int idx, int myCol, int parentCol)
{
	int &r = dp[idx][myCol][parentCol];
	if (r != -1)
		return r;

	r = cost[idx][myCol] + P;

	for (int i = 0; i < tree[idx].size(); i++) {
		int val = 0;
		for (int j = 0; j < K; j++) {
			if (j == 0)
				val = Calc(tree, tree[idx][i], 0, myCol);
			else
				val = min(val, Calc(tree, tree[idx][i], j, myCol));
		}
		r += val;
	}

	int numCol = K;
	if (parentCol != K)
		numCol--;

	if (numCol >= tree[idx].size()) {

		for (int i = 0; i < tree[idx].size(); i++) {
			int j = 0;
			for (int k = 0; k < K; k++) {
				if (k == parentCol)
					continue;
				M[i][j] = Calc(tree, tree[idx][i], k, myCol);
				j++;
			}
		}

		for (int i = tree[idx].size(); i < numCol; i++) {
			for (int j = 0; j < numCol; j++) {
				M[i][j] = 0;
			}
		}

		r = min(r, cost[idx][myCol] + hungarian(numCol));
	}

	return r;
}

int main()
{
   int T;
 
   cin >> T;

   for (int i = 0; i < T; i++) {

		int N;

		cin >> N >> K >> P;

		for (int j = 0; j < N; j++) {
			for (int k = 0; k < K; k++) {
				cin >> cost[j][k];
			}
		}

		int parent[1000];
		for (int j = 0; j < N; j++)
			parent[j] = -1;

		for (int j = 0; j < N-1; j++) {
			int a, b;
			cin >> a >> b;
			a--;b--;
			if (parent[a] == -1)
				parent[a] = b;
			else if (parent[b] == -1)
				parent[b] = a;
			else {
				int newParent = b;
				int oldParent = parent[a];
				while (a != -1) {
					parent[a] = newParent;
					newParent = a;
					a = oldParent;
					if (a != -1)
						oldParent = parent[a];
				}
			}
		}

		vector<vector<int> > tree(N);
		root = -1;
		for (int j = 0; j < N; j++) {
			if (parent[j] == -1)
				root = j;
			else 
				tree[parent[j]].push_back(j);
		}

		for (int j = 0; j < N; j++) {
			for (int k = 0; k <= K; k++) {
				for (int l = 0; l <= K; l++) {
					dp[j][k][l] = -1;	
				}
			}
		}

      int m = INT_MAX;
		for (int j = 0; j < K; j++)
			m = min(m, Calc(tree, root, j, K));

      cout << "Case #" << i+1 << ": " << m << endl;
   }
 
   return 0;
}

