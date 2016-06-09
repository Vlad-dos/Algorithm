#if defined(LOCAL) || defined(LINUX)
#include "task_selection.h"
#include "checker.h"
#else
#define avia2 task
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

namespace avia2 {

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
	const ll MAXN = 2000;
	const int INF = 2e9 + 1;
	const ll LONG_INF = 8e18;
	const ll MOD = 1e9 + 7;
	const ld e = 1e-9;
	const ll C = 500;
	const ll dx[4] = { -1, 0, 1, 0 };
	const ll dy[4] = { 0, 1, 0, -1 };

    struct edge {
       int a, b, w;
       edge(int a, int b, int w) : a(a), b(b), w(w) {}
    };
    vector<edge> edges;

    int parent[MAXN];
    int k;
    int get(int i) {
        if (parent[i] != i)
            parent[i] = get(parent[i]);
        return parent[i];
    }

    void merge(int a, int b) {
        a = get(a);
        b = get(b);
        if (a != b) {
            k--;
            parent[a] = b;
        }
    }

	int main() {
        int n;
        scanf("%d", &n);
        k = n;

        for (int i = 0; i < n; i++) { 
            parent[i] = i;
            for (int j = 0; j < n; j++) {
                int w;
                scanf("%d", &w);
                edges.push_back(edge(i, j, w));
            }
        }

        sort(all(edges), [](edge a, edge b) {
                return a.w < b.w;
            });

        for (auto i : edges) {
            merge(i.a, i.b);
            if (k == 1) {
                cout << i.w << endl;
                return 0;
            }
        }

        cout << "WHAT???" << endl;

		return 0;
	}
}

#if (defined(avia2) && !defined(checker)) || defined(LINUX)
int main() {
#if defined(LOCAL) || defined(LINUX)
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

    avia2::main();
	avia2::wait();
#else   
	freopen("avia.in ", "r", stdin);
	freopen("avia.out", "w", stdout);
	avia2::main();
#endif
	return 0;
}
#endif
