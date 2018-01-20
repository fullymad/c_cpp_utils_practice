#include <stdio.h>

#include "llist_int.h"

/******************************************************************************
 * Driver for testing LinkedListInt API
 *****************************************************************************/
int
main(
	int		argc,
	char	*argv[]
)
{
	LListInt	*llist1 = NULL;
	int			element = 0;

	llist1 = llist_int_create();

	/* Testing printing empty list */
	llist_int_print(llist1);

	llist_int_add_first(llist1, 27);
	llist_int_print(llist1);

	element = llist_int_remove_last(llist1);
	printf("Removed last element is %d\n", element);

	llist_int_print(llist1);

	llist_int_add_last(llist1, 72);
	llist_int_add_last(llist1, 77);
	llist_int_add_first(llist1, 62);

	llist_int_print(llist1);

	llist_int_remove_first(llist1);
	llist_int_remove_first(llist1);
	llist_int_remove_first(llist1);

	llist_int_add_last(llist1, 128);
	llist_int_add_last(llist1, 200);
	llist_int_add_last(llist1, 777);

	llist_int_add_first(llist1, 1000);
	llist_int_add_last(llist1, -2144);

	llist_int_print(llist1);

	llist_int_remove_first(llist1);
	llist_int_print(llist1);

	llist_int_remove_last(llist1);
	llist_int_print(llist1);

	llist_int_remove_first(llist1);
	llist_int_print(llist1);

	llist_int_remove_last(llist1);

	llist_int_print(llist1);

	llist_int_destroy(llist1);

	exit(0);

} /* end main */
