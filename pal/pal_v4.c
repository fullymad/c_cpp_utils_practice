/*****************************************************************************
You have two strings,  and . Find a string, , such that:

 can be expressed as  where  is a non-empty substring of  and  is a non-empty substring of .
 is a palindromic string.
The length of  is as long as possible.
For each of the  pairs of strings ( and ) received as input, find and print string  on a new line. If you're able to form more than one valid string , print whichever one comes first alphabetically. If there is no valid answer, print  instead.

Input Format

The first line contains a single integer, , denoting the number of queries. The subsequent lines describe each query over two lines:

The first line contains a single string denoting .
The second line contains a single string denoting .
Constraints



 and  contain only lowercase English letters.
Sum of |a| over all queries does not exceed 
Sum of |b| over all queries does not exceed 
Output Format

For each pair of strings ( and ), find some  satisfying the conditions above and print it on a new line. If there is no such string, print  instead.

Sample Input

3
bac
bac
abc
def
jdfh
fds
Sample Output

aba
-1
dfhfd
Explanation

We perform the following three queries:

Concatenate  with  to create .
We're given  and ; because both strings are composed of unique characters, we cannot use them to form a palindromic string. Thus, we print .
Concatenate  with  to create . Note that we chose these particular substrings because the length of string  must be maximal.
*****************************************************************************/

/* Following needed for strdup declaration to be picked up */
#define _BSD_SOURCE

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_STR_SIZE 100001
#define MAX_INPUT_COUNT 10

#define NUM_DISTINCT_CHARS 26
#define NO_MATCH_FOUND -1

#define PARSE_FORWARD 0
#define PARSE_BACKWARD 1

typedef struct StrPair {
	char	*first_str;
	char	*second_str;
} StrPair;

/*****************************************************************************
* Returns True if the specific substring of the given string is a palindrome.
* The substring is defined by the given start and end indices of the input
* string.
*
* NOTE: Special case - a single character is considered a palindrome.
*
* Input:
*   str - Input string
*   start_index - Index of the first character of the substring
*   end_index - Index of the last character of the substring
*
* Returns:
*   1 if the substring is a palindrome, 0 otherwise.
*****************************************************************************/
static int
is_palindrome(
	char	*str,
	int		start_index,
	int		end_index
)
{
	int 	palindrome = 0; /* For now, NOT a palindrome */

	assert (start_index <= end_index);

	while (str[start_index] == str[end_index]) {
		start_index++;
		end_index--;

		if (start_index >= end_index) {
			palindrome = 1;
		}
	}

	return palindrome;
} /* end is_palindrome */

/*****************************************************************************
* Returns a specific string index from the list of indices corresponding to the
* given character
*
* ASSUMPTION: First element of array tells the count of stored indices
*
* Input:
*   matched_indices: Array of pointers to lists of indices corresponding to
*     letters 'a' through 'z' (all lowercase)
*   matched_char: One of 'a' - 'z' whose list needs to be used
*   match_num: If 'n', the nth string index where match found for this
*     character. This value will be 1 through count of indices in list.
*   parse_direction: PARSE_FORWARD for nth index from start of string and
*     PARSE_BACKWARD for nth index going back from end of string
*
* Returns
*   The string index for the nth match
*
* EXAMPLE data:
*   When character 'd' is matched with the string "divided", the 4th element
*     of matched_indices will point to an integer array of size 4. The elements
*     of this integer array (0 throu 3) will be 3, 0, 4, 6. Element 0 has the
*     count of 3 (as there are 3 occurrences of 'd' in "divided"). As the
*     string indices that match 'd' are 0, 4 and 6, the last 3 elements of the
*     integer array contain these numbers. If input has matched_char = 'd' and
*     match_num = 1, the value 0 will be returned for PARSE_FORWARD and 6 will
*     be returned for PARSE_BACKWARD (as this is match number 1 from the end).
*****************************************************************************/
static unsigned int
get_next_matched_index(
	unsigned int	*matched_indices[],
	char			matched_char,
	int				match_num,
	int				parse_direction
)
{
	unsigned int	*int_list_ptr;
	unsigned int	matched_pos;
	int				element_id;

	assert(matched_indices != NULL && match_num >= 1);
	assert(matched_char >= 'a' && matched_char <= 'z');

	/* Destination array holds data for 'a' through 'z' in elements 0 to 25 */
	element_id = matched_char - 'a';

	/* Get pointer to integer list for the given character */
	int_list_ptr = matched_indices[element_id];
	
	/* If character never found OR asking for beyond the last one found ...*/
	if (int_list_ptr == NULL || match_num > int_list_ptr[0]) {
		matched_pos = NO_MATCH_FOUND;
	}
	else {
		/* Reverse the order, as match_num 1 will be the last in list */
		if (parse_direction == PARSE_BACKWARD) {
			match_num = int_list_ptr[0] - match_num + 1;
		}
		matched_pos = int_list_ptr[match_num];
	}

	return matched_pos;

} /* end get_next_matched_index */

/*****************************************************************************
* Looks for the longest palindrome substring of the given string starting at
* the given index and returns the 'end' index of the substring. The direction
* of search (within the string) is either forward or backward depending on the
* input parameter.
*
* As can be seen above, only the part of the input string that is at/after OR
* at/before will be considered (for the cases of PARSE_FORWARD and
* PARSE_BACKWARD respectively).
*
* Uses the given map of characters to their locations in input string.
*
* The first character of the palindrome is fixed at the given start index and
* the return value will be at least 1 (for the special case of a single
* character palindrome).
*
* Input:
*   str - Input string
*	str_size - Length of input string
*   start_index - The first character of the palindrome
*   matched_indices: Array of pointers to lists of indices corresponding to
*     letters 'a' through 'z' (all lowercase) where str contains that letter
*   palindrome_len_cache: Cache of previously computed length for each index.
*     Caller should allocate enough space and initialize cache to set length to
*     0. It should also make sure to pass the right cache for given 'str' and
*     'parse_direction'
*   parse_direction - PARSE_FORWARD for forward match and PARSE_BACKWARD for
*     backward match
*
* Return:
*	Number of characters in the palindrome
*
* Examples:
*   'abcbd', index 1, PARSE_FORWARD - Returns 3 ('bcb')
*   'abcbd', index 2, PARSE_FORWARD - Returns 1 ('c')
*   'abbd', index 1, PARSE_BACKWARD - Returns 1 ('b')
*   'kkbkbkk', index 5, PARSE_BACKWARD - Returns 5 ('kbkbk')
*****************************************************************************/
static int
get_palindrome_len(
	char	*str,
	int		str_size,
	int		start_index,
	unsigned int *matched_indices[],
	unsigned int *palindrome_len_cache,
	int		parse_direction
)
{
	char	start_char;
	int		match_num;
	int		next_match_pos;
	int		i;
	int		count = 1;

	assert(NULL != str && start_index >= 0 && str_size > 0);

	/* If length computed before for this index, return from cache */
	if (palindrome_len_cache[start_index] != 0) {
		return palindrome_len_cache[start_index];
	}

	/* Get the first character of the palindrome using start_index */
	start_char = str[start_index];

	/* The last character of the palindrome has to be the same as start_char.
	 * For each occurrence of this character in the 'remainder' of the string,
	 * check if it is the other end of a palindrome, settling for the longest
	 * such palindrome.
	 *
	 * When searching for the palindrome from given position forward, the
	 * longest palindrome is matched by starting from the end and going
	 * backward from the matching position (and inversely when searching from
	 * given position backward), hence the flipping of direction when invoking
	 * function that returns matching position.
	 */

	if (PARSE_FORWARD == parse_direction) {
		match_num = 1;
		while (1) {
			next_match_pos = get_next_matched_index(matched_indices,
				start_char, match_num, PARSE_BACKWARD);

			if (next_match_pos == NO_MATCH_FOUND ||
				next_match_pos <= start_index) {
				break;
			}

/* TODO
    If prev index in cache has len > 2 AND (next_match_pos - start_index + 1)
    == (len - 2), count = len - 2 & break ELSE is_palindrome() ...
*/
			if (is_palindrome(str, start_index, next_match_pos)) {
				count = next_match_pos - start_index + 1;
				break;
			}
			match_num++;
		}
	}
	else { /* PARSE_BACKWARD */
		match_num = 1;
		while (1) {
			next_match_pos = get_next_matched_index(matched_indices,
				start_char, match_num, PARSE_FORWARD);

			if (next_match_pos == NO_MATCH_FOUND ||
				next_match_pos >= start_index) {
				break;
			}

			if (is_palindrome(str, next_match_pos, start_index)) {
				count = start_index - next_match_pos + 1;
				break;
			}
			match_num++;
		}
	}

	/* Update cache with the computed length */
	palindrome_len_cache[start_index] = count;

	return count;
} /* end get_palindrome_len */

/*****************************************************************************
* Utility function to concatenate 2 strings and copy into provided buffer.
*
* Input:
*   s1 - First string
*   count1 - Number of characters to copy (NO check for NULL terminator)
*   s2 - Second string
*   count2 - Number of characters to copy (NO check for NULL terminator)
*
* Output:
*   result_str - Updated with concatenated string
*****************************************************************************/
static void
concat_sub_strs(
	char	result_str[],
	char	*s1,
	int		count1,
	char	*s2,
	int		count2
)
{
	strncpy(result_str, s1, count1);
	strncpy(result_str + count1, s2, count2);
	result_str[count1 + count2] = '\0';

	return;
} /* end concat_sub_strs */

/*****************************************************************************
* Utility function to process the new matched string and store it in given
* buffer if needed. Assumes that the length of the new string >= previously
* stored string in the buffer and that the buffer has sufficient memory for the
* new string. If it is equal in length (already determined by caller and passed
* in as a boolean parameter), stores new string only if it is alphabetically
* ahead of the previous one. The new string is passed in as 2 substrings to be
* concatenated together.
*
* Input:
*   result_str - Pointer to the previous stored string
*   s1 - First string whose indices s1_low and s1_high denote the first
*        substring (both positions included)
*   s2 - Second string whose indices s2_low and s2_high denote the second
*        substring (both positions included)
*   s1_low, s1_high, s2_low, s2_high - As explained above
*   same_length - True if new string of the same length, so only stored if
*         alphabetically ahead
*
* Output:
*   result_str - Potentially updated with the given 2 substrings
*****************************************************************************/
static void
process_new_match(
	char	result_str[],
	char	*s1,
	int		s1_low,
	int		s1_high,
	char	*s2,
	int		s2_low,
	int		s2_high,
	int		same_length
)
{
	int		len_first_part, len_second_part;
	int		need_to_store = 1;
	int		cmp_result;
	/* DEBUG
	char	dbg_result[2 * MAX_STR_SIZE];
	 */

	len_first_part = s1_high - s1_low + 1;
	len_second_part = s2_high - s2_low + 1;

	assert(s1 && s2 && len_first_part > 0 && len_second_part > 0);

	/* DEBUG
	concat_sub_strs(dbg_result, s1 + s1_low, len_first_part,
					s2 + s2_low, len_second_part);
	printf("Matched %s\n\n", dbg_result);
	*/

/* TODO
    Instead of copying into result_str for every longer match, store the
    substrings as (offset, count). While comparing below, compare in 3 steps
    if the previous and current substring lengths vary. For example, if the
    split was 7/5 before and 5/7 now, compare new s1 part with 5 characters of
    old s1, followed by 2 characters of new s2 part with last 2 characters of
    old s1, followed by last 5 characters of new 2 part with old s2.
*/

	/* If same length, check if new string is alphabetically ahead */
	if (same_length) {
		/* Compare with first substring */
		cmp_result = strncmp(s1 + s1_low, result_str, len_first_part);

		if (cmp_result > 0) {
			need_to_store = 0;
		}
		/* Compare with second substring if first part identical */
		else if (0 == cmp_result) {
			cmp_result = strncmp(s2 + s2_low, result_str + len_first_part,
				len_second_part);
			if (cmp_result >= 0) {
				need_to_store = 0;
			}
		}
	} /* if same length */

	if (need_to_store) {
		concat_sub_strs(result_str, s1 + s1_low, len_first_part,
						s2 + s2_low, len_second_part);
	}

	return;
} /* end process_new_match */

/*****************************************************************************
* Map each character ('a' through 'z' all lowercase), to the list of indices
* where it is found in the given string.
*
* EXAMPLE data:
*   If the string is "divided", character 'd' will be mapped to the list of
*   integers 0, 4 and 6 as those are the indices of the string where 'd' is
*   found. This map is stored in an integer array whose element 0 has the
*   count (3 in this case) and the remaining elements contain the indices
*   0, 4 and 6 in this case) as in {3, 0, 4, 6}.
*
* Input:
*   source_str: Source string (Assumed to only contain 'a' through 'z')
*
* Returns:
*   Pointer to a newly allocated array of integer pointers, each corresponding
*   to a letter from 'a' to 'z'. Each integer pointer, in turn, is the start
*   of an array of integers. If a letter is not found in the string, the
*   top level pointer will be NULL.
*****************************************************************************/
static unsigned int **
map_chars_to_matching_str_pos(
	char	*source_str
)
{
	unsigned int	**result_vector;
	unsigned int	*indices_ptr;
	unsigned int	counts[NUM_DISTINCT_CHARS] = {0};
	char			*ptr = NULL;
	unsigned int	source_len = 0; /* Length of source string */
	int				source_i; /* Index into source string */
	int				i;

	assert(source_str != NULL);

	/* First pass to get count of occurrences of each letter */
	ptr = source_str;
	source_len = 0;
	for (ptr = source_str; *ptr != '\0'; ptr++) {
		assert(*ptr >= 'a' && *ptr <= 'z');
		counts[*ptr - 'a'] += 1;
		source_len++;
	}

	result_vector = (unsigned int **)malloc(
				sizeof(unsigned int *) * NUM_DISTINCT_CHARS); 
	assert(result_vector != NULL);

	/* Allocate memory for indices matched for all characters */
	for (i = 0; i < NUM_DISTINCT_CHARS; i++) {
		if (counts[i] == 0) {
			result_vector[i] = NULL;
		}
		else {
			result_vector[i] = (unsigned int *)malloc(
					sizeof(unsigned int) * (counts[i] + 1));
			assert(result_vector[i]);
			result_vector[i][0] = 0; /* Initialize count for this character */
		}
	}

	/* Second pass to store indices each character is matched at */
	for (source_i = 0; source_i < source_len ; source_i++) {
		i = source_str[source_i] - 'a'; /* Character's position in vector */
		indices_ptr = result_vector[i]; /* List of indices for this letter */
		indices_ptr[0] += 1; /* Increment number of matching indices */
		indices_ptr[indices_ptr[0]] = source_i;
	}

	return(result_vector);

} /* end map_chars_to_matching_str_pos */

/*****************************************************************************
* Given 2 strings s1 and s2, finds and prints the string s that satisfies
* conditions below.
*   - s = s1_sub + s2_sub where s1_sub and s2_sub are non-empty substrings of s1
*   and s2 respectively.
*   - s is a palindromic string
*   - s is as long as possible
*****************************************************************************/
static void
find_max_len_palindrome(
	char	*s1,
	char	*s2
)
{
	int i, j, inner_i, s1_len, s2_len;
	int result_len = 0;
    char result_str[2 * MAX_STR_SIZE];
	int tmp_s1_low = 0, tmp_s1_high = 0, tmp_s2_low = 0, tmp_s2_high = 0;
	int start_s2_pos;
	int matched = 0;
	int match_len = 0;
	int extra_match_len_1 = 0, extra_match_len_2 = 0;
	int match_num, next_match_pos = 0;
	int matched_s2_pos = -1; /* For matching anchor characters in s1 and s2 */

	assert(s1 && s2);

	s1_len = (int)strlen(s1);
	s2_len = (int)strlen(s2);

	assert(0 != s1_len && 0 != s2_len);

	/* Cache the indices where each character is found in s1 and s2 */
	unsigned int **map_to_s1_indices = map_chars_to_matching_str_pos(s1);
	assert(map_to_s1_indices != NULL);

	unsigned int **map_to_s2_indices = map_chars_to_matching_str_pos(s2);
	assert(map_to_s2_indices != NULL);

	/* Initialize cache that contains palindrome length starting at each
	 * position. This palindrome is within each string in forward direction
	 * starting at that position for s1 and in backward direction starting at
	 * that position for s2. Use calloc() to initialize to 0.
	 */
	unsigned int *palindrome_len_cache_s1 = (unsigned int *)calloc(
					s1_len, sizeof(unsigned int));
	assert(palindrome_len_cache_s1 != NULL);

	unsigned int *palindrome_len_cache_s2 = (unsigned int *)calloc(
					s2_len, sizeof(unsigned int));
	assert(palindrome_len_cache_s2 != NULL);

	/* The main logic is as below.
	 * - For each character in s1 (say, index i1), find each index where the
	 * character is matched in s2 (say, index j2).
	 * - Look for longest palindrome starting at s1.i1 and s2.j2 (the latter
	 * string being parsed in reverse)
	 * - Only parse starting s2 locations where this s1 character exists
	 *
	 * An array of 26 elements (for the characters 'a' to 'z') will contain
	 * pointers to integer arrays holding the matching indices in s2 for that
	 * character.
	 */

	result_str[0] = '\0';

	/* Find palindrome with substring starting at each s1 position */
	for (i = 0; i < s1_len; i++) {

		/* For each s1 position, start comparison with end of s2 in reverse */

		/* Get first location in s2 (from the end) that has this character */
		match_num = 1;
		next_match_pos = get_next_matched_index(map_to_s2_indices,
				s1[i], match_num, PARSE_BACKWARD);

		if (NO_MATCH_FOUND == next_match_pos) {
			continue;
		}
		else {
			start_s2_pos = next_match_pos;
		}

		/* If current match length is already more than what we will get if all
		 * the remaining characters matched, finish checking. */
		if ((s1_len - i + start_s2_pos + 1) < result_len) {
			break;
		}

		while (start_s2_pos >= 0) {

			/* If current match length is already more than what we will get if
			 * all the remaining characters matched, go to next s1 index.
			 */
			if ((s1_len - i + start_s2_pos + 1) < result_len) {
				break;
			}

			matched = 0;
			match_len = 0;
			for (j = start_s2_pos, inner_i = i;
					j >= 0 && inner_i < s1_len; j--, inner_i++) {

				if (s1[inner_i] == s2[j]) {

					/* If matched anchor character from s1 ... */
					if (inner_i == i) {
						/* Mark that matched s2 position should be cached */
						matched_s2_pos = j;

						/* If previous s1 position and next s2 position
						 * match, any new matched string will only be a subset
						 * of an earlier match, so no need to match further -
						 * pretend no match at all.
						 */
						if ( inner_i > 0 && j < (s2_len - 1)
							&& s1[inner_i - 1] == s2[j + 1]
							) {

							matched = 0; /* As we look for the next match */
							match_len = 0;
							/* Out of for, so start with previous s2 position */
							break;
						}
						
					}

					if (! matched) {
						tmp_s1_low = tmp_s1_high = inner_i;
						tmp_s2_low = tmp_s2_high = j;
						matched = 1;
					}
					else {
						tmp_s1_high++;
						tmp_s2_low--;
					}
					match_len += 2;
				}
				else {
					if (matched) {
						/* Some of the remaining characters in either string
						 * can potentially form a palindrome separately, thus
						 * extending the matched palindrome, so extend the
						 * string with the better matching addition (with
						 * consideration for the alphabetic order).
						 */

						/* Get palindrome lengths from rest of s1 and s2 */
						extra_match_len_1 = get_palindrome_len(s1, s1_len,
							tmp_s1_high + 1, map_to_s1_indices,
							palindrome_len_cache_s1, PARSE_FORWARD);
						extra_match_len_2 = get_palindrome_len(s2, s2_len,
							tmp_s2_low - 1, map_to_s2_indices,
							palindrome_len_cache_s2, PARSE_BACKWARD);

						/* Pick the longer of the 2 and if same length, pick
						 * the one alphabetically ahead
						 */
						if (extra_match_len_1 > extra_match_len_2) {
								tmp_s1_high += extra_match_len_1;
								match_len += extra_match_len_1;
						}
						else if (extra_match_len_2 > extra_match_len_1) {
								tmp_s2_low -= extra_match_len_2;
								match_len += extra_match_len_2;
						}
						else if (s1[inner_i] <= s2[j]) {
								tmp_s1_high += extra_match_len_1;
								match_len += extra_match_len_1;
						}
						else {
								tmp_s2_low -= extra_match_len_2;
								match_len += extra_match_len_2;
						}

						if (match_len >= result_len) {
							/* Copy new match and set result_len */
							process_new_match(result_str,
								s1, tmp_s1_low, tmp_s1_high,
								s2, tmp_s2_low, tmp_s2_high,
								match_len == result_len ? 1 : 0);
							result_len = match_len;
						}
					}
					matched = 0; /* As we look for the next match */
					match_len = 0;
					break; /* Out of for, so start with previous s2 position */
				}
			} /* for loop for comparing substrings from s1 and s2 */

			/* If still matched, reached end of s1 or s2 or both. Process
			 * matched substrings */
			if (matched) {
				/* Some of the remaining characters in either string
				 * can potentially form a palindrome separately, thus
				 * extending the matched palindrome, so extend the string
				 * that is alphabetically preferred
				 */
				if (inner_i < s1_len) { /* Reached end of s2 */
					extra_match_len_1 = get_palindrome_len(s1, s1_len,
						tmp_s1_high + 1, map_to_s1_indices,
						palindrome_len_cache_s1, PARSE_FORWARD);
					tmp_s1_high += extra_match_len_1;
					match_len += extra_match_len_1;
				}
				else if (j >= 0) { /* Reached end of s1 */
					extra_match_len_2 = get_palindrome_len(s2, s2_len,
						tmp_s2_low - 1, map_to_s2_indices,
						palindrome_len_cache_s2, PARSE_BACKWARD);
					tmp_s2_low -= extra_match_len_2;
					match_len += extra_match_len_2;
				}

				if (match_len >= result_len) {
					/* Copy new match if qualifies and set result_len */
					process_new_match(result_str,
						s1, tmp_s1_low, tmp_s1_high,
						s2, tmp_s2_low, tmp_s2_high,
						match_len == result_len ? 1 : 0);
					result_len = match_len;
				}
				matched = 0; /* As we look for the next match */
				match_len = 0;
			}

			/* Get next s2 position where s1 character matched before */
			match_num++;
			start_s2_pos = get_next_matched_index(map_to_s2_indices,
					s1[i], match_num, PARSE_BACKWARD);
		} /* while some substring to compare in s2 for this s1 index */
	} /* main for each character in s1 */

	/* Free the 2 caches of matched s1 and s2 indices for each character */
	for (i = 0; i < NUM_DISTINCT_CHARS; i++) {
		if (NULL != map_to_s1_indices[i]) {
			free(map_to_s1_indices[i]);
		}
	}
	free(map_to_s1_indices);

	for (i = 0; i < NUM_DISTINCT_CHARS; i++) {
		if (NULL != map_to_s2_indices[i]) {
			free(map_to_s2_indices[i]);
		}
	}
	free(map_to_s2_indices);

	if (result_str[0] == '\0') {
		strcpy(result_str, "-1");
	}

	/* Free the 2 caches that store the palindrome lengths */
	free(palindrome_len_cache_s1);
	free(palindrome_len_cache_s2);

	printf("%s\n", result_str);

	return;
} /* end find_max_len_palindrome */

int main(int argc, const char *argv[])
{
	int		i;
	int		count = 0;
	StrPair	input_pair[MAX_INPUT_COUNT];
	char	first_str[MAX_STR_SIZE];
	char	second_str[MAX_STR_SIZE];

    scanf("%d", &count);

	assert(count > 0 && count <= 10);

	/* Gather all input */
    for (i = 0; i < count; i++) {
        scanf("%s", first_str);
        scanf("%s", second_str);

		assert('\0' != first_str[0] && '\0' != second_str[0]);

		input_pair[i].first_str = strdup(first_str);
		input_pair[i].second_str = strdup(second_str);

		assert(NULL != input_pair[i].first_str &&
				NULL != input_pair[i].second_str);
    }

	/* Process all input */
    for (i = 0; i < count; i++) {
		find_max_len_palindrome(input_pair[i].first_str,
			input_pair[i].second_str);

		free(input_pair[i].first_str);
		free(input_pair[i].second_str);
	}

    return 0;
}
