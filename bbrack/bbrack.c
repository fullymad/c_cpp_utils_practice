/*****************************************************************************
https://www.hackerrank.com/challenges/ctci-balanced-brackets/problem
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
	char	next_char;
	char	matching_left;

	char	stack[1000]; /* Stack to hold the longest input string */
	int		stack_top = -1;

	bool	result = true;

	assert(expression != NULL);

	for (i = 0; expression[i] != '\0'; i++) {
		next_char = expression[i];

		if (is_left_bracket(next_char)) { /* Hit left bracket */
			stack_top++;
			stack[stack_top] = next_char;
			continue;
		}
		else { /* Hit right bracket */
			matching_left = get_matching_left(next_char);

			if (stack_top == -1 || stack[stack_top] != matching_left) {
				/* None or different type of left bracket, so unbalanced */
				result = false;
				break;
			}
			else {
				stack_top--;
			}
		}
	} /* for each character in input */

	/* If any left bracket left to be matched, it is unbalanced */
	if (stack_top != -1) {
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
