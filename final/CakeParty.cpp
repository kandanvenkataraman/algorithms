// topcoder SRM 338 Div 1 level 3
#include <list>
#include <vector>
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


class CakeParty {

	string smallest(int a, int b) {
	
		if (a > b)
			return smallest(b, a);
			
		string sa = to_string(a);
		string sb = to_string(b);
		
		if (sa.length() == sb.length())
			return sa;	
			
		if (a == 0)
			return string(1, '0');
			
		if (sa.compare(to_string(1) + string(sa.length()-1, '0')) == 0)
			return sa;
			
		return string(to_string(1) + string(sa.length(), '0'));
	}
	
public:
	string makeMove(vector <int> pieces) {
	
		
		int m = -1;
		int n = -1;
		for (int i = 0; i < pieces.size(); i++) {
			
			if (m == -1 || pieces[i] > pieces[m]) {
				if (m != -1)
					n = m;
				m = i;	
			}
			else if (n == -1 || pieces[i] > pieces[n])
				n = i;
		}	
	
		int numMax = 0;
		int numSecondMax = 0;
		set<string> s;
		
		for (int i = 0; i < pieces.size(); i++) {
			if (pieces[i] == pieces[m]) {
				numMax++;
				s.insert(to_string(i));
			}
				
			if (n != -1 && pieces[i] == pieces[n])
				numSecondMax++;
		}
		
		if (numMax%2 == 0)
			return string("CAKE " + *s.begin() + " PIECES " + to_string(1));
			
		if (numMax > 1)
			return string("CAKE " + *s.begin() + " PIECES " + to_string(1));	
			
		if (numSecondMax%2 == 1)
			return string("CAKE " + to_string(m) + " PIECES " + to_string(pieces[m]-pieces[n]));	
			
		string ret = smallest(pieces[m]+1-pieces[n], pieces[m]);
		
		return string("CAKE " + to_string(m) + " PIECES " + ret);
		
		
	}
};
