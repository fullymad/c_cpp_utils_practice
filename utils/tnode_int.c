#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "common_utils.h"
#include "tnode_int.h"

/*****************************************************************************
 * Creates a new node for the given data and inserts into the tree in the
 * sorted position.
 *
 * Input:
 *   tnode_int - Tree node (normally the root)
 *   int - Data to insert
 *
 * Returns:
 *   Pointer to the new node (could be root if starting with empty tree) and
 *     NULL on error
 *   Caller should free returned node
 ****************************************************************************/
TNodeInt *
tnode_int_insert(
	TNodeInt	*tnode_int,
	int			data
)
{
	TNodeInt	*new_tnode;

	new_tnode = (TNodeInt *)malloc(sizeof(TNodeInt));

	if (new_tnode == NULL) {
		printf("ERROR: Failed to allocated memory for TNodeInt\n");
	}
	else {
		new_tnode->data = data;
		new_tnode->left = NULL;
		new_tnode->right = NULL;
	}

	/* Insert into the sorted position in the given tree */
	while (tnode_int != NULL) {
		if (data <= tnode_int->data) {
			if (tnode_int->left == NULL) {
				tnode_int->left = new_tnode;
				break;
			}
			else {
				tnode_int = tnode_int->left;
			}
		}
		else {
			if (tnode_int->right == NULL) {
				tnode_int->right = new_tnode;
				break;
			}
			else {
				tnode_int = tnode_int->right;
			}
		}
	}

	return new_tnode;
	
} /* end tnode_int_insert */

/*****************************************************************************
 * Deletes the tree node matching the given data. Frees the node too.
 *
 * Input:
 *   tnode_int - Tree node (normally the root). If NULL, returns 'not found'.
 *   data - Value of node to be deleted
 *
 * Output:
 *   root_tnode - Returns new root node if given root is deleted, otherwise
 *     the input node
 *
 * Returns:
 *   True if node found and deleted, else False
 ****************************************************************************/
bool
tnode_int_delete(
	TNodeInt	*tnode_int,
	int			data,
	TNodeInt	**root_tnode
)
{
	bool		found = false;
	TNodeInt	*found_tnode = NULL;
	TNodeInt	*left = NULL; /* Found tnode's left child */
	TNodeInt	*right = NULL; /* Found tnode's right child */
	TNodeInt	*parent = NULL; /* Found tnode's parent */
	TNodeInt	*promoted_child = NULL;
	TNodeInt	*right_most_tip = NULL;

	/* By default, return input node as the root of the modified tree */
	*root_tnode = tnode_int;

	if (tnode_int == NULL) {
		return found;
	}

	found_tnode = tnode_int_find_with_parent(tnode_int, data, &parent);

	/* Promote the left child up to take the place of the node to be deleted
	 * and then move the right child to the bottom of the right tree of the
	 * promoted child. If only right child present, promote it up instead.
	 */
	if (found_tnode != NULL) {
		found = true;

		left = found_tnode->left;
		right = found_tnode->right;

		if (left != NULL) {
			/* Move right child to bottom of the right of promoted child */
			if (right != NULL) {
				right_most_tip = left;
				while (right_most_tip->right != NULL) {
					right_most_tip = right_most_tip->right;
				}
				right_most_tip->right = right;
			}
			promoted_child = left;
		}
		else {
			promoted_child = right;
		}

		/* Promote appropriate child one level up. If this child becomes the
		 * root, set it to be the new root */
		if (parent != NULL) {
			if (parent->left == found_tnode) {
				parent->left = promoted_child;
			}
			else {
				parent->right = promoted_child;
			}
		}
		else { /* Promoted child becomes the root */
			*root_tnode = promoted_child;
		}

		free(found_tnode);
	}

	return found;

} /* end tnode_int_delete */

/*****************************************************************************
 * Returns the node matching the given data
 *
 * Input:
 *   tnode_int - Tree node (normally the root)
 *   data - Value to look for
 *   parent - Parent of the input node, NULL on pre-recursive call
 *
 * Returns:
 *   Matching tree node pointer, NULL if not found
 *   MODIFIES parent recursing down the tree
 ****************************************************************************/
TNodeInt *
tnode_int_find_with_parent(
	TNodeInt	*tnode_int,
	int			data,
	TNodeInt	**parent
)
{
	TNodeInt	*ret_tnode = NULL;

	if (tnode_int != NULL) {
		if (tnode_int->data == data) {
			ret_tnode = tnode_int;
		}
		else if (tnode_int->data > data && tnode_int->left != NULL) {
			*parent = tnode_int;
			ret_tnode = tnode_int_find_with_parent(tnode_int->left,
						data, parent);
		}
		else if (tnode_int->data < data && tnode_int->right != NULL) {
			*parent = tnode_int;
			ret_tnode = tnode_int_find_with_parent(tnode_int->right,
						data, parent);
		}
	}

	return ret_tnode;

} /* end tnode_int_find_with_parent */

/*****************************************************************************
 * Returns the node matching the given data
 *
 * Input:
 *   tnode_int - Tree node (normally the root)
 *   data - Value to look for
 *
 * Returns:
 *   Matching tree node pointer, NULL if not found
 ****************************************************************************/
TNodeInt *
tnode_int_find(
	TNodeInt	*tnode_int,
	int			data
)
{
	TNodeInt	*parent = NULL;

	return tnode_int_find_with_parent(tnode_int, data, &parent);

} /* end tnode_int_find */

/*****************************************************************************
 * Gets the height of the tree (the height of a single node tree being 0)
 *
 * Input:
 *   tnode_int - Tree node
 *
 * Returns:
 *   Length of path from given node to the deepest node in the tree
 ****************************************************************************/
int
tnode_int_height(
	TNodeInt	*tnode_int
)
{
	int	sub_tree_height = -1;
	TNodeInt	*left;
	TNodeInt	*right;
	int left_height = 0;
	int right_height = 0;

	if (tnode_int != NULL) {
		left = tnode_int->left;
		right = tnode_int->right;

		if (left == NULL && right == NULL) {
			sub_tree_height = -1;
		}
		else {
			left_height = tnode_int_height(tnode_int->left);
			right_height = tnode_int_height(tnode_int->right);

			sub_tree_height = MAX(left_height, right_height);
		}
	}

	return sub_tree_height + 1;

} /* end tnode_int_height */

/*****************************************************************************
 * Prints the elements of the tree in the given traversal order
 *
 * Input:
 *   tnode_int - Tree node (normally the root)
 *   traversal_order - Enum for in-order, pre-order or post-order
 ****************************************************************************/
void
tnode_int_print(
	TNodeInt	*tnode_int,
	TraversalOrder	traversal_order
)
{
	if (tnode_int == NULL) {
		printf("Empty tree\n");
	}
	else if (traversal_order == TRAVERSAL_IN_ORDER) {
		if (tnode_int->left != NULL) {
			tnode_int_print(tnode_int->left, traversal_order);
		}
		printf("%d\n", tnode_int->data);
		if (tnode_int->right != NULL) {
			tnode_int_print(tnode_int->right, traversal_order);
		}
	}
	else {
		printf("tnode_int_print: Traversal order %d not supported\n",
			traversal_order);
	}

	return;

} /* end tnode_int_print */

/*****************************************************************************
 * Frees all the nodes of the integer tree including the given root node 
 *
 * Input:
 *   tnode_int - Tree node (normally the root)
 ****************************************************************************/
void
tnode_int_destroy(
	TNodeInt	*tnode_int
)
{
	assert(tnode_int != NULL);

	if (tnode_int->left != NULL) {
		tnode_int_destroy(tnode_int->left);
	}

	if (tnode_int->right != NULL) {
		tnode_int_destroy(tnode_int->right);
	}

	free(tnode_int);

	return;

} /* end tnode_int_destroy */
