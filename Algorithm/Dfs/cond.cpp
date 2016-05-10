#ifdef LOCAL
#include "task_selection.h"
#include "checker.h"
#else
#define cond task
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

namespace cond {

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

	int n, m;
	vector<int> ans;
	vector<int> g[MAXN];
	vector<int> ag[MAXN];
	int used[MAXN];

	void dfs(int v) {
		used[v] = 1;
		for (auto i : g[v]) {
			if (!used[i]) {
				dfs(i);
			}
		}
		used[v] = 2;
		ans.push_back(v);
	}

	int ans_color[MAXN];
	void dfs2(int v, int color) {
		ans_color[v] = color;
		for (auto i : ag[v]) {
			if (!ans_color[i]) {
				dfs2(i, color);
			}
		}
	}

	int main() {
		cin >> n >> m;
		for (int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;
			a--, b--;
			g[a].push_back(b);
			ag[b].push_back(a);
		}

		for (int i = 0; i < n; i++) {
			if (!used[i]) {
				dfs(i);
			}
		}
		reverse(all(ans));

		int color = 0;
		for (auto i : ans) {
			if (!ans_color[i]) {
				dfs2(i, ++color);
			}
		}

		cout << color << endl;
		for (int i = 0; i < n; i++) {
			cout << ans_color[i] << ' ';
		}
		cout << endl;

		return 0;
	}
}

#if defined(cond) && !defined(checker)
int main() {
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	while (!cin.eof()) {
		cond::main();
	}
	cond::wait();
#else   
	freopen("cond.in ", "r", stdin);
	freopen("cond.out", "w", stdout);
	cond::main();
#endif
	return 0;
}
#endif