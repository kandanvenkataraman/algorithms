// topcoder SRM 211 Div 1 level 2
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

using namespace std;

struct Point {
	int x;
	int y;
	
	Point(int a, int b) : x(a), y(b) {}
};
	

struct Rect {
	int row1;
	int col1;
	int row2;
	int col2;
};


class grafixMask {
	vector<Rect> rects;
	vector<vector<int> > matrix;
	

		
	int getArea(const Point &s) {
	
		
		vector<Point> v;
		queue<Point> q;
		
		q.push(s);
		
		while (!q.empty()) {
		
			Point p = q.front();
			q.pop();
			
			if (p.x < 0 || p.x >= 400)
				continue;
				
			if (p.y < 0 || p.y >= 600)
				continue;
			
			if (matrix[p.x][p.y] != 0)
				continue;
				
			matrix[p.x][p.y] = 1;
				
			v.push_back(p);
			
			q.push(Point(p.x-1, p.y));
			q.push(Point(p.x+1, p.y));
			q.push(Point(p.x, p.y-1));
			q.push(Point(p.x, p.y+1));
			
		}
		
		return v.size();
	}
	
public:
	vector <int> sortedAreas(vector <string> rectangles) {
		for (int i = 0 ;i < 400; i++)
			matrix.push_back(vector<int>(600, 0));
		for (int i = 0; i < rectangles.size(); i++) {
			string s = rectangles[i];
			stringstream sst(s);
			Rect r;
			sst >> r.row1 >> r.col1 >> r.row2 >> r.col2;
			rects.push_back(r);
		 }
		 for (int i = 0; i < 400; i++) {
		 	for (int j = 0; j < 600; j++) {
		 		bool found = false;
		 		for (int k = 0; k < rects.size(); k++) {
		 			if (rects[k].row1 <= i && rects[k].row2 >= i && rects[k].col1 <= j && rects[k].col2 >= j) {
		 				found = true;
		 				break;
		 			}
		 		}
		 		if (found)
		 			matrix[i][j] = 2;
		 	}
		 }
		 vector<int> out;
		 for (int i = 0; i < 400; i++) {
		 	for (int j = 0; j < 600; j++) {
		 		if (matrix[i][j] != 0)
		 			continue;
		 		out.push_back(getArea(Point(i,j)));
		 	}
		 }
		 sort(out.begin(), out.end());
		 return out;
	}
};
