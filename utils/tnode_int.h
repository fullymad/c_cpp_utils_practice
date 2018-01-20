/*****************************************************************************
 * Defines a tree node for integer for use in C
 ****************************************************************************/

#include <stdbool.h>
#include <stdlib.h>

typedef enum TraversalOrder {
	TRAVERSAL_IN_ORDER,
	TRAVERSAL_PRE_ORDER,
	TRAVERSAL_POST_ORDER
} TraversalOrder;

typedef struct TreeNodeInt {
	int					data;
	struct TreeNodeInt	*left;
	struct TreeNodeInt	*right;
} TNodeInt;

extern TNodeInt *
tnode_int_insert(
	TNodeInt	*tnode_int,
	int			data
);

extern bool
tnode_int_delete(
	TNodeInt	*tnode_int,
	int			data,
	TNodeInt	**root_tnode
);

extern TNodeInt *
tnode_int_find_with_parent(
	TNodeInt	*tnode_int,
	int			data,
	TNodeInt	**parent
);

extern TNodeInt *
tnode_int_find(
	TNodeInt	*tnode_int,
	int			data
);

extern int
tnode_int_height(
	TNodeInt	*tnode_int
);

extern void
tnode_int_print(
	TNodeInt	*tnode_int,
	TraversalOrder	traversal_order
);

extern void
tnode_int_destroy(
	TNodeInt	*tnode_int
);
