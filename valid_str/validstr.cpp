/******************************************************************************
https://www.hackerrank.com/challenges/sherlock-and-valid-string/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=strings
******************************************************************************/
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;
#include <stdlib.h>

const int NUM_CHARS = 26;

// Given a map and its integer key, increments the integer value. If key does
// not exist, inserts entry with value = 1
// Returns the new value for the key
static int
incr_value_in_map(
	unordered_map<int, int> &in_map,
	int						key
)
{
	int		new_value = 0;
	unordered_map<int, int>::iterator iter;

	iter = in_map.find(key);
	if (iter != in_map.end()) {
		iter->second += 1;
		new_value = iter->second;
	}
	else {
		in_map.insert(pair<int, int>(key, 1));
		new_value = 1;
	}

	return new_value;

} // end incr_value_in_map

// Complete the isValid function below.
string isValid(string s) {
	string		result = "YES";
	size_t		len = s.length();
	vector<int> v_freq(NUM_CHARS, 0);
	vector<int>::iterator iter;
	unordered_map<int, int> freq_count;
	unordered_map<int, int>::iterator c_iter;
	pair<int, int>	freqs[2];

	// Store frequency of each of 'a' - 'z' in an array
	for (int i = 0; i < len; i++) {
		v_freq[s[i] - 'a'] += 1;
	}

/*
	for (int i = 0; i < NUM_CHARS; i++) {
		cout << "ch = " << 'a' + i << " count = " << v_freq[i] << endl;
	}
*/

	// Store occurrences of each frequency value in a map
	// Key: Frequency, Value: How many characters occur with that frequency?
	for (int i = 0; i < NUM_CHARS; i++) {
		if (v_freq[i] != 0) {
			incr_value_in_map(freq_count, v_freq[i]);
		}
	}

	// If there are 3 distinct frequencies, string is invalid
	if (freq_count.size() > 2) {
		result = "NO";
	}

	// With 2 distinct frequencies, here are some examples
	// Example 1: Invalid string
	// Key: 5, Value: 3 (say, characters a, f, k occur 5 times each)
	// Key: 4, Value: 2 (say, characters q, z occur 4 times each)
	// Example 2: Valid string
	// Key: 5, Value: 1 (say, character k occurs 5 times)
	// Key: 4, Value: 2 (say, characters q, z occur 4 times each)

	else if (freq_count.size() == 2) { // Size 1 means valid string
		int i_freqs = 0;
		for (c_iter = freq_count.begin(); c_iter != freq_count.end();
				++c_iter) {
			freqs[i_freqs].first = c_iter->first;
			freqs[i_freqs].second = c_iter->second;
			i_freqs++;
		}

/*
		cout << "Key 1: " << freqs[0].first << " Value 1: "
			<< freqs[0].second << endl;
		cout << "Key 2: " << freqs[1].first << " Value 2: "
			<< freqs[1].second << endl;
*/

		// We now have 2 frequencies and number of characters in 2 pairs
		// Valid if 2 frequencies differ by 1 and higher frequency is for a
		// single character
		// EXCEPTION: 2 frequencies differ by more than 1, but one frequency
		// is 1 with its number of characters also as 1. Example: abbbbcccc

		if ( (freqs[0].first == 1 && freqs[0].second == 1) ||
			(freqs[1].first == 1 && freqs[1].second == 1) ) {
			// Get EXCEPTION case out of the way
			result = "YES";
		}
		else if (abs(freqs[0].first - freqs[1].first) != 1) {
			// Frequencies differ by more than 1
			result = "NO";
		}
		else if (freqs[0].first > freqs[1].first && freqs[0].second != 1) {
			// Higher frequency is not for a single character
			result = "NO";
		}
		else if (freqs[1].first > freqs[0].first && freqs[1].second != 1) {
			// Higher frequency is not for a single character
			result = "NO";
		}
	}

	return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = isValid(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
