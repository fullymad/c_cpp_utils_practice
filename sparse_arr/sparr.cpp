/*****************************************************************************
There is a collection of N strings ( There can be multiple occurences of a particular string ). Each string's length is no more than 20 characters. There are also Q queries. For each query, you are given a string, and you need to find out how many times this string occurs in the given collection of N strings.

Input Format

The first line contains N, the number of strings.
The next N lines each contain a string.
The N+ 2nd line contains Q, the number of queries.
The following Q lines each contain a query string.

Constraints

1 <= N <= 1000
1 <= Q <= 1000
1 <= length of any string <=20

Sample Input

4
aba
baba
aba
xzxb
3
aba
xzxb
ab
Sample Output

2
1
0
Explanation

Here, "aba" occurs twice, in the first and third string. The string "xzxb" occurs once in the fourth string, and "ab" does not occur at all.
*****************************************************************************/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

int main(){
	int		count;
	int		i;
	string	next_str;
	map<string, int>	str_map;
	map<string, int>::iterator iter;

	cin >> count;

	for (i = 0; i < count; i++) {
		cin >> next_str;

		iter = str_map.find(next_str);
		if (iter == str_map.end()) {
			str_map.insert(pair<string, int>(next_str, 1));
		}
		else {
			iter->second = iter->second + 1;
		}
	}

	cin >> count;

	for (i = 0; i < count; i++) {
		cin >> next_str;

		iter = str_map.find(next_str);
		if (iter == str_map.end()) {
			cout << 0 << endl;
		}
		else {
			cout << iter->second << endl;
		}
	}

	return 0;
}
