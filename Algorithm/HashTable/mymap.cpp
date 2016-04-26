#ifdef LOCAL
#include "task_selection.h"
#include "checker.h"
#else
#define mymap task
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

namespace mymap {

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
	const ll dx[4] = { -1, 0, 1, 0 };
	const ll dy[4] = { 0, 1, 0, -1 };

	class hashmap {
	private:
		class node {
		public:
			int hash;
			char* key;
			char* value;
			node* next;

			node(int hash, char* key, char* value, node* next = nullptr) : hash(hash), key(key), value(value), next(next) {}
		};

		vector<node*> table;
		int size;
		int capacity;
		const int p = 31;

		bool equals(char* a, char* b) {
			int lena = strlen(a);
			int lenb = strlen(b);
			if (lena == lenb) {
				for (int i = 0; i < lena; i++) {
					if (a[i] != b[i])
						return false;
				}
				return true;
			}
			else {
				return false;
			}
		}

		int hash(char* key) {
			ll h = 0;
			ll st = 1;
			ll len = strlen(key);
			for (int i = 0; i < len; i++) {
				h += (st * key[i]);
				h %= capacity;
				st *= p;
				st %= capacity;
			}
			return (int)h;
		}

		void ensure_capacity(int sz) {
			if (capacity * 4 >= sz * 3) {
				return;
			}
			else {
				size = 0;
				capacity *= 2;
				auto old_table = table;
				table = vector<node*>(capacity);
				for (auto i : old_table) {
					node* pos = i;
					while (pos != nullptr) {
						insert(pos->key, pos->value);
						node* temp = pos;
						pos = pos->next;
						delete(temp);
					}
				}
			}
		}
	public:
		void insert(char* key, char* value) {
			ensure_capacity(++size);
			node* a = new node(hash(key), key, value, nullptr);
			node* pos = table[a->hash];
			node* last_pos = nullptr;
			while (pos != nullptr) {
				if (equals(pos->key, key)) {
					pos->value = value;
					return;
				}
				last_pos = pos;
				pos = pos->next;
			}
			if (last_pos != nullptr) {
				last_pos->next = a;
			}
			else {
				table[a->hash] = a;
			}
		}

		bool exist(char* key) {
			int h = hash(key);
			node* pos = table[h];
			while (pos != nullptr) {
				if (equals(pos->key, key)) {
					return true;
				}
				pos = pos->next;
			}
			return false;
		}

		char* get(char* key) {
			int h = hash(key);
			node* pos = table[h];
			while (pos != nullptr) {
				if (equals(pos->key, key)) {
					return pos->value;
				}
				pos = pos->next;
			}
			return nullptr;
		}

		void remove(char* key) {
			int h = hash(key);
			node* pos = table[h];
			node* last_pos = nullptr;
			while (pos != nullptr) {
				if (equals(pos->key, key)) {
					if (last_pos != nullptr) {
						last_pos->next = pos->next;
					}
					else {
						table[h] = pos->next;
					}
					delete(pos);
					return;
				}
				last_pos = pos;
				pos = pos->next;
			}
		}

		hashmap() {
			size = 0;
			capacity = 10;
			table = vector<node*>(capacity);
		}
	};

	hashmap map;

	int main() {
		char s[20];
		while (scanf("%s", s) != -1) {
			char* key = new char[20];
			char* value = new char[20];
			if (s[0] == 'p') {
				scanf("%s %s", key, value);
				map.insert(key, value);
			}
			else if (s[0] == 'g') {
				scanf("%s", key);
				char *ans = map.get(key);
				if (ans == nullptr) {
					cout << "none\n";
				}
				else {
					cout << ans << '\n';
				}
			}
			else {
				scanf("%s", key);
				map.remove(key);
			}
		}

		return 0;
	}
}

#if defined(mymap) && !defined(checker)
int main() {
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

		mymap::main();
	mymap::wait();
#else   
	freopen("map.in ", "r", stdin);
	freopen("map.out", "w", stdout);
	mymap::main();
#endif
	return 0;
}
#endif