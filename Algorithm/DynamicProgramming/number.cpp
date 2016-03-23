#ifdef LOCAL
#include "task_selection.h"
#include "checker.h"
#else
#define number task
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

namespace number {

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
	const ll MAXN = 1e3 + 10;
	const int INF = 2e9 + 1;
	const ll LONG_INF = 8e18;
	const ll MOD = 1e9 + 7;
	const ld e = 1e-9;
	const ll C = 500;
	const ll dx[4] = { -1, 0, 1, 0 };
	const ll dy[4] = { 0, 1, 0, -1 };

	int dp[MAXN][MAXN];
	pair<int, int> prev[MAXN][MAXN];
	queue< pair<int, int> > q;
	int n;
	int pow[MAXN];

	int main() {
		cin.clear();
		cin >> n;
		if (n == 0)
			return 0;
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= n; j++) {
				dp[i][j] = INF;
				prev[i][j] = make_pair(INF, INF);
			}
		}
		dp[0][0] = 0;
		prev[0][0] = make_pair(-1, -1);

		q.push(make_pair(0, 0));
		while (!q.empty()) {
			pair<int, int> v = q.front();
			q.pop();
			for (int c = 0; c < 10; c++) {
				pair<int, int> newv = make_pair(v.first + c, (v.second * 10 + c) % n);
				if (dp[newv.first][newv.second] > dp[v.first][v.second] + 1) {
					dp[newv.first][newv.second] = dp[v.first][v.second] + 1;
					prev[newv.first][newv.second] = make_pair(c, v.second);
					q.push(newv);
				}
				else if (dp[newv.first][newv.second] == dp[v.first][v.second] + 1) {
					prev[newv.first][newv.second] = max(prev[newv.first][newv.second], make_pair(c, v.second));
				}
			}
		}

		pair<int, int> pos = make_pair(n, 0);
		assert(dp[pos.first][pos.second] != INF);
		int size = dp[pos.first][pos.second];
		vector<int> ans;
		int curr = 0;
		int sum = n;
		pow[0] = 1;
		for (int i = 1; i < size; i++)
			pow[i] = (pow[i - 1] * 10) % n;

		for (; size > 0; size--) {
			int j = 0;
			while (dp[sum - j][(curr - (j * pow[size - 1]) % n + n) % n] >= size)
				j++;
			ans.push_back(j);
			sum = sum - j;
			curr = (curr - (j * pow[size - 1]) % n + n) % n;
		}

		/*while (pos.first) {
			auto tmp = prev[pos.first][pos.second];
			ans.push_back(tmp.first);
			pos.first -= tmp.first;
			pos.second = tmp.second;
		}
		reverse(all(ans));*/
		for (int i : ans) {
			cout << i;
		}
		cout << endl;

		return 0;
	}
}

#if defined(number) && !defined(checker)
int main() {
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	while (!cin.eof()) {
		number::main();
	}
	number::wait();
#else   
	freopen("number.in ", "r", stdin);
	freopen("number.out", "w", stdout);
	number::main();
#endif
	return 0;
}
#endif