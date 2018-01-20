/*****************************************************************************
 * Wraps a linked list of integers for use in C
 ****************************************************************************/

#include <stdbool.h>
#include <stdlib.h>

typedef struct NodeInt {
	struct NodeInt	*next;
	int				data;
} NodeInt;

typedef struct LinkedListInt {
	NodeInt	*head;
	NodeInt	*tail; /* For ease of adding to the end */
	unsigned int	count;
} LListInt;

extern LListInt *
llist_int_create();

extern void
llist_int_destroy(
	LListInt	*llist_int
);

extern bool
llist_int_add_first(
	LListInt	*llist_int,
	int		data
);

extern bool
llist_int_add_last(
	LListInt	*llist_int,
	int		data
);

extern int
llist_int_remove_first(
	LListInt	*llist_int
);

extern int
llist_int_remove_last(
	LListInt	*llist_int
);

extern bool
llist_int_is_empty(
	LListInt	*llist_int
);

extern void
llist_int_print(
	LListInt	*llist_int
);
