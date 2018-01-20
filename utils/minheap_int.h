/*****************************************************************************
 * Wraps a minimum heap of integers for use in C
 ****************************************************************************/

#include <stdbool.h>
#include <stdlib.h>

typedef struct MinHeapInt {
	/* For now, negative numbers allowed */
	int				*heap_nodes; /* Pointer to first (root) node */
	unsigned int	total_size;
	unsigned int	used_size;
} MinHeapInt;

extern MinHeapInt *
minheap_int_create(
	unsigned int		init_size
);

extern void
minheap_int_destroy(
	MinHeapInt	*minheap_int
);

extern bool
minheap_int_insert(
	MinHeapInt	*minheap_int,
	int			data
);

extern int
minheap_int_extract_min(
	MinHeapInt	*minheap_int
);

extern bool
minheap_int_is_empty(
	MinHeapInt	*minheap_int
);

extern void
minheap_int_print(
	MinHeapInt	*minheap_int
);
