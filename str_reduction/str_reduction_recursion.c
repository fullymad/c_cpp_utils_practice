/****************************************************************************
Given a string consisting of letters, '', '' and '', we can perform the following operation: Take any two adjacent distinct characters and replace them with the third character. For example, if '' and '' are adjacent, they can replaced by ''. Find the smallest string which we can obtain by applying this operation repeatedly?

Input Format: 
The first line contains the number of test cases .  test cases follow. Each test case contains the string you start with.

Constraints:


The string will have at most  characters.
Output Format: 
Output  lines, one for each test case, containing the smallest length of the resultant string after applying the operations optimally.

Sample Input:

3  
cab  
bcab  
ccccc
Sample Output:

2  
1  
5
****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
/* Head ends here */

#define MAX_ARR_SIZE 100001

/****************************************************************************
* Input:
*   Any distinct 2 of the 3 characters a, b and c.
*   RESULT UNPREDICTABLE if input is NOT DISTINCT or NOT in this set.
*
* Return:
*   Returns the 3rd character (the one not in the input) 
*
* Example:
*   Input: a,c Return: b
****************************************************************************/
char
getThirdChar(
	char first,
	char second
)
{
	char ret_ch = ' ';
	char tmp_ch = ' ';

	/* Order them ascending */
	if (first > second) {
		tmp_ch = first;
		first = second;
		second = tmp_ch;
	}

	if (first == second) {
		ret_ch = first;
	}
	else if ((second - first) == 2) { /* Got a and c */
		ret_ch = 'b';
	}
	else if (first == 'a') { /* Got a and b */
		ret_ch = 'c';
	}
	else {
		ret_ch = 'a';
	} 

	return ret_ch; 

} /* end getNewChar */

int stringReduction(char a[]) {
	char tmp_ch = ' ';
	int len = 0;

	if (a[0] == '\0') {
		len =  0;
	}
	else if (a[1] == '\0') {
		len = 1;
	}
	else {
		len = stringReduction(a + 1);

		if (a[0] == a[1]) {
			len = len + 1;
		}
		else {
			tmp_ch = getThirdChar(a[0], a[1]);
			if (len % 2) { /* Odd number of the same character */
				a[0] = tmp_ch;
			}
			a[1] = '\0';
			len = 1;
		}
	}

    return len;
}

int main() {
    int res, t, i;
    scanf("%d",&t);
    char a[MAX_ARR_SIZE];
    for (i=0;i<t;i++) {
        scanf("%s",a);
        res=stringReduction(a);
        printf("%d\n",res);  
    }

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}
