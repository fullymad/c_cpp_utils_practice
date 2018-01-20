#include <stdio.h>

#include "minheap_int.h"

void static
test1()
{
	MinHeapInt	*minheap = NULL;
	unsigned int init_size = 4;
	int			min_int;

	minheap = minheap_int_create(init_size);

	/* Testing printing empty list */
	minheap_int_print(minheap);

	minheap_int_insert(minheap, 41);
	minheap_int_print(minheap);

	minheap_int_insert(minheap, 43);
	minheap_int_print(minheap);

	minheap_int_insert(minheap, 53);
	minheap_int_print(minheap);

	minheap_int_insert(minheap, 64);
	minheap_int_print(minheap);

	minheap_int_insert(minheap, 32);
	minheap_int_print(minheap);

	minheap_int_insert(minheap, 50);
	minheap_int_print(minheap);

	minheap_int_insert(minheap, 14);
	minheap_int_print(minheap);

	minheap_int_insert(minheap, 5);
	minheap_int_print(minheap);

	minheap_int_insert(minheap, 18);
	minheap_int_print(minheap);

	minheap_int_insert(minheap, 23);
	minheap_int_print(minheap);

	minheap_int_insert(minheap, 87);
	minheap_int_print(minheap);

	minheap_int_insert(minheap, 90);
	minheap_int_print(minheap);

	minheap_int_insert(minheap, 2);
	minheap_int_print(minheap);

	while (! minheap_int_is_empty(minheap)) {
		min_int = minheap_int_extract_min(minheap);
		printf("Extracted %d\n", min_int);
		printf("-------------------\n");
		minheap_int_print(minheap);
		printf("===================\n");
	}

	minheap_int_destroy(minheap);

} /* end test1 */

void static
test2()
{
	MinHeapInt	*minheap = NULL;
	unsigned int init_size = 16;
	int			min_int;
	int			i;

	minheap = minheap_int_create(init_size);

	for (i = 100; i > 0; i -= 5) {
		minheap_int_insert(minheap, i);
	}

	minheap_int_print(minheap);

	while (! minheap_int_is_empty(minheap)) {
		min_int = minheap_int_extract_min(minheap);
		printf("Extracted %d\n", min_int);
		printf("-------------------\n");
		minheap_int_print(minheap);
		printf("===================\n");
	}

	minheap_int_destroy(minheap);

} /* end test2 */

/******************************************************************************
 * Driver for testing MinHeapInt API
 *****************************************************************************/
int
main(
	int		argc,
	char	*argv[]
)
{
	test1();
	test2();

	exit(0);

} /* end main */
