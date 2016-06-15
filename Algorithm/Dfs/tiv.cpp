#if defined(LOCAL) && !defined(LINUX)
#include "task_selection.h"
#include "checker.h"
#else
#define tiv task
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

namespace tiv {

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
	const ll MAXN = 70;
	const int INF = 2e9 + 1;
	const ll LONG_INF = 8e18;
	const ll MOD = 1e9 + 7;
	const ld e = 1e-9;
	const ll C = 500;
	const ll dx[4] = { -1, 0, 1, 0 };
	const ll dy[4] = { 0, 1, 0, -1 };

	int n;
	vector<int> g[MAXN];
	string s;
	string last;
    bool lead[MAXN];
    bool cant_lead[MAXN];

	vector<int> ans;
	int a[MAXN];
	int used[MAXN];

    vector<string> input;

	void dfs(int v) {
		used[v] = 1;
		for (auto i : g[v]) {
			if (used[i] == 1) {
				cout << "No" << endl;
				exit(0);
			}
			if (!used[i])
				dfs(i);
		}
		used[v] = 2;
		ans.push_back(v);
	}

	int main() {
		cin >> n;
		last = "";
		for (int i = 0; i < n; i++) {
			cin >> s;
            input.push_back(s);
            if (s.size() > 1) {
                lead[s[0] - 'a'] = true;
            }
            if (s == last || s.size() < last.size()) {
                cout << "No" << endl;
                return 0;
            }
			if (s.size() == last.size()) {
				bool f = false;
 				for (size_t i = 0; i < s.size(); i++) {
					if (s[i] != last[i]) {
						int a = s[i] - 'a';
						int b = last[i] - 'a';
						g[b].push_back(a);
                        cant_lead[a] = true;
						break;
					}
				}
				if (!f) {
					cout << "No" << endl;
					exit(0);
				}
			}
			last = s;
		}

        int zero = 0;
        bool f = false;
        for (int i = 0; i < 26; i++) {
            if (!lead[i] && !cant_lead[i]) {
                f = true;
                used[i] = 2;
                zero = i;
                break;
            }
        }

        if (!f) {
            cout << "No" << endl;
            return 0;
        }

		for (int i = 0; i < 26; i++) {
			if (!used[i]) {
				dfs(i);
			}
		}

		reverse(all(ans));
		cout << "Yes" << endl;
		int cnt = 1;
		for (auto i : ans) {
			a[i] = cnt++;
		}
        a[zero] = 0;

		for (int i = 0; i < 26; i++) {
			cout << a[i] << ' ';
		}
		cout << endl;

        vector<int> result;
        for (auto s : input) {
            for (auto& i : s) {
                i = char(a[i - 'a'] + '0');
            }
            result.push_back(atoi(s.c_str()));
        }

        /* int last_int = -1; */
        /* for (auto i : result) { */
        /*     assert(i > last_int); */
        /*     last_int = i; */
        /* } */

		return 0;
	}
}

#if (defined(tiv) && !defined(checker))
int main() {
#if defined(LOCAL) || defined(LINUX)
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

    tiv::main();
	tiv::wait();
#else   
	freopen("tiv.in ", "r", stdin);
	freopen("tiv.out", "w", stdout);
	tiv::main();
#endif
	return 0;
}
#endif
