#include <stdio.h>

#include "tnode_int.h"

static TNodeInt *
delete_tnode(
	TNodeInt	*tnode_int,
	int			data
)
{
	bool		found = false;
	TNodeInt	*current_root = NULL;
	
	current_root = tnode_int;

	found = tnode_int_delete(tnode_int, data, &current_root);

	if (found) {
		printf("Found and deleted node with data: %d\n", data);

		if (current_root != tnode_int) {
			if (current_root != NULL) {
				printf("New root node: %d\n", current_root->data);
			}
			else {
				printf("New root node: NULL\n");
			}
		}
	}
	else {
		printf("Could not find node with data: %d\n", data);
	}

	return (current_root);

} /* end delete_tnode */

/******************************************************************************
 * Driver for testing TreeNodeInt API
 *****************************************************************************/
int
main(
	int		argc,
	char	*argv[]
)
{
	bool		found = false;
	TNodeInt	*tnode1 = NULL;
	TNodeInt	*found_tnode = NULL;

	tnode_int_print(tnode1, TRAVERSAL_IN_ORDER);

	/* First one, so get back root of tree */
	tnode1 = tnode_int_insert(NULL, 3535);

	printf("Finding 27\n");
	found_tnode = tnode_int_find(tnode1, 27);
	tnode_int_print(found_tnode, TRAVERSAL_IN_ORDER);
	printf("Height of tree: %d\n", tnode_int_height(tnode1));

	/* Testing printing empty tree */
	printf("Integers in tree in-order\n");
	tnode_int_print(tnode1, TRAVERSAL_IN_ORDER);
	printf("Height of tree: %d\n", tnode_int_height(tnode1));

	tnode_int_insert(tnode1, 3);
	tnode_int_insert(tnode1, 33);
	tnode_int_insert(tnode1, 79);
	tnode_int_insert(tnode1, 1);
	tnode_int_insert(tnode1, 27);
	tnode_int_insert(tnode1, 389);
	tnode_int_insert(tnode1, 27);
	tnode_int_insert(tnode1, 30);
	tnode_int_insert(tnode1, 140);

	printf("Integers in tree in-order\n");
	tnode_int_print(tnode1, TRAVERSAL_IN_ORDER);
	printf("Height of tree: %d\n", tnode_int_height(tnode1));

	tnode1 = delete_tnode(tnode1, 32);

	tnode1 = delete_tnode(tnode1, 33);
	tnode_int_print(tnode1, TRAVERSAL_IN_ORDER);
	printf("Height of tree: %d\n", tnode_int_height(tnode1));

	tnode1 = delete_tnode(tnode1, 140);
	tnode_int_print(tnode1, TRAVERSAL_IN_ORDER);
	printf("Height of tree: %d\n", tnode_int_height(tnode1));

	tnode1 = delete_tnode(tnode1, 79);
	tnode_int_print(tnode1, TRAVERSAL_IN_ORDER);
	printf("Height of tree: %d\n", tnode_int_height(tnode1));

	tnode1 = delete_tnode(tnode1, 3535);
	tnode_int_print(tnode1, TRAVERSAL_IN_ORDER);
	printf("Height of tree: %d\n", tnode_int_height(tnode1));

	tnode1 = delete_tnode(tnode1, 30);
	tnode_int_print(tnode1, TRAVERSAL_IN_ORDER);
	printf("Height of tree: %d\n", tnode_int_height(tnode1));

	tnode1 = delete_tnode(tnode1, 27);
	tnode_int_print(tnode1, TRAVERSAL_IN_ORDER);
	printf("Height of tree: %d\n", tnode_int_height(tnode1));

	tnode1 = delete_tnode(tnode1, 1);
	tnode_int_print(tnode1, TRAVERSAL_IN_ORDER);
	printf("Height of tree: %d\n", tnode_int_height(tnode1));

	tnode1 = delete_tnode(tnode1, 389);
	tnode_int_print(tnode1, TRAVERSAL_IN_ORDER);
	printf("Height of tree: %d\n", tnode_int_height(tnode1));

	tnode1 = delete_tnode(tnode1, 27);
	tnode_int_print(tnode1, TRAVERSAL_IN_ORDER);
	printf("Height of tree: %d\n", tnode_int_height(tnode1));

	tnode1 = delete_tnode(tnode1, 3);
	tnode_int_print(tnode1, TRAVERSAL_IN_ORDER);
	printf("Height of tree: %d\n", tnode_int_height(tnode1));
/*
	printf("Finding 27\n");
	found_tnode = tnode_int_find(tnode1, 27);
	tnode_int_print(found_tnode, TRAVERSAL_IN_ORDER);

	printf("Finding 33\n");
	found_tnode = tnode_int_find(tnode1, 33);
	tnode_int_print(found_tnode, TRAVERSAL_IN_ORDER);
*/

	if (tnode1 != NULL) {
		tnode_int_destroy(tnode1);
	}

	exit(0);

} /* end main */
