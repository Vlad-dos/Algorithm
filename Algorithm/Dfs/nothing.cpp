#include "task_selection.h"
#include "checker.h"

#ifdef nothing

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>

using namespace std;

int nothing::main() {
	ifstream patient_in("patient_output.txt");
	string s;
	while (patient_in >> s) {
		cout << s << endl;
	}
	return 0;
}
#endif