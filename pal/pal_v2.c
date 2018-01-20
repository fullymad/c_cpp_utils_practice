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
#define FIRST_TIME_PROCESSED -2
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
* Looks for the longest palindrome substring of the given string starting at
* the given index and returns the 'end' index of the substring. The direction
* of search (within the string) is either forward or backward depending on the
* input parameter.
*
* As can be seen above, only the part of the input string that is at/after OR
* at/before will be considered (for the cases of PARSE_FORWARD and
* PARSE_BACKWARD respectively).
*
* The first character of the palindrome is fixed at the given start index and
* the return value will be at least 1 (for the special case of a single
* character palindrome).
*
* Input:
*   str - Input string
*	str_size - Length of input string
*   start_index - The first character of the palindrome
*   parse_direction - PARSE_FORWARD for forward search and PARSE_BACKWARD for
*     backward search
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
	int		parse_direction
)
{
	char	start_char;
	int		i;
	int		count = 1;

	assert(NULL != str && start_index >= 0 && str_size > 0);

	/* Get the first character of the palindrome using start_index */
	start_char = str[start_index];

	/* The last character of the palindrome has to be the same as start_char.
	 * For each occurrence of this character in the 'remainder' of the string,
	 * check if it is the other end of a palindrome, settling for the longest
	 * such palindrome.
	 */

	if (PARSE_FORWARD == parse_direction) {
		for (i = str_size - 1; i > start_index; i--) {
			if (str[i] == start_char) {
				if (is_palindrome(str, start_index, i)) {
					count = i - start_index + 1;
					break;
				}
			}
		}
	}
	else { /* PARSE_BACKWARD */
		for (i = 0; i < start_index; i++) {
			if (str[i] == start_char) {
				if (is_palindrome(str, i, start_index)) {
					count = start_index - i + 1;
					break;
				}
			}
		}
	}

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
	char	dbg_result[2 * MAX_STR_SIZE];

	len_first_part = s1_high - s1_low + 1;
	len_second_part = s2_high - s2_low + 1;

	assert(s1 && s2 && len_first_part > 0 && len_second_part > 0);

	/* DEBUG
	concat_sub_strs(dbg_result, s1 + s1_low, len_first_part,
					s2 + s2_low, len_second_part);
	printf("Matched %s\n\n", dbg_result);
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
* Saves the source list of indices into a new list corresponding to the given
* character. The new list pointer is stored into an array of such pointers, one
* for each of 'a' through 'z' (all lowercase).
*
* NOTE: Memory is allocated for the new list. Caller should free it when done.
*
* NOTE: Source list is REINITIALIZED to be an empty list of indices.
* 
* The idea is that the source list is a temporary one that can hold the
* maximum number of such indices and is built as each character is matched. The
* new list will only have memory allocated to hold the actual number of such
* indices for this specific character.
*
* Input:
*   matched_indices_source: Source array (element 0 = count of indices that
*     follow in the array)
*   matched_indices_dest: Array of pointers to lists of indices corresponding
*     to letters 'a' through 'z' (all lowercase)
*   matched_char: One of the characters 'a' through 'z'
*****************************************************************************/
static void
save_matched_str2_pos_from_staging(
	unsigned int	matched_indices_source[],
	unsigned int	*matched_indices_dest[],
	char			matched_char
)
{
	int				i, element_id, count;
	unsigned int	*dest_ptr;
	size_t			mem_size;

	assert(matched_indices_source != NULL && matched_indices_dest != NULL);
	assert(matched_char >= 'a' && matched_char <= 'z');

	/* Destination array holds data for 'a' to 'z' in elements 0 through 25 */
	element_id = matched_char - 'a';

	/* Relevant element should be 'clean' on entry */
	assert(matched_indices_dest[element_id] == NULL);

	count = matched_indices_source[0]; /* Element 0 has the count */

	/* Space for count + actual number of elements in source */
	mem_size = sizeof(unsigned int) * (count + 1);
	dest_ptr = (unsigned int *)malloc(mem_size);

	assert(dest_ptr != NULL);

	matched_indices_dest[element_id] = dest_ptr;
	dest_ptr[0] = count;
	for (i = 1; i <= count; i++) {
		dest_ptr[i] = matched_indices_source[i];
	}

	/* REINITIALIZE source list to be empty */
	matched_indices_source[0] = 0;

	return;

} /* end save_matched_str2_pos_from_staging */

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
*
* Returns
*   The string index for the nth match
*
* EXAMPLE data:
*   When character 'd' is matched with the string "divided", the 4th element
*     of matched_indices will point to an integer array of size 4. The elements
*     of this integer array (0 throu 3) will be 3, 6, 4, 0. Element 0 has the
*     count of 3 (as there are 3 occurrences of 'd' in "divided"). As the
*     string indices that match 'd' are 0, 4 and 6, the last 3 elements of the
*     integer array contain these numbers (in reverse order though). If input
*     has matched_char = 'd' and match_num = 1, the value 6 will be returned
*     as this is match number 1 (from the end).
*****************************************************************************/
static unsigned int
get_next_matched_str2_pos(
	unsigned int	*matched_indices[],
	char			matched_char,
	int				match_num
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

	/* If list not found, character is being processed for the first time */ 
	if (int_list_ptr == NULL) {
		matched_pos = FIRST_TIME_PROCESSED;
	}
	/* Match number exceeded number of matched indices */
	else if (match_num > int_list_ptr[0]) { /* Element 0 holds count */
		matched_pos = NO_MATCH_FOUND;
	}
	else {
		matched_pos = int_list_ptr[match_num];
	}

	return matched_pos;

} /* end get_next_matched_str2_pos */

/*****************************************************************************
* Stores the given index (of string) into the list of indices in the given
* integer array (whose element 0 tells the number of such stored indices).
* 
* ASSUMPTION: First element of array tells the currrent count of stored indices
*
* Input:
*   matched_indices: Destination integer array
*   index_to_add: Index to add to the end of the array
*****************************************************************************/
static void
add_match_pos_to_staging(
	unsigned int	matched_indices[],
	unsigned int	index_to_add
)
{
	unsigned int	count_indices;

	assert(matched_indices != NULL);

	matched_indices[0]++; /* Bump count of matched indices */
	count_indices = matched_indices[0];

	matched_indices[count_indices] = index_to_add; /* Add to last location */

	return;

} /* end add_match_pos_to_staging */

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
	int new_s1_high = 0, new_s2_low = 0;
	int start_s2_pos;
	int matched = 0;
	int match_len = 0;
	int extra_match_len_1 = 0, extra_match_len_2 = 0;
	int match_num, next_match_pos = 0;
	int matched_s2_pos = -1; /* For matching anchor characters in s1 and s2 */
	unsigned int *matched_indices[NUM_DISTINCT_CHARS] = {NULL};

	/* Staging area sized for worst case of same s1 character in all of s2 */
	unsigned int matched_indices_staging[MAX_STR_SIZE];

	assert(s1 && s2);

	s1_len = strlen(s1);
	s2_len = strlen(s2);

	assert(0 != s1_len && 0 != s2_len);

	/* The main logic is as below.
	 * - For each character in s1 (say, index i1), find each index where the
	 * character is matched in s2 (say, index j2).
	 * - Look for longest palindrome starting at s1.i1 and s2.j2 (the latter
	 * string being parsed in reverse)
	 * - Need to make sure that only the first occurrence of a given character
	 * (say, 'a') in s1 should result in all the characters of s2 being
	 * checked. The subsequent occurrences should look up a cache of which
	 * indices of s2 contain 'a' and only parse starting those locations.
	 *
	 * An array of 26 elements (for the characters 'a' to 'z') will contain
	 * pointers to integer arrays holding the matching indices in s2 for that
	 * character.
	 */

	matched_indices_staging[0] = 0;
	result_str[0] = '\0';

	/* Find palindrome with substring starting at each s1 position */
	for (i = 0; i < s1_len; i++) {

		/* If a specific s1 character was encountered for the first time in the
		 * previous iteration, populate the cache from the data in the
		 * staging area (accumulated during the first pass for this particular
		 * character). */
		if (FIRST_TIME_PROCESSED == next_match_pos) {
			save_matched_str2_pos_from_staging(matched_indices_staging,
				matched_indices, s1[i - 1]);
		}

		/* For each s1 position, start comparison with end of s2 in reverse */

		/* If this s1 character previously encountered, get first location in
		 * s2 (from the end) that had a match */
		match_num = 1;
		next_match_pos = get_next_matched_str2_pos(matched_indices,
				s1[i], match_num);

		if (FIRST_TIME_PROCESSED == next_match_pos) {
			/* s1 character seen for first time, so start from end of s2 */
			start_s2_pos = s2_len - 1;
		}
		else if (NO_MATCH_FOUND == next_match_pos) {
			/* s1 character seen before, but no match in s2 at all */
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
			 * NOTE: Remove this optimization for the first occurrence of this
			 * particular s1 character since cache of s2 hits needs to be
			 * built.
			 */
			if ( ((s1_len - i + start_s2_pos + 1) < result_len) 
					&& (!FIRST_TIME_PROCESSED) ) {
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
							&& (!FIRST_TIME_PROCESSED) ) {

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
							tmp_s1_high + 1, PARSE_FORWARD);
						extra_match_len_2 = get_palindrome_len(s2, s2_len,
							tmp_s2_low - 1, PARSE_BACKWARD);

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
						tmp_s1_high + 1, PARSE_FORWARD);
					tmp_s1_high += extra_match_len_1;
					match_len += extra_match_len_1;
				}
				else if (j >= 0) { /* Reached end of s1 */
					extra_match_len_2 = get_palindrome_len(s2, s2_len,
						tmp_s2_low - 1, PARSE_BACKWARD);
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

			if (FIRST_TIME_PROCESSED == next_match_pos) {
				start_s2_pos--;

				/* If the anchor s1 character matched at all, add to staging
				 * so that the cache can be built */
				if (matched_s2_pos >= 0) {
					add_match_pos_to_staging(matched_indices_staging,
						matched_s2_pos);
					matched_s2_pos = -1;
				}
			}
			else {
				/* Get next s2 position where s1 character matched before */
				match_num++;
				start_s2_pos = get_next_matched_str2_pos(matched_indices,
					s1[i], match_num);
			}
		} /* while some substring to compare in s2 for this s1 index */
	} /* main for each character in s1 */

	/* Free cache of matched s2 indices for each character found in s1 */
	for (i = 0; i < NUM_DISTINCT_CHARS; i++) {
		if (NULL != matched_indices[i]) {
			free(matched_indices[i]);
		}
	}

	if (result_str[0] == '\0') {
		strcpy(result_str, "-1");
	}

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
