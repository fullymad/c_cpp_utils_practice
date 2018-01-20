/******************************************************************************
https://www.hackerrank.com/challenges/contacts
******************************************************************************/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

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
	vector<struct trie>::iterator it;
	bool			found_letter = false;

	Trie			new_trie;

	len = name.length();

 	ch = name[index];

	//cout << "Name: " << name << " len: " << len;
	//cout << " Index: " << index << " ch: " << ch << endl;

	vector<struct trie>	&next_tries = trie.next_letters;

	for (it = next_tries.begin(); it < next_tries.end(); ++it) {
		if (it->letter == ch) {
			it->count += 1;

			if (index < len - 1) {
				add_name(*it, name, index + 1);
			}

			found_letter = true;
			break;
		}
	}

	if (! found_letter) {
		new_trie.letter = ch;
		new_trie.count = 1;
		next_tries.push_back(new_trie);

		if (index < len - 1) {
			add_name(next_tries.back(), name, index + 1);
		}
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
	vector<struct trie>::iterator it;

	len = partial.length();

	ch = partial[index];

	//cout << "Partial: " << partial << " len: " << len;
	//cout << " Index: " << index << " ch: " << ch << endl;

	vector<struct trie>	&next_tries = trie.next_letters;

	for (it = next_tries.begin(); it < next_tries.end(); ++it) {
		//cout << "letter: " << it->letter;
		//cout << "count: " << it-> count << endl;

		if (it->letter == ch) {
			if (index == len - 1) {
				count = it->count;
			}
			else {
				count = find_partial(*it, partial, index + 1);
			}

			break;
		}
	}

	return count;

} /* find_partial */


int main() {
	int		ops;
	string	operation;
	string	name;
	int		count;
	Trie 	trie;

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
