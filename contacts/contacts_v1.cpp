/******************************************************************************
https://www.hackerrank.com/challenges/contacts
******************************************************************************/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define NUM_LETTERS 26

typedef struct trie {
	unsigned char	letter;
	vector<struct trie> next_letters;
	unsigned int	count;
} Trie;


void add_name(
	Trie	&trie,
	string	name,
	unsigned int index
)
{
	char			ch;
	size_t			len;
	unsigned int	ch_pos;

	len = name.length();

 	ch = name[index];
	ch_pos = ch - 'a';

	//cout << "Name: " << name << " len: " << len << " ch_pos: " << ch_pos;
	//cout << " Index: " << index << " ch: " << ch << endl;

	if (trie.next_letters.size() < ch_pos + 1) {
		//cout << "Capacity: " << trie.next_letters.capacity() << endl;
		trie.next_letters.resize(ch_pos + 1);
		//cout << "Resized to: " << ch_pos + 1 << endl;
	}

	trie.next_letters[ch_pos].letter = ch;
	trie.next_letters[ch_pos].count += 1;

	if (index < len - 1) {
		add_name(trie.next_letters[ch_pos], name, index + 1);
	}

	return;

} /* add_name */


int find_partial(
	Trie	&trie,
	string	partial,
	unsigned int index
)
{
	int				count = 0;
	char			ch;
	size_t			len;
	unsigned int	ch_pos;

	len = partial.length();

	ch = partial[index];
	ch_pos = ch - 'a';

	//cout << "Partial: " << partial << " len: " << len << " ch_pos: " << ch_pos;
	//cout << " Index: " << index << " ch: " << ch << endl;

	if (trie.next_letters.size() >= ch_pos + 1 &&
			trie.next_letters[ch_pos].letter == ch) {

		if (index == len - 1) {
			count = trie.next_letters[ch_pos].count;
		}
		else {
			count = find_partial(trie.next_letters[ch_pos], partial, index + 1);
		}
	}
 
	return count;

} /* find_partial */


int main() {
	int		ops;
	Trie	trie;
	string	operation;
	string	name;
	int		count;

	trie.letter = '\0';
	trie.count = 0;

	cin >> ops;

	for (int i = 0; i < ops; i++) {
		cin >> operation;
		cin >> name;

		if (operation == "add") {
			add_name(trie, name, 0);
		}
		else if (operation == "find") {
			count = find_partial(trie, name, 0);
			cout << count << endl;
		}
		else {
			cout << "Invalid operation: " << operation << endl;
			return 1;
		}
	}

	return 0;
}
