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
#include <cassert>

using namespace std;


int
get_ops(
	long	diff
)
{
	long ops = 0;
	long quotient = 0;

	quotient = diff / 5;
	ops += quotient;
	diff -= quotient * 5;

	if (diff == 1 || diff == 2) {
		ops += 1;
	}
	else if (diff == 3 || diff == 4) {
		ops += 2;
	}

	return ops;

} /* get_ops */


int
find_ops_incr_by_five(
	vector<int>		&chocs
)
{
	long prev_low = chocs[0];
	int diff = 0;
	int incr = 0;
	int quotient = 0;
	long aggregate_incr = 0;
	int ops = 0;
	int	people = chocs.size();

	for (int i = 1; i < people; i++) {
		// Add hitherto total increment to current element
		if ((chocs[i] + aggregate_incr) > prev_low) {
			diff = chocs[i] + aggregate_incr - prev_low;

			// Get increment and number of operations to get prev_low to
			// equal the next higher number
			incr = 0;

			quotient = diff / 5;
			if (quotient != 0) {
				ops += quotient;
				incr += quotient * 5;
				diff -= quotient * 5;
			}

			// If remainder is 1 or 2, increment by that so that prev_low
			// value catches up with the current value
			if (diff == 1 || diff == 2) {
				ops += 1;
				incr += diff;
				diff = 0;
				prev_low += incr;
			}
			// If remainder would result in 2 operations, do the following.
			// - Increment by 5 to make prev_low become higher than current
			// value
			// - Swap positions of prev_low and current
			// - Increment by 1 or 2 as the case may be to make current and
			// prev_low the same
			else if (diff == 3 || diff == 4) {
				ops += 2;
				incr += 5 + (5 - diff);
				diff = 0;
				prev_low += (quotient * 5) + 5;
			}
			else {
				prev_low += incr;
			}

			aggregate_incr += incr;

		} // if found higher number
	} // for each colleague

	return ops;

} /* find_ops_incr_by_five */

int
find_ops_look_ahead(
	vector<int>		&chocs
)
{
	long prev_low = chocs[0];
	int diff = 0;
	int incr = 0;
	int quotient = 0;
	long aggregate_incr = 0;
	int ops = 0;
	int	people = chocs.size();

	for (int i = 1; i < people; i++) {
		// Add hitherto total increment to current element
		if ((chocs[i] + aggregate_incr) > prev_low) {
			diff = chocs[i] + aggregate_incr - prev_low;

			// Get increment and number of operations to get prev_low to
			// equal the next higher number
			incr = 0;

			quotient = diff / 5;
			if (quotient != 0) {
				ops += quotient;
				incr += quotient * 5;
				diff -= quotient * 5;
			}

			// If remainder is 1 or 2, increment by that so that prev_low
			// value catches up with the current value
			if (diff == 1 || diff == 2) {
				ops += 1;
				incr += diff;
				diff = 0;
				prev_low += incr;
			}
			// If remainder would result in 2 operations, do the following.
			// - Increment by 5 to make prev_low become higher than current
			// value
			// - Swap positions of prev_low and current
			// - Increment by 1 or 2 as the case may be to make current and
			// prev_low the same

			// NOTE: Use the simple logic in find_ops_sequential() if the next
			// iteration would result in less operations than the logic of
			// incrementing by 5.
			else if (diff == 3 || diff == 4) {
				int ops_1 = 0;
				int ops_2 = 0;
				// If not at end, look ahead to check which method is better
				// for the current and next iterations together. Current is 2
				// either way, but the next one could be 1 or 2.
				if (i < (people - 1)) {
					ops_1 = get_ops(chocs[i + 1] + incr + 5 - chocs[i]);
					ops_2 = get_ops(chocs[i + 1] + incr + diff - chocs[i]);
				}

				cout << "ops_1: " << ops_1 << " ops_2: " << ops_2 << endl;

				if (ops_1 <= ops_2) {
					ops += 2;
					incr += 5 + (5 - diff);
					diff = 0;
					prev_low += (quotient * 5) + 5;
				}
				else {
					ops += 2;
					incr += diff;
					diff = 0;
					prev_low += incr;
				}
			}
			else {
				prev_low += incr;
			}

			aggregate_incr += incr;

		} // if found higher number
	} // for each colleague

	return ops;

} /* find_ops_look_ahead */



int
find_ops_sequential(
	vector<int>		&chocs
)
{
	long prev_low = chocs[0];
	int diff = 0;
	int incr = 0;
	int quotient = 0;
	long aggregate_incr = 0;
	int ops = 0;
	int	people = chocs.size();

	for (int i = 1; i < people; i++) {
		// Add hitherto total increment to current element
		if ((chocs[i] + aggregate_incr) > prev_low) {
			diff = chocs[i] + aggregate_incr - prev_low;

			// Get increment and number of operations to get prev_low to
			// equal the next higher number
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

			prev_low += incr;
			aggregate_incr += incr;

		} // if found higher number
	} // for each colleague

	return ops;

} /* find_ops_sequential */


int main() {
	int tests;
	int people;

	cin >> tests;
	assert(tests > 0);

	for (int t = 0; t < tests; t++) {
		int ops = 0;
		int ops_incr_by_five = 0;
		int ops_sequential = 0;
		int ops_look_ahead = 0;

		cin >> people;
		assert(people > 0);

		vector<int> chocs(people);
		for (int p = 0; p < people; p++) {
			cin >> chocs[p];
		}

		// Sort in place
		sort(chocs.begin(), chocs.end());

		// Use the smallest of operations returned by the 3 methods
		ops_incr_by_five = find_ops_incr_by_five(chocs);
		ops_sequential = find_ops_sequential(chocs);
		ops_look_ahead = find_ops_look_ahead(chocs);

		ops = (ops_incr_by_five <= ops_sequential ?
				ops_incr_by_five : ops_sequential);

		ops = (ops <= ops_look_ahead ? ops : ops_look_ahead);

		cout << "ops_incr_by_five: " << ops_incr_by_five << endl;
		cout << "ops_sequential: " << ops_sequential << endl;
		cout << "ops_look_ahead: " << ops_look_ahead << endl;

		cout << ops << endl;

	} // for each test case

	return 0;
}
