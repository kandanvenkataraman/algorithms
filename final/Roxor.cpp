// topcoder SRM 216 Div 1 level 3
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace std;


class Roxor {
public:
	vector <int> play(vector <int> piles) {
		vector<int> result;
		int n = piles.size();
		vector<int> val(n, 0);
		for (int i = n-2; i >= 0; i--) {
			int l = -1;
			bool found = false;
			do {
				l++;
				found = false;
				for (int j = i+1; j <= n-1; j++) {
					if (found)
						break;
					for (int k = j; k <= n-1; k++) {
						if ((val[j] ^ val[k]) == l) {
							found = true;
							break;
						}
					}
				}
			} while (found);
			val[i] = l;
		}
		int r = 0;
		for (int i = 0; i < n-1; i++) {
			if (piles[i]%2 == 1)
				r = (r ^ val[i]);
		}
		if (r == 0)
			return result;
		for (int i = 0; i < n-1; i++) {
			if (piles[i] == 0)
				continue;
			for (int j = i+1; j < n; j++) {
				for (int k = j; k < n; k++) {
					if ((r ^ val[i]) == (val[j] ^ val[k])) {
						result.push_back(i);
						result.push_back(j);
						result.push_back(k);
						return result;
					}
				}
			}
		}
		return result;
	}
};


