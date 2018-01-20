#include <stdio.h>
#include <assert.h>

#include "llist_int.h"

/*****************************************************************************
 * Creates an empty linked list of integers.
 *
 * NOTE: This API must be called first to create the linked list and should be
 * used for all further operations (at the end of which the destroy API should
 * be called).
 *
 * Returns:
 *   Pointer to newly allocated LListInt structure, NULL on error
 ****************************************************************************/
LListInt *
llist_int_create()
{
	LListInt	*ret_llist = NULL;

	ret_llist = (LListInt *)malloc(sizeof(LListInt));

	if (ret_llist == NULL) {
		printf("ERROR: Failed to allocate memory for LListInt\n");
	}
	else {
		ret_llist->head = NULL;
		ret_llist->tail = NULL;
		ret_llist->count = 0;
	}

	return ret_llist;

} /* end llist_int_create */

/*****************************************************************************
 * Frees the linked list and the wrapper LListInt structure.
 ****************************************************************************/
void
llist_int_destroy(
	LListInt	*llist_int
)
{
	NodeInt		*next_node = NULL;
	NodeInt		*temp_node = NULL;

	assert(llist_int != NULL);

	next_node = llist_int->head;

	while (next_node != NULL) {
		temp_node = next_node->next; /* Save next node */
		free(next_node); /* Free current node */

		next_node = temp_node;
	}

	free(llist_int);

	return;

} /* end llist_int_destroy */

/*****************************************************************************
 * Adds the given integer to the start of the linked list
 *
 * Returns:
 *   true if successful, else false
 ****************************************************************************/
bool
llist_int_add_first(
	LListInt	*llist_int,
	int			data
)
{
	bool		result = true;
	NodeInt		*head_node = NULL;
	NodeInt		*new_node = NULL;

	assert(llist_int != NULL);

	head_node = llist_int->head;

	new_node = (NodeInt *)malloc(sizeof(NodeInt));

	if (new_node != NULL) {
		new_node->next = head_node;
		new_node->data = data;

		llist_int->head = new_node;

		/* If adding first ever node, make it the 'tail' too */
		if (llist_int->tail == NULL) {
			llist_int->tail = new_node;
		}

		llist_int->count++;
	}
	else {
		printf("ERROR: Failed to allocate in llist_int_add_first\n");
		result = false;
	}

	return result;

} /* end llist_int_add_first */

/*****************************************************************************
 * Adds the given integer to the end of the linked list
 *
 * Returns:
 *   true if successful, else false
 ****************************************************************************/
bool
llist_int_add_last(
	LListInt	*llist_int,
	int			data
)
{
	bool		result = true;
	NodeInt		*tail_node = NULL;
	NodeInt		*new_node = NULL;

	assert(llist_int != NULL);

	tail_node = llist_int->tail;

	new_node = (NodeInt *)malloc(sizeof(NodeInt));

	if (new_node != NULL) {
		new_node->next = NULL;
		new_node->data = data;

		if (tail_node != NULL) {
			tail_node->next = new_node;
		}

		llist_int->tail = new_node;

		/* If adding first ever node, make it the 'head' too */
		if (llist_int->head == NULL) {
			llist_int->head = new_node;
		}

		llist_int->count++;
	}
	else {
		printf("ERROR: Failed to allocate in llist_int_add_last\n");
		result = false;
	}

	return result;

} /* end llist_int_add_last */

/*****************************************************************************
 * Removes the first node in the linked list and returns its integer value.
 * It is an error to call this when the list is empty.
 *
 * Returns:
 *   Integer data in the removed node
 ****************************************************************************/
int
llist_int_remove_first(
	LListInt	*llist_int
)
{
	int			ret_value;
	NodeInt		*removed_node = NULL;

	assert(llist_int != NULL && llist_int->head != NULL);

	removed_node = llist_int->head;
	llist_int->head = removed_node->next;
	llist_int->count--;

	/* If removing the only node, set tail to NULL too */
	if (llist_int->tail == removed_node) {
		llist_int->tail = NULL;
	}

	ret_value = removed_node->data;
	free(removed_node);

	return ret_value;

} /* end llist_int_remove_first */

/*****************************************************************************
 * Removes the last node in the linked list and returns its integer value.
 * It is an error to call this when the list is empty.
 *
 * Returns:
 *   Integer data in the removed node
 ****************************************************************************/
int
llist_int_remove_last(
	LListInt	*llist_int
)
{
	int			ret_value;
	NodeInt		*this_node = NULL;
	NodeInt		*removed_node = NULL;

	assert(llist_int != NULL && llist_int->tail != NULL);

	this_node = llist_int->head;

	/* Get the node that is before the tail node, considering that the tail
	 * could be the only node.
	 */
	while (this_node != llist_int->tail &&
			this_node->next != llist_int->tail) {
		this_node = this_node->next;
	}

	removed_node = llist_int->tail;

	if (this_node == llist_int->tail) { /* Removing the only node */
		llist_int->tail = NULL;
	}
	else {
		llist_int->tail = this_node; /* Set tail to the previous node */
		this_node->next = NULL;
	}
	llist_int->count--;

	/* If removing the only node, set head to NULL too */
	if (llist_int->head == removed_node) {
		llist_int->head = NULL;
	}

	ret_value = removed_node->data;
	free(removed_node);

	return ret_value;

} /* end llist_int_remove_last */

/*****************************************************************************
 * Tells if the linked list is empty.
 *
 * Returns:
 *   true if the linked list is empty (zero elements), else false.
 ****************************************************************************/
bool
llist_int_is_empty(
	LListInt	*llist_int
)
{
	bool	result;

	assert(llist_int != NULL);

	if (llist_int->count == 0) {
		result = true;
	}
	else {
		result = false;
	}

	return result;

} /* end llist_int_is_empty */

/*****************************************************************************
 * Prints the list of integers in the linked list with some header information
 * about the list (like first element, count, etc.).
 ****************************************************************************/
void
llist_int_print(
	LListInt	*llist_int
)
{
	NodeInt	*this_node;

	assert(llist_int != NULL);

	printf("Integer linked list contains %d elements\n", llist_int->count);

	/* Try to print head and tail even if count is 0 - just for sanity check */

	if (llist_int->head != NULL) {
		printf("  First integer: %d\n", llist_int->head->data);
	}

	if (llist_int->tail != NULL) {
		printf("  Last integer: %d\n", llist_int->tail->data);
	}

	if (! llist_int_is_empty(llist_int)) {
		printf("  List of all integers in the linked list\n");

		this_node = llist_int->head;

		while (this_node != NULL) {
			printf("    %d\n", this_node->data);
			this_node = this_node->next;
		}
	}

	return;

} /* end llist_int_print */
