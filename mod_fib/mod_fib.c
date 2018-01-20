/****************************************************************************
Given terms ti and ti+1 and  where , term ti+2 is computed using the following relation:

	ti+2 = ti + (ti+1)2

For example, if term  and , term , term , term , and so on.

Given three integers, t1, t2, and n, compute and print term tn of a modified Fibonacci sequence.

Note: The value of tn may exceed the range of a -bit integer. Many submission languages have libraries that can handle such large results but, for those that don't (e.g., C++), you will need to be more creative in your solution to compensate for the limitations of your chosen submission language.

Input Format

A single line of three space-separated integers describing the respective values of , , and .

Constraints



 may exceed the range of a -bit integer.
Output Format

Print a single integer denoting the value of term  in the modified Fibonacci sequence where the first two terms are  and .

Sample Input

0 1 5
Sample Output

5
Explanation

The first two terms of the sequence are t1 = 0 and 52 = 1, which gives us a modified Fibonacci sequence of {0,1,1,2,5,27}. Because n = 5, we print term t5, which is 5.
****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
/* Head ends here */

int main() {
    int t1, t2, n;
	double res, d_t1, d_t2;
	int i;

    scanf("%d %d %d", &t1, &t2, &n);

	assert (t1 >= 0 && t1 <= 2 && t2 >= 0 && t2 <= 2 && n >=3 && n<= 20);

	d_t1 = t1;
	d_t2 = t2;

    for (i=3;i<=n;i++) {
		res = d_t1 + d_t2 * d_t2;
		d_t1 = d_t2;
		d_t2 = res;
    }

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
	printf("%f\n",res);  
    return 0;
}
