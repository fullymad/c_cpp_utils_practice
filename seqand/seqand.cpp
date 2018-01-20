/*****************************************************************************
https://www.hackerrank.com/challenges/and-product
start
Find the bitwise AND product of all numbers in the inclusive range between a
and b. Input has the number of such intervals followed by each interval of
space-separated numbers.

1 <=n <= 200
0 <= a <= b < 2**32
*****************************************************************************/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

unsigned int get_product(
	unsigned int start,
	unsigned int end
)
{
	unsigned int product = 0;

	//printf("get_product: start %x, end %x\n", start, end);

	if (start == 0) {
		product = 0;
	}
	else if (start == end) {
		product = start;
	}
	else {
		// If the highest set bit is different between start and end, start
		// will be masked out completely and so the AND product will be 0

		unsigned int temp, highest_set_1, highest_set_2;

		temp = start;
		highest_set_1 = 0;
		while (temp >>= 1) {
			highest_set_1++;
		}

		temp = end;
		highest_set_2 = 0;
		while (temp >>= 1) {
			highest_set_2++;
		}

		if (highest_set_1 != highest_set_2) {
			product = 0;
			//printf("Returning product as 0\n");
		}
		else {
			// Highest bit matches in entire range, check remaining bits
			product = (1 << highest_set_1); // Set highest bit as matching
			//printf("Matching bit translates to : %x\n", product);
			if (highest_set_1 != 0) {
				start -= product;
				end -= product;
				product |= get_product(start, end);
			}
		}
	}

	return product;
}

int main() {
	unsigned int n, start, end, product;

	cin >> n; // Get number of intervals

	for (int i = 0; i < n; i++) {
		cin >> start >> end;

		product = 0;
		product |= get_product(start, end);

		cout << product << endl;
	}

	return 0;
}
