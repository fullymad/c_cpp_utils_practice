/******************************************************************************
https://www.hackerrank.com/challenges/find-the-running-median
******************************************************************************/
#include <map>
#include <string>
#include <iomanip>
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

double
get_median(
	multimap<int, bool> &all_numbers,
	int count
)
{
	multimap<int, bool>::iterator iter;
	int	index; // 'index' of median in logical sorted order
	bool			odd_count = false;
	double			result;

	assert(count != 0);

	// Get the middle (or average of middle 2) element(s) to find median.

	if (count % 2 == 1) {
		odd_count = true;
		index = ((count + 1) / 2) - 1;
	}
	else {
		index = (count / 2) - 1;
	}

	iter = all_numbers.begin();
	// 'iter += index' does not work, hence the loop
	for (int i = 1; i <= index; i++) {
		iter++;
	}
	result = iter->first;

	if (! odd_count) { // Get next one and find average
		iter++;
		result += iter->first;
		result /= 2;
	}

	return result;

} // get_median


// Functionally fine but fails to perform and times out
// NOTE: Maybe a doubly linked list with a current median pointer being tracked
// When a new element is added before/after the current median, the pointer can
// be adjusted.
int main() {
	unsigned int	count;
	unsigned int	number;
	multimap<int, bool>	all_numbers;

	cin >> count;

	for (int i = 0; i < count; i++) {
		cin >> number;

		all_numbers.insert(std::pair<int, bool>(number, true));

		cout << fixed << setprecision(1)
			<< get_median(all_numbers, i + 1) << endl;
	}

	return 0;
}
