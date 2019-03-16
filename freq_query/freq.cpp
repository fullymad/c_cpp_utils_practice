/******************************************************************************
https://www.hackerrank.com/challenges/frequency-queries/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dictionaries-hashmaps
******************************************************************************/
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

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

// Given a map and its integer key, decrements the integer value if key is
// present. If new value becomes 0, deletes key.
// Returns the new value for the key, 0 if just deleted or -1 if not found
static int
decr_value_in_map(
	unordered_map<int, int> &in_map,
	int						key
)
{
	int		new_value = -1; // If key not found
	unordered_map<int, int>::iterator iter;

	iter = in_map.find(key);
	if (iter != in_map.end()) {
		iter->second -= 1;
		new_value = iter->second;
		if (new_value == 0) { // Discard if down to 0
			in_map.erase(iter);
		}
	}

	return new_value;

} // end decr_value_in_map

// Complete the freqQuery function below.
vector<int> freqQuery(vector<vector<int> > queries) {

	vector<int>		result;
	vector<vector<int> >::iterator q_iter;
	int				oper, value;
	int				new_count;
	int				discard;

	// Map of value to count
	unordered_map<int, int>	val_cache;
	unordered_map<int, int>::iterator vc_iter;

	// Map of count to number of values with that count
	unordered_map<int, int>	count_cache;
	unordered_map<int, int>::iterator cc_iter;

	for (q_iter = queries.begin(); q_iter != queries.end(); ++q_iter) {
		oper = q_iter->at(0);
		value = q_iter->at(1);

		bool deleted = false;
		switch (oper) {
			case 1:
				// Insert operation
				// Insert value with count = 1 or increment count
				new_count = incr_value_in_map(val_cache, value);

				// Update cache of count -> number of values
				// 1. Increment number of values with new count
				discard = incr_value_in_map(count_cache, new_count);

				// 2. Decrement number of values with previous count
				if (new_count > 1) {
					discard = decr_value_in_map(count_cache, new_count - 1);
				}

				break;
			case 2:
				// Delete operation
				// Remove value or decrement count
				new_count = decr_value_in_map(val_cache, value);

				if (new_count != -1) { // Found and decremented
					// Update cache of count -> number of values
					// 1. Increment number of values with new count
					if (new_count != 0) {
						discard = incr_value_in_map(count_cache, new_count);
					}

					// 2. Decrement number of values with previous count
					discard = decr_value_in_map(count_cache, new_count + 1);
				}

				break;
			case 3:
				int result_val = 0;
				if (count_cache.find(value) != count_cache.end()) {
					result_val = 1;
				}
				result.push_back(result_val);
				break;
		} // end switch
	}

	return result;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    vector<vector<int> > queries(q);

    for (int i = 0; i < q; i++) {
        queries[i].resize(2);

        string queries_row_temp_temp;
        getline(cin, queries_row_temp_temp);

        vector<string> queries_row_temp = split(rtrim(queries_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int queries_row_item = stoi(queries_row_temp[j]);

            queries[i][j] = queries_row_item;
        }
    }

    vector<int> ans = freqQuery(queries);

    for (int i = 0; i < ans.size(); i++) {
        fout << ans[i];

        if (i != ans.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
