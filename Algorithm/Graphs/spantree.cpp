#ifdef LOCAL
#include "task_selection.h"
#include "checker.h"
#else
#define spantree task
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

namespace spantree {

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

	int color[MAXN];
	int parent[MAXN];

	int get_color(int a) {
		if (parent[a] != a)
			parent[a] = get_color(parent[a]);
		return parent[a];
	}

	void merge(int a, int b) {
		a = get_color(a);
		b = get_color(b);
		parent[a] = b;
	}

	struct edge {
		int a, b;
		int w;

		edge() {};
		edge(int a, int b, int w)
			: a(a),
			b(b),
			w(w) {}
	};

	vector<edge> edges;
	int n;
	pair<int, int> points[MAXN];

	int dist(pair<int, int> a, pair<int, int> b) {
		return ((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
	}

	int main() {
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> points[i].first >> points[i].second;;
		}

		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				edges.emplace_back(i, j, dist(points[i], points[j]));
			}
		}


		sort(all(edges), [](edge a, edge b) {
			return a.w < b.w;
		});

		for (int i = 0; i < n; i++) {
			parent[i] = i;
		}

		double ans = 0;
		for (auto i : edges) {
			if (get_color(i.a) != get_color(i.b)) {
				ans += sqrt(static_cast<double>(i.w));
				merge(i.a, i.b);
			}
		}

		cout.precision(15);
		cout << fixed << ans << endl;

		return 0;
	}
}

#if defined(spantree) && !defined(checker)
int main() {
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	while (!cin.eof()) {
		spantree::main();
	}
	spantree::wait();
#else   
	freopen("spantree.in ", "r", stdin);
	freopen("spantree.out", "w", stdout);
	spantree::main();
#endif
	return 0;
}
#endif