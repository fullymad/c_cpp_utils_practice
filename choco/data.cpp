/******************************************************************************
https://www.hackerrank.com/challenges/equal
******************************************************************************/

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;


int main(){

	cout << 1 << endl; // Number of test cases

/*
	cout << 9991 << endl;
	for (int outer = 0; outer < 10; outer++) {
		for (int n = 999; n > 0; n--) {
			cout << n << " ";
		}
	}

	cout << 999 << endl;
*/

	cout << 10000 << endl;

	// Initialize the seed for random number generator
	srand(time(NULL));

	for (int i = 0; i < 9999; i++) {
		cout << (rand() % 1000) << " ";
	}

	cout << 999 << endl;

	return 0;
}
