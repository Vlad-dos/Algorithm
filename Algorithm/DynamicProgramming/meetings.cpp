#ifdef LOCAL
#include "task_selection.h"
#include "checker.h"
#else
#define meetings task
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

namespace meetings {

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

	const int K = 21;
	const ll MAXN = 1 << K;
	const int INF = 2e9 + 1;
	const ll LONG_INF = 8e18;
	const ll MOD = 1e9 + 7;
	const ld e = 1e-9;
	const ll C = 500;
	const ll dx[4] = { -1, 0, 1, 0 };
	const ll dy[4] = { 0, 1, 0, -1 };

	bool dp[MAXN];
	int prev[MAXN];
	int delta[MAXN];
	pair<int, int> bounds[K];
	int move[K];
	int size[MAXN];
	int start;
	int n;
	int ans = -1;
	int pos = -1;

	bool in_bounds(int pos, pair<int, int> bounds) {
		return bounds.first <= pos && pos <= bounds.second;
	}

	bool in_mask(int i, int mask) {
		return (mask & (1 << i));
	}

	int main() {
		cin >> n >> start;
		for (int i = 0; i < n; i++) {
			cin >> bounds[i].first >> bounds[i].second;
			cin >> move[i];
}

		delta[0] = 0;
		size[0] = 0;
		for (int mask = 1; mask < (1 << n); mask++) {
			int pos = 0;
			for (int i = 0; i < n; i++) {
				if (in_mask(i, mask)) {
					pos = i;
				}
			}
			delta[mask] = delta[mask - (1 << pos)] + move[pos];
			size[mask] = size[mask - (1 << pos)] + 1;
		}

		dp[0] = 1;
		for (int mask = 1; mask < (1 << n); mask++) {
			dp[mask] = 0;
			for (int j = 0; j < n; j++) {
				if (in_mask(j, mask) && dp[mask - (1 << j)] && in_bounds(start + delta[mask - (1 << j)], bounds[j])) {
					dp[mask] = 1;
					prev[mask] = j;
				}
			}

			if (dp[mask] && size[mask] > ans) {
				ans = size[mask];
				pos = mask;
			}
		}

		if (ans < 0) {
			cout << 0;
		}
		else {
			cout << ans << endl;
			int mask = pos;
			vector<int> output;
			while (mask) {
				output.push_back(prev[mask] + 1);
				mask -= (1 << prev[mask]);
			}
			reverse(all(output));
			for (auto i : output) {
				cout << i << ' ';
			}
			cout << endl;
		}

		return 0;
	}
}

#if defined(meetings) && !defined(checker)
int main() {
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	while (!cin.eof()) {
		meetings::main();
	}
	meetings::wait();
#else   
	freopen("meetings.in ", "r", stdin);
	freopen("meetings.out", "w", stdout);
	meetings::main();
#endif
	return 0;
}
#endif