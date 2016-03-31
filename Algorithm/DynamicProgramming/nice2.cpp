#ifdef LOCAL
#include "task_selection.h"
#include "checker.h"
#else
#define nice2 task
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

namespace nice2 {

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

	const int K = 20;
	const ll MAXN = (1 << K);
	const int INF = 2e9 + 1;
	const ll LONG_INF = 8e18;
	const unsigned int MOD = (1 << 30) + 1;
	const ld e = 1e-9;
	const ll C = 500;
	const ll dx[4] = { -1, 0, 1, 0 };
	const ll dy[4] = { 0, 1, 0, -1 };

	unsigned int dp[MAXN][K];

	int get(int mask, int pos) {
		return (mask >> pos) & 1;
	}
	int n, m;

	int main() {
		//int M, N;
		cin >> n >> m;
		//M = m;
		//N = n;
		if (n > m) {
			swap(n, m);
		}

		if (n == 1) {
			int ans = 1;
			for (int i = 0; i < m; i++) {
				ans *= 2;
				ans %= MOD;
			}
			cout << ans << endl;
			//cout << "dp[" << M << "]" << "[" << N << "]" << " = " << ans << ";" << endl;
			return 0;
		}

		for (int col = 0; col < m; col++) {
			for (int line = 0; line < n; line++) {
				for (int mask = 0; mask < (1 << (n + 2)); mask++) {
					if (col == 0) {
						dp[mask][line] = ((mask & ((1 << (n - line + 1)) - 1)) == 0);
					}
					else if (col == 1 && line == 0) {
						dp[mask][line] = !get(mask, 0);
					}
					else if (line == 0) {
						dp[mask][line] = dp[(mask << 1) % (1 << (n + 2)) + 0][n - 1] + dp[(mask << 1) % (1 << (n + 2)) + 1][n - 1];
						dp[mask][line] %= MOD;
					}
					else {
						if ((get(mask, 0) + get(mask, 1) + get(mask, n) + get(mask, n + 1)) % 4) {
							dp[mask][line] = dp[(mask << 1) % (1 << (n + 2)) + 0][line - 1] + dp[(mask << 1) % (1 << (n + 2)) + 1][line - 1];
							dp[mask][line] %= MOD;
						}
						else {
							dp[mask][line] = 0;
						}
					}
				}
			}
		}

		unsigned int ans = 0;
		for (int mask = 0; mask < (1 << (n + 2)); mask++) {
			ans += dp[mask][n - 1];
			ans %= MOD;
		}

		cout << ans << endl;
		//cout << "dp[" << M << "]" << "[" << N << "]" << " = " << ans << ";" << endl;

		return 0;
	}
}

#if defined(nice2) && !defined(checker)
int main() {
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	while (!cin.eof()) {
		nice2::main();
		cerr << "Done " << nice2::n << ' ' << nice2::m << endl;
	}
	nice2::wait();
#else   
	freopen("nice.in ", "r", stdin);
	freopen("nice.out", "w", stdout);
	nice2::main();
#endif
	return 0;
}
#endif