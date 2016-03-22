#ifdef LOCAL
#include "task_selection.h"
#else
#define lis
#endif

#ifdef lis

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

int dp[MAXN];
int pre[MAXN];
int pos[MAXN];
int a[MAXN];
int n;

int main() {
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#else   
	freopen("lis.in ", "r", stdin);
	freopen("lis.out", "w", stdout);
#endif

	cin >> n;

	dp[0] = -INF;
	for (int i = 1; i < n; i++) {
		dp[i] = INF;
	}
	pos[0] = -1;

	ll ans = 1;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		int* p = lower_bound(dp, dp + n, a[i]);
		ll f = p - dp;
		ans = max(ans, f);
		dp[f] = a[i];
		pos[f] = i;
		pre[i] = pos[f - 1];
	}

	cout << ans << endl;
	int i = pos[ans];
	vector<int> r;
	while (i >= 0) {
		r.push_back(i);
		i = pre[i];
	}
	reverse(r.begin(), r.end());
	for (int i : r) {
		cout << a[i] << ' ';
	}
	cout << endl;


	wait();
	return 0;
}
#endif