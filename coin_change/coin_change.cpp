/*****************************************************************************
https://www.hackerrank.com/challenges/coin-change/problem
*****************************************************************************/
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

long
getWays(long amount, vector <long> &coins,
		int start_from, map<long, long> cache_ways)
{
	long ways = 0;
	map<long, long>::iterator cache_iter;

	cout << "Calculating for amount " << amount << " starting from "
		<< start_from << endl;

	if (amount == 0) {
		return 1;
	}
	else if (amount < 0) {
		return 0;
	}

	// If previously calculated for this amount, return from cache
	cache_iter = cache_ways.find(amount);
	if (cache_iter != cache_ways.end()) {
		return cache_iter->second;
	}

	int count_coins = coins.size();

	// start_from used to avoid processing the same combination already
	// processed when iterating
	for (int i = start_from; i < count_coins; i++) {
		if (amount - coins[i] == 0) {
			ways += 1;
		}
		else if (amount - coins[i] >= 0) {
			ways += getWays(amount - coins[i], coins, i, cache_ways);
		}
	}

	cache_ways.insert(pair<long, long>(amount, ways));

	cout << "Returning ways " << ways << endl;

	return ways;

} /* end getWays */

long getWays(long n, vector < long > &c){

	long ways = 0;
	long amount = n;
	map<long, long> cache_ways;
	vector<long>::iterator coins_iter;
	int start_from = 0;

	ways = getWays(amount, c, start_from, cache_ways);

	return ways;

} /* getWays */

int main() {
    int n;
    int m;
    cin >> n >> m;
    vector<long> c(m);
    for(int c_i = 0; c_i < m; c_i++){
       cin >> c[c_i];
    }
    // Print the number of ways of making change for 'n' units using coins having the values given by 'c'
    long ways = getWays(n, c);

	cout << ways << endl;

    return 0;
} /* main */
