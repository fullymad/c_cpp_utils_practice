/******************************************************************************
https://www.hackerrank.com/challenges/xor-se/problem
******************************************************************************/

/*****
Here is a solution that needs to be coded and tested
----------------------------------------------------

A0 = 0
A1 = A0 xor 1
A2 = A1 xor 2 (or) 1 xor 2
A3 = 1 xor 2 xor 3
An = 1 xor 2 xor 3 ....... xor n

A1 xor A2 xor A3 xor A4 = 1 xor 1xor2 xor 1xor2xor3 xor 1xor2xor3xor4

Going backwards, get each 4 elements
In each pair within those, all elements cancel out except the differing last
number.
    1 .. n-1
    1 .. n-2
    1 .. n-3
    1 .. n-4

1 .. n-1 xor 1 .. n-2 = n-2
1 .. n-3 xor 1 .. n-4 = n-4

n-2 xor n-4 = 2 if both are odd (diff is in bit 1)
n-2 xor n-4 = 6 if both are even (diff is in bits 1 and 2)

start, end are input parameters

count = end  - start + 1;

sets_of_four = count / 4;
result = 0;
if (end % 2 == 1) {
	if (sets_of_four % 2 == 1) {
		result = 2;
	}
}
else {
	if (sets_of_four % 2 == 1) {
		result = 6;
	}
}
remaining = count % 4;
if (remaining == 3) {
	// xor of the second and third results in the third number left over
	result = result xor (start + 2);
	remaining = 1;
}
else if (remaining == 2) {
	result = result xor (start + 1);
}

if (remaining == 1) {
	// Must be a way to optimize xor of a sequence, maybe use boundaries of
	// power of 2
	// Maybe: How many times is each of 16 bits set? For each bit, find if odd
	// or even number of times and set that accordingly
	for (i = 1; i <= start; i++) {
		result = result xor i;
	}
}

return result;
*****/
