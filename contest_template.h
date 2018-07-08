#include <bits/stdc++.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

typedef long long int lli;
typedef pair<int, int> ii;

template<class T>bool chmax(T &a, const T &b) { if( a < b ) { a = b; return 1; } return 0;}
template<class T>bool chmin(T &a, const T &b) { if( b < a ) { a = b; return 1; } return 0;}

#ifdef LOCAL
	#define eprintf(...) printf(__VA_ARGS__)
#else
	#define eprintf(...) 1
#endif

#define ROUNDUP(a, b) 		( ((a) + ((b) - 1) ) / (b))
#define SET_ZERO(a)	 		( memset((a), 0, sizeof(a)))
#define SET_NUM_ARRAY(a,b)	( memset((a), b, sizeof(a)))
//#define int long long int //dont forget to change int to signed

// situational
lli C[51][51];
void combinate_init(int n) {
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= i; j++) {
			if (j == 0 || i == j) {
				C[i][j] = 1;
			} else {
				C[i][j] = (C[i-1][j-1] + C[i-1][j]);
			}
		}
	}
}

template<typename T>T gcd(T a, T b) {
	T c;
	if (a < b) {
		a += b;
		b = a - b;
		a -= b;
	}
	while (b != 0) {
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}

int count8bit(unsigned char v) {
	unsigned count = (v & 0x55) + ((v >> 1) & 0x55);
	count = (count & 0x33) + ((count >> 2) & 0x33);
	return (count & 0x0f) + ((count >> 4) & 0x0f);
}

int count16bit(unsigned short v) {
	unsigned short count = (v & 0x5555) + ((v >> 1) & 0x5555);
	count = (count & 0x3333) + ((count >> 2) & 0x3333);
	count = (count & 0x0f0f) + ((count >> 4) & 0x0f0f);
	return (count & 0x00ff) + ((count >> 8) & 0x00ff);
}

int count32bit(unsigned v) {
	unsigned count = (v & 0x55555555) + ((v >> 1) & 0x55555555);
	count = (count & 0x33333333) + ((count >> 2) & 0x33333333);
	count = (count & 0x0f0f0f0f) + ((count >> 4) & 0x0f0f0f0f);
	count = (count & 0x00ff00ff) + ((count >> 8) & 0x00ff00ff);
	return (count & 0x0000ffff) + ((count >> 16) & 0x0000ffff);
}

// int count64bit(unsigned __int64 v) {
// 	unsigned __int64 count = (v & 0x5555555555555555) + ((v >> 1) & 0x5555555555555555);
// 	count = (count & 0x3333333333333333) + ((count >> 2) & 0x3333333333333333);
// 	count = (count & 0x0f0f0f0f0f0f0f0f) + ((count >> 4) & 0x0f0f0f0f0f0f0f0f);
// 	count = (count & 0x00ff00ff00ff00ff) + ((count >> 8) & 0x00ff00ff00ff00ff);
// 	count = (count & 0x0000ffff0000ffff) + ((count >> 16) & 0x0000ffff0000ffff);
// 	return (int)((count & 0x00000000ffffffff) + ((count >> 32) & 0x00000000ffffffff));
// }

template<class Abel> struct UnionFind{
	vector<int> par;
	vector<int> rank;
	vector<Abel> diff_weight;

	UnionFind(int n = 1, Abel SUM_UNITY = 0) {
		init(n, SUM_UNITY);
	}

	void init(int n = 1, Abel SUM_UNITY = 0) {
		par.resize(n);
		rank.resize(n);
		diff_weight.resize(n);
		for (int i = 0; i < n; ++i) {
			par[i] = i;
			rank[i] = 0;
		}
	}

	int root(int x) {
		if (par[x] == x) {
			return x;
		} else { 
			int r = root(par[x]);
			diff_weight[x] += diff_weight[par[x]];
			return par[x] = r;
		}
	}

	Abel weight(int x) {
		root(x);
		return diff_weight[x];
	} 

	Abel diff(int x, int y) {
		return weight(x) - weight(y);
	} 

	bool issame(int x, int y) {
		return root(x) == root(y);
	}

	bool merge(int x, int y, int w) {
		w += weight(x);
		w -= weight(x);
		x = root(x);
		y = root(y);
		if (x == y) return false;
		if (rank[x] < rank[y]) {
			swap(x,y);
			w = -w;
		}
		if (rank[x] == rank[y]) ++rank[x];
		par[y] = x;
		diff_weight[y] = w;
		return true;
	}
};