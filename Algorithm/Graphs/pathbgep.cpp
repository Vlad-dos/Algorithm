#ifdef LOCAL
#include "task_selection.h"
#include "checker.h"
#else
#define pathbgep task
#endif

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cmath>
#include <fstream>
#include <queue>
#include <stack>
#include <cassert>
#include <complex>
#include <bitset>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <list>

#include <forward_list>
#include <numeric>
#include <functional>
#include <initializer_list>

using namespace std;

namespace pathbgep {

#if defined(_DEBUG)
#define debug printf
#define reader scanf
#define error(...) fprintf(stderr,__VA_ARGS__)

	void wait() {
		fclose(stdin);
		fclose(stdout);
		freopen("CON", "r", stdin);
		freopen("CON", "w", stdout);
		system("pause");
	}
#else
#define debug ;
#define reader ;
#define error ;
	void wait() {}
#endif

	typedef long long ll;
	typedef long double ld;
#define mp make_pair
#define write(a, c) for (auto i : a) cout << i << c;
#define all(a) (a).begin(), (a).end()

	const int K = 18;
	const ll MAXN = 1e6;
	const int INF = 2e9 + 1;
	const ll LONG_INF = 8e18;
	const ll MOD = 1e9 + 7;
	const ld e = 1e-9;
	const ll C = 500;
	const ll dx[4] = { -1, 0, 1, 0 };
	const ll dy[4] = { 0, 1, 0, -1 };

	struct edge {
		int a, b, w;

		edge(int a, int b, int w)
			: a(a),
			b(b),
			w(w) {}
	};

	int n, m;
	vector<edge> g[MAXN];
	unsigned int dist[MAXN];


	struct cmp {
		bool operator()(int x, int y) const {
			return (dist[x] < dist[y] || (dist[x] == dist[y] && x < y));
		}
	};
	set<int, cmp> vert;

	void dijkstra(int s) {
		for (int i = 0; i < n; i++) {
			dist[i] = INF;
		}

		dist[s] = 0;
		vert.insert(s);

		while (!vert.empty()) {
			int u = *vert.begin();
			vert.erase(u);
			if (dist[u] == INF) {
				continue;
			}
			for (auto i : g[u]) {
				if (i.b != u && dist[i.b] > dist[i.a] + i.w) {
					vert.erase(i.b);
					dist[i.b] = dist[i.a] + i.w;
					vert.insert(i.b);
				}
			}
		}
	}

	int main() {
		scanf("%d %d", &n, &m);

		for (int i = 0; i < m; i++) {
			int a, b, w;
			scanf("%d %d %d", &a, &b, &w);
			a--, b--;
			g[a].emplace_back(a, b, w);
			g[b].emplace_back(b, a, w);
		}

		dijkstra(0);
	
		for (int i = 0; i < n; i++) {
			printf("%u ", dist[i]);
		}
		printf("\n");

		return 0;
	}
}

#if defined(pathbgep) && !defined(checker)
int main() {
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

		pathbgep::main();
	pathbgep::wait();
#else   
	freopen("pathbgep.in ", "r", stdin);
	freopen("pathbgep.out", "w", stdout);
	pathbgep::main();
#endif
	return 0;
}
#endif