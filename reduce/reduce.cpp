/******************************************************************************
https://www.hackerrank.com/challenges/counter-game/problem
******************************************************************************/
#include <iostream>
#include <bitset>

using namespace std;

string counterGame(long n) {
	unsigned int	total_moves = 0;

	long temp = n;
	int highest_set = 0;
	int lowest_set = -1;
	int count = 0;
	int bit_num = 0;

	// Count the total number of bits set
	// Check 0th bit after epeatedly shifting right
	while (temp) {
		if (temp & 1) {
			count++;

			// For now, this is the highest bit set
			highest_set = bit_num;

			// For first set bit, mark as lowest bit set
			if (lowest_set == -1) {
				lowest_set = bit_num;
			}
		}

		bit_num++;
		temp >>= 1;
	}

	// Power of 2, so will get reduced to 1 after division by 2 'highest_set'
	// times
	if (count == 1) {
		total_moves = highest_set;
	}
	// Subtracting the highest power of 2 means resetting leftmost set bit.
	// This happens repeatedly until one bit is left set (at which time it is
	// a power of 2).
	else {
		total_moves += (count - 1); // Repeated subtraction
		total_moves += lowest_set; // Division by 2 until it is reduced to 1
	}

	// Odd number of moves - Louise being the starter makes the last move
	if (total_moves % 2) {
		return "Louise";
	}
	else {
		return "Richard";
	}
}

int main() {
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        long n;
        cin >> n;
        string result = counterGame(n);
        cout << result << endl;
    }
    return 0;
}
