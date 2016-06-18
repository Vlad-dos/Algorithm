#ifdef LOCAL
#include "task_selection.h"
#include "checker.h"
#else
#define mindiff task
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

namespace mindiff {

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
	const ll dx[4] = {-1, 0, 1, 0};
	const ll dy[4] = {0, 1, 0, -1};

	int color[MAXN];
	int parent[MAXN];
	int k;

	int get_color(int a) {
		if (parent[a] != a)
			parent[a] = get_color(parent[a]);
		return parent[a];
	}

	void merge(int a, int b) {
		a = get_color(a);
		b = get_color(b);
		if (a != b) {
			parent[a] = b;
			k--;
		}
	}

	struct edge {
		int a, b, w;

		edge() {};
		edge(int a, int b, int w)
			: a(a),
			b(b),
			w(w) {}
	};

	edge edges[MAXN];
	int n, m;

	int main() {
		cin >> n >> m;
		for (int i = 0; i < m; i++) {
			int a, b, w;
			cin >> a >> b >> w;
			a--, b--;
			edges[i] = edge(a, b, w);
		}

		sort(edges, edges + m, [](edge a, edge b) {
			return a.w < b.w;
		});

		int super_ans = INF;
		bool f = false;
		for (int start = 0; start < m; start++) {
			for (int i = 0; i < n; i++) {
				parent[i] = i;
			}
			k = n;
			int ans = -INF;
			int ans2 = INF;
			for (int i = start; i < m; i++) {
				if (get_color(edges[i].a) != get_color(edges[i].b)) {
					ans = max(edges[i].w, ans);
					ans2 = min(edges[i].w, ans2);
				}
				merge(edges[i].a, edges[i].b);
			}
			if (k == 1) {
				f = true;
				super_ans = min(super_ans, ans - ans2);
			}
		}

		if (f) {
			cout << "YES" << endl;
			cout << super_ans << endl;
		} else {
			cout << "NO" << endl;
		}

		return 0;
	}
}

#if defined(mindiff) && !defined(checker)
int main() {
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

		mindiff::main();
	mindiff::wait();
#else   
	freopen("mindiff.in ", "r", stdin);
	freopen("mindiff.out", "w", stdout);
	mindiff::main();
#endif
	return 0;
}
#endif