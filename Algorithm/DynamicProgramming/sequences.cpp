#ifdef LOCAL
#include "task_selection.h"
#include "checker.h"
#else
#define sequences task
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

namespace sequences {

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
	const ll MOD = 999999937;
	const ld e = 1e-9;
	const ll C = 500;
	const ll dx[4] = { -1, 0, 1, 0 };
	const ll dy[4] = { 0, 1, 0, -1 };

	class matrix {
		vector< vector<ll> > data;
	public:
		int n, m;

		matrix() {}
		matrix(initializer_list< initializer_list<ll> > a) {
			n = a.size();
			data = vector< vector<ll> >();
			m = a.begin()->size();
			for (auto i : a) {
				assert((int)i.size() == m);
				data.push_back(vector<ll>());
				auto tmp = &data.back();
				for (auto j : i) {
					tmp->push_back(j);
				}
			}
		}

		matrix(int N, int M) {
			n = N;
			m = M;
			data = vector< vector<ll> >(n);
			for (int i = 0; i < n; i++) {
				data[i] = vector<ll>(m);
			}
		}

		ll& operator()(const int i, const int j) {
			return data[i][j];
		}

		matrix operator*(matrix b) {
			assert(m == b.n);
			matrix result(n, b.m);

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < b.m; j++) {
					ll sum = 0;
					for (int k = 0; k < m; k++) {
						sum += operator()(i, k) * b(k, j);
						sum %= MOD;
					}
					result(i, j) = sum;
				}
			}

			return result;
		}

		matrix one() {
			assert(n == m);
			matrix result(n, m);
			for (int i = 0; i < n; i++) {
				result(i, i) = 1;
			}
			return result;
		}

		void print(std::ostream& stream) {
			for (auto i : data) {
				for (auto j : i) {
					stream << j << ' ';
				}
				stream << '\n';
			}
		}
	};

	matrix fast_pow(matrix a, ll k) {
		ll l = k;
		matrix b = a;
		matrix x = a.one();
		while (l > 0) {
			if (l % 2 == 0) {
				b = b * b;
				l /= 2;
			}
			else {
				x = b * x;
				l -= 1;
			}
		}
		return x;
	}

	ostream& operator<< (ostream& stream, matrix& tmp) {
		tmp.print(stream);
		return stream;
	}

	matrix a;
	matrix p;

	int main() {
		ll n;
		cin >> n;
		while (n != 0) {
			a = matrix({ { 2, 3 } });
			p = matrix({ { 1, 2 },{ 2, 3 } });

			a = a * fast_pow(p, n - 1);
			cout << (a(0, 0) + a(0, 1)) % MOD << endl;

			cin >> n;
		}

		return 0;
	}
}

#if defined(sequences) && !defined(checker)
int main() {
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	//while (!cin.eof()) {
		sequences::main();
	//}
	sequences::wait();
#else   
	freopen("sequences.in ", "r", stdin);
	freopen("sequences.out", "w", stdout);
	sequences::main();
#endif
	return 0;
}
#endif