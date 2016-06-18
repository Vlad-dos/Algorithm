#ifdef LOCAL
#include "task_selection.h"
#include "checker.h"
#else
#define negcycle task
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

namespace negcycle {

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

	struct edge {
		int a, b, w;

		edge(int a, int b, int w)
			: a(a),
			b(b),
			w(w) {}
	};

	int n, m;
	vector<edge> graph;
	int dist[MAXN];
	int last_update[MAXN];


	int main() {
		cin >> n;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int w;
				cin >> w;
				if (w != 1e9) {
					graph.emplace_back(i, j, w);
				}
			}
		}

		for (int i = 0; i < n; i++) {
			dist[i] = INF;
		}

		dist[0] = 0;
		
		bool f = false;
		int v = 0;
		for (int i = 0; i < n; i++) {
			for (edge& j : graph) {
				if (dist[j.b] > dist[j.a] + j.w) {
					if (i == n - 1) {
						f = true;
						v = j.b;
					} else {
						dist[j.b] = dist[j.a] + j.w;
					}
					last_update[j.b] = j.a;
				}
			}
		}

		if (f) {
			cout << "YES" << endl;
			vector<int> stack;
			vector<int> use(n);
			
			int p = v;
			int size = 0;
			while (!use[p]) {
				size++;
				use[p] = true;
				stack.push_back(p);
				p = last_update[p];
			}

			vector<int> answer;
			answer.push_back(p + 1);
			while (stack.back() != p) {
				answer.push_back(stack.back() + 1);
				stack.pop_back();
			}
			answer.push_back(p + 1);
			cout << answer.size() << endl;
			write(answer, ' ');
			cout << endl;
		} else {
			cout << "NO" << endl;
		}

		return 0;
	}
}

#if defined(negcycle) && !defined(checker)
int main() {
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	while (!cin.eof()) {
		negcycle::main();
	}
	negcycle::wait();
#else   
	freopen("negcycle.in ", "r", stdin);
	freopen("negcycle.out", "w", stdout);
	negcycle::main();
#endif
	return 0;
}
#endif