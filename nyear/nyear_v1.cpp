/******************************************************************************
https://www.hackerrank.com/challenges/new-year-chaos/problem

It's New Year's Day and everyone's in line for the Wonderland rollercoaster ride!

There are n people queued up, and each person wears a sticker indicating their initial position in the queue (i.e.: 1,2,...,n-1,n with the first number denoting the frontmost position).

Any person in the queue can bribe the person directly in front of them to swap positions. If two people swap positions, they still wear the same sticker denoting their original place in line. One person can bribe at most two other persons.

That is to say, if n=8 and Person 5 bribes Person 4, the queue will look like this: 1,2,3,5,4,6,7,8.

Fascinated by this chaotic queue, you decide you must know the minimum number of bribes that took place to get the queue into its current state!

Note: Each Person X wears sticker X, meaning they were initially the Xth person in queue.

Input Format

The first line contains an integer, T, denoting the number of test cases. 
Each test case is comprised of two lines; the first line has n (an integer indicating the number of people in the queue), and the second line has n space-separated integers describing the final state of the queue.

Constraints

1 <= T <= 10
1 <= n <= 10**5


Subtasks

For 60% score 1<= n <= 10**3
For 100% score 1<= n <= 10**5

Output Format

Print an integer denoting the minimum number of bribes needed to get the queue into its final state; print Too chaotic if the state is invalid (requires Person X to bribe more than 2 people).

Sample Input

2
5
2 1 5 3 4
5
2 5 1 3 4
Sample Output

3
Too chaotic
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
	int T;
	cin >> T;
	for(int a0 = 0; a0 < T; a0++){
		int n;
		cin >> n;
		vector<int> q(n);
		for(int q_i = 0;q_i < n;q_i++){
			cin >> q[q_i];
		}

		int bribes = 0; // Number of bribes
		int shifts = 0; // Number of minimum shifts - a single bribe can shift
						// 2 subsequent elements back, each by 1
		bool valid = true;
		int diff = 0;
		int curr_shifts = 0; // Tells how many current element shifted back

		for (int q_i = 0; q_i < n; q_i++) {
			diff = q[q_i] - (q_i + 1);
			if (diff > 2) { // Only 2 bribes allowed per person
				valid = false;
				break;
			}
			else if (diff > 0) {
				bribes += diff;
				// For now, assume 1 or 2 elements will be shifted right by 1
				shifts++;
			}
			else {
				curr_shifts = abs(diff); // Could be 0, meaning not shifted

				if (shifts == curr_shifts) {
					shifts = 0;
				}
				// If current element not shifted by the expected amount, it
				// means more bribes happened to shift it forward
				else if (shifts > curr_shifts) {
					bribes += (shifts - curr_shifts);
					shifts++; // Subsequent elements would be shifted right
				}
			}
		}

		if (! valid) {
			cout << "Too chaotic" << endl;
		}
		else {
			cout << bribes << endl;
		}
	} /* for all tests */

	return 0;
}
