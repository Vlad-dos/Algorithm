#ifdef LOCAL
#include "task_selection.h"
#include "checker.h"
#else
#define components task
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

namespace components {

#if defined(LOCAL)
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

	int n, m;
	vector<int> g[MAXN];
	int color[MAXN];

	void dfs(int v, int c) {
		color[v] = c;
		for (auto i : g[v]) {
			if (!color[i])
				dfs(i, c);
		}
	}

	int main() {
		cin >> n >> m;
		for (int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;
			a--, b--;
			g[a].push_back(b);
			g[b].push_back(a);
		}
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			if (!color[i])
				dfs(i, ++cnt);
		}

		cout << cnt << endl;
		for (int i = 0; i < n; i++) {
			cout << color[i] << ' ';
		}
		cout << endl;

		return 0;
	}
}

#if defined(components) && !defined(checker)
int main() {
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	while (!cin.eof()) {
		components::main();
	}
	components::wait();
#else   
	freopen("components.in ", "r", stdin);
	freopen("components.out", "w", stdout);
	components::main();
#endif
	return 0;
}
#endif