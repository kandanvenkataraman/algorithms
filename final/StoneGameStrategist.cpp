// topcoder SRM 309 Div 1 level 3
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
#include <string>

using namespace std;


class StoneGameStrategist {
public:
	string play(vector <int> piles) {
	
		int n = piles.size();
		vector<int> diff(n, 0);
		diff[0] = piles[0];
		for (int i = 1; i < n; i++) {
			diff[i] = piles[i] - piles[i-1];
		}
		int val = 0;
		for (int i = n-1; i >= 0; i = i-2) {
			val = val ^ diff[i];
		}
		if (val == 0)
			return string("YOU LOSE");
		int s = 0;
		int k = -1;
		for (int i = 0; i < n; i++) {
			if (i%2 == (n-1)%2) {
				int num = val ^ diff[i];
				if (num < diff[i]) {
					if (k == -1 || s > (diff[i] - num)) {
						k = i;
						s = diff[i] - num;
					}
				}
			}
			else {
				int num = val ^ diff[i+1];
				if (num > diff[i+1] && diff[i] >= (num - diff[i+1])) {
					if (k == -1 || s > (num - diff[i+1])) {
						k = i;
						s = num - diff[i+1];
					}
				}
			}	
		}				
		return string("TAKE " + to_string(s) + " STONES FROM PILE " + to_string(k));
	}
};
