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

int n;
int wires[MAXN];
vector<int> g[MAXN];
int sockets[MAXN];

vector<int> pairs[MAXN];

int get_pair(int i) {
    return pairs[sockets[i]][0] + pairs[sockets[i]][1] - i;
}

vector<int> ans;
int used[MAXN];
void dfs(int v) {
    used[v] = 1;
    for (auto i : g[v]) 
        if (!used[i])
            dfs(i);
    ans.push_back(v);
}

int color[MAXN];
int done[MAXN];
int res[MAXN];
bool paint(int v) {
    /* cout << "falskdf  " << v << ' ' << get_pair(v) << " -- " << sockets[v] << endl; */
    done[v] = 1;
    done[get_pair(v)] = 1;
    color[v] = 1;
    color[get_pair(v)] = 0;
    res[sockets[v]] = v + 1;
    
    /* write(g[v], ' '); */
    /* cout << endl; */

    bool f = true;
    for (auto i : g[v]) {
        /* cout << v << " -- " << i << endl; */
        if (!done[i])
            f &= paint(i);
        else
            if (color[i] == 0) {
                return false;
            }
    }
    return f;
}

int main() {
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
    freopen("chip.in", "r", stdin);
    freopen("chip.out", "w", stdout);
#endif

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> wires[i];
    }

    for (int i = 0; i < 2 * n; i++) {
        int wire;
        cin >> wire;
        wire--;
        sockets[i] = wire;
        pairs[wire].push_back(i);
    }

    vector<int> tmp;
    for (int i = 0; i < 2 * n; i++) {
        int last = (i + 2 * n - 1) % (2 * n);

        /* cout << i << ' ' << last << endl;; */
        /* cout << "pair " << i << ' ' << get_pair(i) << endl; */
        /* cout << pairs[sockets[i]][0] << ' ' << pairs[sockets[i]][1] << endl; */
        /* cout << endl; */

        tmp.push_back(i);
        if (wires[sockets[last]] == wires[sockets[i]]) {
            g[i].push_back(get_pair(last));
            g[last].push_back(get_pair(i)); 
        }
    }

    bool f = false;
    int cnt = 0;
    while (!f) {
        if (cnt > 25) {
            cout << "NO" << endl;
            return 0;
        }
        cnt++;
        f = true;
        for (int i = 0; i < 2 * n; i++) {
            used[i] = 0;
            color[i] = 0;
            done[i] = 0;
            res[i] = 0;
        }
        ans.clear();
        random_shuffle(all(tmp));
        for (auto i : tmp)
            if (!used[i])
                dfs(i);

        for (auto i : ans) {
            if (!done[i])
                f &= paint(i);
        }
    }

    cout << "YES" << endl;
    for (int i = 0; i < n; i++) {
        cout << res[i] << ' ';
    }
    cout << endl;

    return 0;
}

