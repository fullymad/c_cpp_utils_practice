/*****************************************************************************
A bracket is considered to be any one of the following characters: (, ), {, }, [, or ].

Two brackets are considered to be a matched pair if the an opening bracket (i.e., (, [, or {) occurs to the left of a closing bracket (i.e., ), ], or }) of the exact same type. There are three types of matched pairs of brackets: [], {}, and ().

A matching pair of brackets is not balanced if the set of brackets it encloses are not matched. For example, {[(])} is not balanced because the contents in between { and } are not balanced. The pair of square brackets encloses a single, unbalanced opening bracket, (, and the pair of parentheses encloses a single, unbalanced closing square bracket, ].

By this logic, we say a sequence of brackets is considered to be balanced if the following conditions are met:

It contains no unmatched brackets.
The subset of brackets enclosed within the confines of a matched pair of brackets is also a matched pair of brackets.
Given  strings of brackets, determine whether each sequence of brackets is balanced. If a string is balanced, print YES on a new line; otherwise, print NO on a new line.

Input Format

The first line contains a single integer, , denoting the number of strings. 
Each line  of the  subsequent lines consists of a single string, , denoting a sequence of brackets.

Constraints


, where  is the length of the sequence.
Each character in the sequence will be a bracket (i.e., {, }, (, ), [, and ]).
Output Format

For each string, print whether or not the string of brackets is balanced on a new line. If the brackets are balanced, print YES; otherwise, print NO.

Sample Input

3
{[()]}
{[(])}
{{[[(())]]}}
Sample Output

YES
NO
YES
*****************************************************************************/
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

bool is_left_bracket(char ch) {
	if (ch == '{' || ch == '[' || ch == '(') {
		return true;
	}
	else {
		assert(ch == '}' || ch == ']' || ch == ')');
		return false;
	}
} /* is_left_bracket */

char get_matching_left(char ch) {
	char matching_left = '\0';

	switch (ch) {
		case '}':
			matching_left = '{';
			break;
		case ']':
			matching_left = '[';
			break;
		case ')':
			matching_left = '(';
			break;
	}

	return matching_left;

} /* get_matching_left */

bool is_balanced(char expression[]) {
	int		i;
	int		left_bound = -1;
	char	next_char;
	char	matching_left;
	int		sequence_start = 0;

	bool	result = true;

	assert(expression != NULL);

	for (i = 0; expression[i] != '\0'; i++) {
		next_char = expression[i];

		if (is_left_bracket(next_char)) { /* Hit left bracket */
			left_bound = i; /* Mark where the next right should be matched */
			continue;
		}
		else { /* Hit right bracket */
			if (left_bound == sequence_start - 1) {
				/* No left bracket to match, so unbalanced */
				result = false;
				break;
			}

			matching_left = get_matching_left(next_char);
			if (expression[left_bound] != matching_left) {
				/* Found different type of left bracket, so unbalanced */
				result = false;
				break;
			}
			else {
				/* Kinda like popping the matching left bracket */
				left_bound--;
				if (left_bound == sequence_start - 1) {
					/* Possibly starting a new balanced sequence */
					sequence_start = i + 1;
					left_bound = i;
				}
			}
		}
	} /* for each character in input */

	/* If any left bracket left to be matched, it is unbalanced */
	if (result && left_bound != sequence_start - 1) {
		result = false;
	}

	return result;

} /* is_balanced */

int main(){
    int t; 
    scanf("%d",&t);
    for(int a0 = 0; a0 < t; a0++){
        char* expression = (char *)malloc(512000 * sizeof(char));
        scanf("%s",expression);
         bool answer = is_balanced(expression);
         if(answer)
          printf("YES\n");
         else
          printf("NO\n");
    }
    return 0;
}
