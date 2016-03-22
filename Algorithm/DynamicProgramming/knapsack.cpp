#ifdef LOCAL
#include "task_selection.h"
#else
#define knapsack
#endif

#ifdef knapsack

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

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

#ifdef _DEBUG
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

using namespace std;

typedef long long ll;
typedef long double ld;
#define mp make_pair
#define write(a, c) for (auto i : a) cout << i << c;
#define all(a) (a).begin(), (a).end()

const int K = 18;
const ll MAXN = 4e5;
const int INF = 2e9 + 1;
const ll LONG_INF = 8e18;
const ll MOD = 1e9 + 7;
const ld e = 1e-9;
const ll C = 500;
const ll dx[4] = { -1, 0, 1, 0 };
const ll dy[4] = { 0, 1, 0, -1 };

int dp[(int)1e3 + 10][(int)1e4 + 10];
int prev[(int)1e3 + 10][(int)1e4 + 10];
int mass[MAXN];
int cost[MAXN];
int m, n;

int main() {
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#else   
	freopen("knapsack.in ", "r", stdin);
	freopen("knapsack.out", "w", stdout);
#endif

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> mass[i + 1];
	}
	for (int i = 0; i < n; i++) {
		cin >> cost[i + 1];
	}

	int max_n = -INF, max_m = -INF;
	int max_dp = -INF;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (i != 0) {
				dp[i][j] = dp[i - 1][j];
				if (j >= mass[i] && dp[i][j] < dp[i - 1][j - mass[i]] + cost[i] && dp[i - 1][j - mass[i]] != -INF) {
					dp[i][j] = dp[i - 1][j - mass[i]] + cost[i];
				}
			}
			else if (j != 0) {
				dp[i][j] = -INF;
			}
			else {
				dp[i][j] = 0;
			}
			if (max_dp < dp[i][j]) {
				max_n = i;
				max_m = j;
				max_dp = dp[i][j];
			}
		}
	}



	vector<int> a;
	int j = max_m;
	int i = max_n;
	for (; i != 0; i--) {
		if (dp[i][j] != dp[i - 1][j]) {
			a.push_back(i);
			j -= mass[i];
		}
	}
	sort(all(a));
	cout << a.size() << endl;
	for (int i : a) {
		cout << i << " ";
	}
	cout << endl;

	wait();
	return 0;
}
#endif