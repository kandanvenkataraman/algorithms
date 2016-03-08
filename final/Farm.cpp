// facebook hacker cup round 3 2016
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <iomanip>
 
using namespace std;
 
double PL(int N, double PA, double PB)
{
	double d = fabs(PA-PB);

	if (d == 1) {
		if (PA > PB)
			return 1.0;
		return 0.0;
	}

	double dn = pow(d, N-1);

	if (PA > PB)
		return (PB*((1-dn)/(1-d))) + (dn*PA);

	return (PA*((1-dn)/(1-d))) + (dn*PA);
}

int main()
{
   int T;
 
   cin >> T;
 
   cout << setprecision(9) << fixed;
 
   for (int i = 0; i < T; i++) {

		int N;

		double WA, WB, LA, LB;

		cin >> N >> WA >> WB >> LA >> LB;

		double val = 0.0;

		if (N == 1)
			val = WA;
		else if (WA == WB)
			val = WA;
		else if (LA == LB)
			val = (LA*max(WA, WB)) + ((1-LA)*min(WA,WB));
		else {
			double c = PL(N-1, LA, LB);
			val = (c*max(WA, WB)) + ((1-c)*min(WA,WB));
		}
 
      cout << "Case #" << i+1 << ": " << val << endl;
   }
 
   return 0;
}
