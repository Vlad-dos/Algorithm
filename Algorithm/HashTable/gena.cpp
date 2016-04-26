#include "task_selection.h"
#include "checker.h"

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

namespace gena {

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
	const ll MAXN = 2e3 + 10;
	const int INF = 2e9 + 1;
	const ll LONG_INF = 8e18;
	const ll MOD = 1e9 + 7;
	const ld e = 1e-9;
	const ll C = 500;
	const ll dx[4] = { -1, 0, 1, 0 };
	const ll dy[4] = { 0, 1, 0, -1 };

	int main();
}

using namespace gena;

set<string> used;

string rands() {
	if (rand() % 5 == 0 && used.size()) {
		int pos = rand() % used.size();
		auto a = used.begin();
		for (int i = 0; i < pos; i++) {
			a++;
		}
		return *a;
	}
	int len = rand() % 20 + 1;
	string s;
	for (int i = 0; i < len; i++) {
		s += ('a' + rand() % 20);
	}
	used.insert(s);
	return s;
}

int gena::main() {
	for (int i = 0; i < 100; i++) {
		int type = rand() % 30;
		if (type < 10) {
			cout << "put ";
		}
		else if (type < 25) {
			cout << "get ";
		} else {
			cout << "delete ";
		}
		if (type < 10) {
			cout << rands() << ' ';
		}
		cout << rands() << endl;
	}

	return 0;
}

#if defined(gena) && !defined(checker)
int main() {
	freopen("input.txt", "w", stdout);

	gena::main();
	gena::wait();
	return 0;
}
#endif