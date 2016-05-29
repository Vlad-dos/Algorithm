#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
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
#include <functional>
#include <numeric>
#include <initializer_list>
#include <complex>
#include <bitset>
#include <deque>
#include <forward_list>
#include <list>
#include <unordered_set>
#include <unordered_map>

using namespace std;

typedef long long ll;
typedef double ld;

#define mp make_pair
#define write(a, c) for (auto i : a) cout << i << c;
#define all(a) a.begin(), a.end()

const ll MAXN = 1e6;
const int INF = 2e9 + 1;
const ll LONG_INF = 8e18;
const ll MOD = 1e9 + 7;
const ld e = 1e-9;
const ll C = 500;
const int dx[4] = { 0, 1, 0, -1 };
const int dy[4] = { 1, 0, -1, 0 };

struct edge {
    int a, b;
    bool same;
    int t;
    edge(int a, int b, bool same) : a(a), b(b), same(same) {
        int static time = 0;
        t = time++;
    };
};

int n, m;
vector<edge> g[MAXN];
int used[MAXN];
int color[MAXN];

bool dfs(int v, int time, int seed) {
    /* cout << "Dfs " << v << ' ' << time << ' ' << seed << endl; */
    used[v] = seed;
    bool correct = true;
    for (auto& i : g[v]) {
        if (i.t <= time) {
            if (used[i.b] != seed) {
                color[i.b] = color[v] ^ i.same;
                correct &= dfs(i.b, time, seed); 
            } else {
                /* cout << i.b << ' ' << v << ' ' << i.same << endl; */
                if (color[i.b] != (color[v] ^ !i.same)) {
                    return false;
                }
            }
        }
    }
    return correct;
}

bool check(int time) {
    static int seed = 1;
    bool correct = true;
    for (int i = 0; i < n; i++) {
        if (used[i] != seed) {
            correct &= dfs(i, time, seed++);
        }
    }
    /* cout << "time = " << time << " is " << correct << endl; */
    return correct;
}

int main() {
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
    freopen("truth.in", "r", stdin);
    freopen("truth.out", "w", stdout);
#endif

    cin >> n >> m;
    vector<int> iamlasy;
    for (int i = 0; i < m; i++) {
        int a, b;
        char type;
        cin >> a >> b >> type;
        a--, b--;
        g[a].push_back(edge(a, b, type == 'T')); 
        iamlasy.push_back(i);
    }

    g[0].push_back(edge(0, 0, false));
    iamlasy.push_back(m);

    /* for (int i = 0; i < n; i++) { */
    /*     for (auto& j : g[i]) { */
    /*         cout << j.a << (j.same ? " == " : " != ") << j.b << " time = " << j.t << endl; */
    /*     } */
    /* } */

    cout << *upper_bound(all(iamlasy), 0, [](int a, int b){
            return check(a) > check(b);
            }) - 1 << endl;

    return 0;
}
