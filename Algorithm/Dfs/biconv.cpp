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
 
const int K = 18;
const ll MAXN = 1e6;
const int INF = 2e9 + 1;
const ll LONG_INF = 8e18;
const ll MOD = 1e9 + 7;
const ld e = 1e-9;
const ll C = 500;
const ll dx[4] = {-1, 0, 1, 0};
const ll dy[4] = {0, 1, 0, -1};
 
vector< int > g[MAXN];
int n, m;
int tin[MAXN];
int up[MAXN];
int ret[MAXN];
int used[MAXN];
int t = 0;
set<int> ans;

map< pair<int, int>, int> edges;
int edge_color[MAXN];
vector< pair<int, int> > s;
int color = 1;
 
void dfs(int u, int prev) {
    used[u] = 1;
    tin[u] = t++;
    up[u] = t++;
    int cnt = 0;
    for (auto v : g[u]) {
        if (v == prev) {
            continue;
        }
        if (used[v]) {
            up[u] = min(up[u], tin[v]);
            if (tin[u] > tin[v])
                s.push_back(make_pair(u,v));
        } else {
            s.push_back(make_pair(v,u));
            cnt++;
            dfs(v, u);
            up[u] = min(up[u], up[v]);
            if (prev == -1 && cnt > 1) {
                ans.insert(u);
                while (s.back() != make_pair(v,u)) {
                    edge_color[edges[s.back()]] = color;
                    s.pop_back();
                }
                edge_color[edges[s.back()]] = color;
                s.pop_back();
                color++;
            } else if (prev != -1 && up[v] >= tin[u]) {

                /* cout << "YEAAAH " << u << ' ' << v << endl; */
                /* for (auto i : s) { */
                /*     cout << i.first << ' ' << i.second << endl; */
                /* } */
                /* cout << endl; */

                ans.insert(u);
                while (s.back() != make_pair(v,u)) {
                    edge_color[edges[s.back()]] = color;
                    s.pop_back();
                }
                edge_color[edges[s.back()]] = color;
                s.pop_back();
                color++;
            }
        }
    }
}
 
int main() {
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
    freopen("biconv.in", "r", stdin);
    freopen("biconv.out", "w", stdout);
#endif
 
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
        edges[make_pair(a, b)] = i;
        edges[make_pair(b, a)] = i;
    }
 
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            t = 0;
            dfs(i, -1);
            while (!s.empty()) {
                edge_color[edges[s.back()]] = color;
                s.pop_back();
            }
            color++;
        }
    }

    set<int> shit;
    for (int i = 0; i < m; i++) {
        shit.insert(edge_color[i]);
    }

    cout << shit.size()  << endl;
    for (int i = 0; i < m; i++) {
        cout << edge_color[i] << ' ';
    }
    cout << endl;
 
    return 0;
}
