#if defined(LOCAL) || defined(LINUX)
#include "task_selection.h"
#include "checker.h"
#else
#define avia task
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
 
namespace avia {
 
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
 
    int n;
    int g[MAXN][MAXN];
    int used[MAXN];
 
    int dfs(int v, int seed, int max_edge) {
        int cnt = 1;
        used[v] = seed;
        for (int i = 0; i < n; i++) {
            if (used[i] != seed && i != v && g[i][v] <= max_edge) {
                cnt += dfs(i, seed, max_edge);
            }
        }
        return cnt;
    }
 
    int seed = 1;
    bool check(int m) {
        return dfs(0, seed++, m) == n;
    }
 
    vector<int> edges;
 
    int main() {
        scanf("%d\n", &n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &g[i][j]);
                edges.push_back(g[i][j]);
            }
        }
 
        sort(all(edges));
 
        cout << *lower_bound(edges.begin(), edges.end(), INF, [](int a, int b) {
            return check(a) < check(b);
        }) << endl;
 
        return 0;
    }
}
 
#if (defined(avia) && !defined(checker)) || defined(LINUX)
int main() {
#if defined(LOCAL) || defined(LINUX)
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
 
        avia::main();
    avia::wait();
#else   
    freopen("avia.in ", "r", stdin);
    freopen("avia.out", "w", stdout);
    avia::main();
#endif
    return 0;
}
#endif
