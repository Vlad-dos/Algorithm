#include "checker.h"
#ifdef checker

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
#include <conio.h>

using namespace std;

void open_io(char input[] = "CON", char output[] = "CON") {
	freopen(input, "r", stdin);
	freopen(output, "w", stdout);
}

void close_io() {
	fclose(stdin);
	fclose(stdout);
}

string s1, s2;
int cnt = 0;

#include <ctime>
int main() {
	srand(time(0));

	while (true) {
		open_io("CON", "input.txt");
		gena::main();
		close_io();
		open_io("input.txt", "patient_output.txt");
		patient::main();
		close_io();
		open_io("input.txt", "dummy_output.txt");
		dummy::main();
		close_io();
		open_io();

		ifstream dummy_in("dummy_output.txt");
		ifstream patient_in("patient_output.txt");

		cout << "test number : " << cnt++ << " ";
		while (dummy_in >> s1) {
			patient_in >> s2;
			if (s1 != s2) {
				cout << "WA\n";
				_getch();
				return 0;
			}
		}
		cout << "OK\n";
	}
}

#endif // checker