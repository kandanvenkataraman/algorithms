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


struct Edge {
	int from;
	int to;
	int capacity;
	int flow;

	Edge(int f, int t, int c) : from(f), to(t), capacity(c), flow(0) {}

	int other(int v) {
		if (v == from)
			return to;
		else if (v == to)
			return from;
		return -1;
	}

	int residualCapacityTo(int v)
	{
		if (v == to)
			return capacity-flow;
		else if (v == from)
			return flow;
		return 0;
	}
};

class MaxFlow {

	vector<Edge> E;
	vector<vector<int> > VE;

public:
	void setNumVertices(int n) {
		VE = vector<vector<int> >(n);
	}

	void addEdge(int f, int t, int c) {
		E.push_back(Edge(f, t, c));
		VE[f].push_back(E.size()-1);
		VE[t].push_back(E.size()-1);
	}

	// 0 is source, VE.size()-1 is sink
	bool hasAugmentPath(vector<int> &e) {

		int n = VE.size();
		vector<bool> marked(n, false);

		marked[0] = true;
		queue<int> q;
		q.push(0);

		while (!q.empty()) {

			int v = q.front();
			q.pop();
			if (v == n-1)
				return true;

			for (int i = 0; i < VE[v].size(); i++) {
				int other = E[VE[v][i]].other(v);
				if (marked[other] || E[VE[v][i]].residualCapacityTo(other) == 0)
					continue;
				marked[other] = true;
				q.push(other);
				e[other] = VE[v][i];
			}
		}

		return false;
	}

	int calcMaxFlow(void)
	{
		int m = 0;
		int n = VE.size();
		vector<int> e(n, -1);

		while (hasAugmentPath(e)) {

			int val = -1;
			int v = n-1;
			while (v != 0) {
				int other = E[e[v]].other(v);
				if (val == -1)
					val = E[e[v]].residualCapacityTo(v);
				else
					val = min(val, E[e[v]].residualCapacityTo(v));
				v = other;
			}
			m += val;
			v = n-1;
			while (v != 0) {
				int other = E[e[v]].other(v);
				if (E[e[v]].to == v)
					E[e[v]].flow += val;
				else
					E[e[v]].flow -= val;
				v = other;
			}
			v = n-1;
			e = vector<int>(n, -1);
		}

		return m;
	}
};

	
			



class RookAttack {
public:
	int howMany(int rows, int cols, vector <string> cutouts) {
	
		vector<vector<int> > matrix(rows, vector<int>(cols, 1));
		for (int i = 0; i < cutouts.size(); i++) {
			int f, t;
			stringstream ss(cutouts[i]);
			while (ss >> f) {
				ss >> t;
				matrix[f][t] = 0;
				if (ss.peek() == ',')
					ss.ignore();
			}
		}
		
		MaxFlow m;
		
		m.setNumVertices(2 + rows + cols);
		for (int i = 0; i < rows; i++)
			m.addEdge(0, i+1, 1);
		for (int i = 0; i < cols; i++)
			m.addEdge(rows+1+i, rows+cols+1, 1);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (matrix[i][j] == 1)
					m.addEdge(i+1, rows+1+j, 1);
			}
		}
		
		return m.calcMaxFlow();
			
	}
};

