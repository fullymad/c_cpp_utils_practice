/******************************************************************************
https://www.hackerrank.com/challenges/find-the-running-median
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
#include <iomanip>
#include <cassert>

using namespace std;

double
get_median(
	vector<unsigned int> all_numbers
)
{
	unsigned int	count = all_numbers.size();
	unsigned int	index; // 'index' of median in logical sorted order
	bool			odd_count = false;
	double			result;

	assert(count != 0);

	// Pop out elements until the middle element is hit. If even number of
	// elements, the average of the 2 middle elements will be the median.

	if (count % 2 == 1) {
		odd_count = true;
		index = ((count + 1) / 2) - 1;
	}
	else {
		index = (count / 2) - 1;
	}
	
	for (int i = 0; i < index; i++) {
		pop_heap(all_numbers.begin(), all_numbers.end());
		all_numbers.pop_back();
	}

	result = all_numbers[0];

	if (! odd_count) {
		pop_heap(all_numbers.begin(), all_numbers.end());
		all_numbers.pop_back();
		result += all_numbers[0];
		result /= 2;
	}

	return result;

} // get_median


int main() {
	unsigned int	count;
	unsigned int	number;
	vector<unsigned int> all_numbers;

	cin >> count;

	for (int i = 0; i < count; i++) {
		cin >> number;

		all_numbers.push_back(number);
		push_heap(all_numbers.begin(), all_numbers.end());

		cout << fixed << setprecision(1) << get_median(all_numbers) << endl;
	}

	return 0;
}
