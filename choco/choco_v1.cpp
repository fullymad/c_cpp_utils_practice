/******************************************************************************
https://www.hackerrank.com/challenges/equal
Christy is interning at HackerRank. One day she has to distribute some chocolates to her colleagues. She is biased towards her friends and may have distributed the chocolates unequally. One of the program managers gets to know this and orders Christy to make sure everyone gets equal number of chocolates.

But to make things difficult for the intern, she is ordered to equalize the number of chocolates for every colleague in the following manner,

For every operation, she can choose one of her colleagues and can do one of the three things.

She can give one chocolate to every colleague other than chosen one.
She can give two chocolates to every colleague other than chosen one.
She can give five chocolates to every colleague other than chosen one.
Calculate minimum number of such operations needed to ensure that every colleague has the same number of chocolates. 

Input Format

First line contains an integer T denoting the number of testcases. T testcases follow. 
Each testcase has 2 lines. First line of each testcase contains an integer N denoting the number of colleagues. Second line contains N space separated integers denoting the current number of chocolates each colleague has.

Constraints

1 <= T <= 100
1 <= N <= 10000
Number of initial chocolates each colleague has < 1000

Output Format

T lines, each containing the minimum number of operations needed to make sure all colleagues have the same number of chocolates.

Sample Input

1
4
2 2 3 7
Sample Output

2
Explanation

1st operation: Christy increases all elements by 1 except 3rd one 
2 2 3 7 -> 3 3 3 8
2nd operation: Christy increases all element by 5 except last one
3 3 3 8 -> 8 8 8 8
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
int main() {
	int tests;
	int people;

	cin >> tests;

	for (int t = 0; t < tests; t++) {
		int ops = 0;
		cin >> people;

		vector<int> chocs(people);
		for (int p = 0; p < people; p++) {
			cin >> chocs[p];
		}

		// Sort in place
		sort(chocs.begin(), chocs.end());

		int prev_low = chocs[0];
		int diff = 0;
		int incr = 0;
		int quotient = 0;
		for (int i = 1; i < people; i++) {
			if (chocs[i] > prev_low) {
				diff = chocs[i] - prev_low;

				// Get increment and number of operations to get prev_low to
				// to equal the next higher number
				incr = 0;

				quotient = diff / 5;
				if (quotient != 0) {
					ops += quotient;
					incr += quotient * 5;
					diff -= quotient * 5;
				}

				quotient = diff / 2;
				if (quotient != 0) {
					ops += quotient;
					incr += quotient * 2;
					diff -= quotient * 2;
				}

				if (diff != 0) {
					ops += diff;
					incr += diff;
					diff = 0;
				}

				// Increment all subsequent elements by incr
				if (i < people) {
					for (int j = i + 1; j < people; j++) {
						chocs[j] += incr;
					}
				}

				prev_low = chocs[i];
			} // if found higher number

		} // for each colleague

		cout << ops << endl;

	} // for each test case

	return 0;
}
