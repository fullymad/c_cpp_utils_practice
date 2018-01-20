/*****************************************************************************
Square Subsequences

A string is called a square string if it can be obtained by concatenating two copies of the same string. For example, "abab", "aa" are square strings, while "aaa", "abba" are not. Given a string, how many (non-empty) subsequences of the string are square strings? A subsequence of a string can be obtained by deleting zero or more characters from it, and maintaining the relative order of the remaining characters.

Input Format

The first line contains the number of test cases, . 
 test cases follow. Each case contains a string, .

Output Format

Output  lines, one for each test case, containing the required answer modulo 1000000007.

Constraints: 
 
 will have at most  lowercase characters ('a' - 'z').

Sample Input

3 
aaa 
abab 
baaba

Sample Output

3 
3 
6

Explanation

For the first case, there are 3 subsequences of length 2, all of which are square strings. 
For the second case, the subsequences "abab", "aa", "bb" are square strings. 
Similarly, for the third case, "bb", "baba" (twice), and "aa" (3 of them) are the square subsequences.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_ARR_SIZE 256

/*****************************************************************************
* Copies source into dest after stripping 2 characters denoted by their
* indices in source string. Thus, dest will have 2 less characters than source.
*
* Input:
*   source: Source string
*	dest: Destination string (caller allocates memory)
*   first_pos: Index in source of the first character to strip
*   second_pos: Index in source of the second character to strip
* Return:
*   String in parameter dest
*****************************************************************************/
static void
strip_two_chars(
	char	source[],
	char	dest[],
	int		first_pos,
	int		second_pos
)
{
	int i;
	int j= 0;

	assert(source && dest);

	//printf("strip_two_chars called with %s\n", source);

	for (i = 0; source[i] != '\0'; i++) {
		if (i != first_pos && i != second_pos) {
			dest[j] = source[i];
			j++;
		}
	}
	dest[j] = '\0';

	//printf("strip_two_chars returned %s\n", dest);

	return;
} /* end strip_two_chars */

/*****************************************************************************
* Tells if the given string is a square string, that is, if it can be obtained
* by concatenating 2 copies of the same string.
*
* Input:
*   str: String to check
* Return:
*   True if str is a square string, else False
*****************************************************************************/
static int
is_square_str(
	char str[]
)
{
	int len;
	int result = 0;

	assert(str);

	//printf("is_square_str called with %s\n", str);

	len = strlen(str);

	if (len && len % 2 == 0) { /* Not odd, so potentially a square string */
		if (0 == strncmp(str, str + (len / 2), len / 2)) {
			result = 1;
		}
	}

	return result;
} /* is_square_str */

static int
square_subsequences(
	char str[],
	int start_pos
)
{
	int i, j;
	int len;
	int result = 0;
	char temp_str[MAX_ARR_SIZE];

	assert (NULL != str);

	printf("square_subsequences called with %s\n", str);

	len = strlen(str);

	if (is_square_str(str)) {
		result++;
	}

	for(i = start_pos; i < len; i++) {
		for (j = i + 1; j < len; j++) {
			strip_two_chars(str, temp_str, i, j);
			if (temp_str[0] != '\0') {
				result += square_subsequences(temp_str, i);
			}
		}
	}

	return result;
} /* end square_subsequences */

int main() {
    int result, count, i;
	int start_pos = 0;

    scanf("%d", &count);
    char str[MAX_ARR_SIZE];

    for (i=0; i<count; i++) {
        scanf("%s", str);
        result = square_subsequences(str, 0);
        printf("%d\n", result);  
    }

    return 0;
}
