/*****************************************************************************
https://www.hackerrank.com/challenges/sparse-arrays/problem
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
