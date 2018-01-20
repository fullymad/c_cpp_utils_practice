// https://www.hackerrank.com/challenges/game-of-stones-1
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_STONES_COUNT 100

int
get_winner(
	int stones,
	int current_player,
	int winner_cache[]
)
{
	int winner;
	int other_player = (current_player == 1 ? 2 : 1);
	int try_1, try_2, try_3;
	bool found_in_cache = false;

	// If previously computed, return result from cache
	// The cache tells if the starting player or the other play wins
	if (winner_cache[stones - 1] != 0) {
		found_in_cache = true;
		winner =
			(winner_cache[stones - 1] == 1 ?  current_player : other_player);
	}
	else if (stones >= 2 && stones <= 5) {
		winner = current_player;
	}
	else if (stones == 1) {
		winner = other_player;
	}
	else {
		// This player can make one of 3 moves after which the other player is
		// deemed to start the game with the remaining stones (for each move).
		// If the other players wins in each of those 3 scenarios, then that
		// player wins the game when started by this player.
		try_1 = get_winner(stones - 2, other_player, winner_cache);
		try_2 = get_winner(stones - 3, other_player, winner_cache);
		try_3 = get_winner(stones - 5, other_player, winner_cache);

		if (try_1 == other_player && try_2 == other_player
				&& try_3 == other_player) {
			winner = other_player;
		}
		else {
			winner = current_player;
		}
	}

	if (! found_in_cache) {
		winner_cache[stones - 1] = (winner == current_player ? 1 : 2);
	}

	return winner;

} // get_winner

int main() {

	int tests, stones, current_player, winner;
	int winner_cache[MAX_STONES_COUNT] = {0};

	cin >> tests;

	for (int t = 0; t < tests; t++) {
		cin >> stones;
		current_player = 1;

		winner = get_winner(stones, current_player, winner_cache);

		cout << (winner == 1 ? "First" : "Second") << endl;
	}

	return 0;
}
