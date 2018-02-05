/*****************************************************************************
https://www.hackerrank.com/challenges/bigger-is-greater/problem
*****************************************************************************/
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

string biggerIsGreater(string w) {

	int len = w.length();
	char temp;
	string result;

	// The 2 positions in string where swapping happens
	int swap_in_pos = -1;
	int swap_out_pos = -1;

	// Attempt to swap the last character with the nearest character that is
	// 'smaller'. This is the swap-in position.
	// If none found till the start of the string, try the second last
	// character and so on.
	// If found, continue with the next character from the end to see if the
	// swap-in position is closer than the previous swap-in position. Stop when
	// crossing the current nearest swap-in position.
	for (int i = len - 1; i >= 0; i--) {
		for (int j = i - 1; j >= 0; j--) {
			if (w[j] < w[i]) {
				swap_in_pos = j;
				swap_out_pos = i;
				break;
			}
			else if (j - 1 <= swap_in_pos) {
				break;
			}
		}
		if (i - 1 <= swap_in_pos + 1) {
			break;
		}
	}

	// No swapping possible, so there is no answer
	if (swap_in_pos == -1) {
		return "no answer";
	}
	else {
		temp = w[swap_in_pos];
		w[swap_in_pos] = w[swap_out_pos];
		w[swap_out_pos] = temp;

		// Sort the substring after the location swapped into, so that the
		// result string is 'minimally' greater
		std::sort(w.begin() + swap_in_pos + 1, w.end());
		return w;
	}

} /* end biggerIsGreater */

int main() {
    int T;
    cin >> T;
    for(int a0 = 0; a0 < T; a0++){
        string w;
        cin >> w;
        string result = biggerIsGreater(w);
        cout << result << endl;
    }
    return 0;
}
