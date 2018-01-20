#include <stdio.h>
#include <assert.h>

#include "minheap_int.h"

/*****************************************************************************
 * Creates an empty min heap with given initial size reserved for nodes
 *
 * NOTE: This API must be called first to create the min heap and should be
 * used for all further operations (at the end of which the destroy API should
 * be called).
 *
 * Input:
 *   init_size - Number of integers for which initial allocation done
 *               For now, it allows size that is NOT a power of 2.
 *
 * Returns:
 *   Pointer to newly allocated MinHeapInt structure, NULL on error
 ****************************************************************************/
MinHeapInt *
minheap_int_create(
	unsigned int	init_size
)
{
	MinHeapInt	*ret_minheap = NULL;

	assert(init_size > 0);

	ret_minheap = (MinHeapInt *)malloc(sizeof(MinHeapInt));

	if (ret_minheap == NULL) {
		printf("ERROR: Failed to allocate memory for MinHeapInt\n");
	}
	else {
		ret_minheap->heap_nodes = (int *)malloc(sizeof(int) * init_size);

		if (ret_minheap->heap_nodes == NULL) {
			printf("ERROR: Failed to allocate memory for MinHeapInt nodes\n");
			init_size = 0; /* Consistent with NULL */
		}

		ret_minheap->total_size = init_size;
		ret_minheap->used_size = 0;
	}

	return ret_minheap;

} /* end minheap_int_create */

/*****************************************************************************
 * Frees the heap nodes and the wrapper MinHeapInt structure.
 ****************************************************************************/
void
minheap_int_destroy(
	MinHeapInt	*minheap_int
)
{
	assert(minheap_int != NULL);

	if (minheap_int->heap_nodes != NULL) {
		free(minheap_int->heap_nodes);
	}

	free(minheap_int);

	return;

} /* end minheap_int_destroy */

/*****************************************************************************
 * Removes and returns the minimum integer in the min heap. Adjusts the
 * remaining nodes so that the min heap property is maintained.
 * It is an error to call this on an empty heap.
 *
 * NOTE: As elements are extracted, the data store shrinks in size. For now,
 * there will be no attempt to release excess free space.
 *
 * Returns:
 *   Minimum integer in the min heap
 ****************************************************************************/
int
minheap_int_extract_min(
	MinHeapInt	*minheap_int
)
{
	int				min_int;
	int				moved_int;
	int				temp_int;
	int				*heap_nodes;
	bool			done = false;
	unsigned int	count;
	unsigned int	current_index;
	unsigned int	swap_index;
	unsigned int	left_child_index;
	unsigned int	right_child_index;

	assert((minheap_int != NULL) && (minheap_int->used_size != 0));

	heap_nodes = minheap_int->heap_nodes;

	/* Get value from the root node in the heap */
	min_int = heap_nodes[0];

	/* Move value from right-most node at bottom to repalce the root one */
	/* Do this only if the heap will NOT become empty after extraction */
	if (minheap_int->used_size > 1) {
		heap_nodes[0] = heap_nodes[minheap_int->used_size - 1];
	}

	minheap_int->used_size--; /* New size after extraction */
	count = minheap_int->used_size;

	/* Move value in root node down as necessary to keep it a min heap */
	if (count != 0) {
		moved_int = heap_nodes[0];
		current_index = 0;
		done = false;
		while (!done) {
			left_child_index = (2 * current_index) + 1;
			right_child_index = (2 * current_index) + 2;

			if ( (left_child_index < count &&
				moved_int > heap_nodes[left_child_index])
				||
				 (right_child_index < count &&
				moved_int > heap_nodes[right_child_index]) ) {

				if (left_child_index >= count) {
					swap_index = right_child_index;
				}
				else if (right_child_index >= count) {
					swap_index = left_child_index;
				}
				else {
					if (heap_nodes[left_child_index]
						< heap_nodes[right_child_index]) {
						swap_index = left_child_index;
					}
					else {
						swap_index = right_child_index;
					}
				}

				/* Found index of child to swap values with, so swap */
				temp_int = heap_nodes[current_index];
				heap_nodes[current_index] = heap_nodes[swap_index];
				heap_nodes[swap_index] = temp_int;

				current_index = swap_index;
			} /* if need to swap */
			else {
				done = true;
			}
		} /* while !done */
	} /* if count != 0 */

	return(min_int);

} /* end minheap_int_extract_min */

/*****************************************************************************
 * Inserts the given integer into the correct position in the min heap.
 *
 * ASSUMPTION: NO duplicates are ever inserted!
 *
 * Returns:
 *   true if successful, else false
 ****************************************************************************/
bool
minheap_int_insert(
	MinHeapInt	*minheap_int,
	int			data
)
{
	bool			result = true;
	bool			done = false;
	unsigned int	insert_index;
	unsigned int	parent_index;
	int				temp_int;
	unsigned int	new_size;
	int				*heap_nodes;

	assert(minheap_int != NULL);

	/* Double the array size if no more space for the new node */
	if (minheap_int->used_size == minheap_int->total_size) {
		new_size = minheap_int->total_size * 2;

		heap_nodes = (int *)realloc(minheap_int->heap_nodes,
						sizeof(int) * new_size);

		if (heap_nodes == NULL) {
			printf("ERROR: Failed to expand memory on insertion\n");
			result = false;
		}
		else {
			minheap_int->heap_nodes = heap_nodes;
			minheap_int->total_size = new_size;
		}
	}
	else {
		heap_nodes = minheap_int->heap_nodes; /* Get pointer to nodes array */
	}

	if (result == true) { /* Everything good so far */

		/* First insert at the left-most space in the bottom of heap */
		insert_index = minheap_int->used_size;
		heap_nodes[insert_index] = data;
		minheap_int->used_size++;

		done = false;
		while (! done) {
			/* Parent node of node 'n' is given by indices as below.
			 * If n is odd, parent is (n - 1)/2. If n is even, it is (n - 2)/2.
			 */

			if (insert_index == 0) { /* Reached root, can't bubble up! */
				done = true;
				break;
			}

			if (insert_index % 2) {
				parent_index = (insert_index - 1)/2;
			}
			else {
				parent_index = (insert_index - 2)/2;
			}

			/* Swap with 'larger' parent and set new insert index */
			if (heap_nodes[parent_index] > heap_nodes[insert_index]) {
				temp_int = heap_nodes[insert_index];
				heap_nodes[insert_index] = heap_nodes[parent_index];
				heap_nodes[parent_index] = temp_int;

				insert_index = parent_index;
			}
			else { /* In right position, so exit bubbling up sequence */
				done = true;
			}
		}
	}

	return result;

} /* end minheap_int_insert */

/*****************************************************************************
 * Tells if the heap is empty.
 *
 * Returns:
 *   true if the heap is empty (zero nodes), else false.
 ****************************************************************************/
bool
minheap_int_is_empty(
	MinHeapInt	*minheap_int
)
{
	bool	result;

	assert(minheap_int != NULL);

	if (minheap_int->used_size == 0) {
		result = true;
	}
	else {
		result = false;
	}

	return result;

} /* end minheap_int_is_empty */

/*****************************************************************************
 * Prints the list of integers in the min heap at each level of the tree.
 ****************************************************************************/
void
minheap_int_print(
	MinHeapInt	*minheap_int
)
{
	unsigned int	level = 0;
	unsigned int	count = 0;
	unsigned int	index = 0;
	unsigned int	depth = 0;
	unsigned int	max_count_at_level = 0;

	assert(minheap_int != NULL);

	printf("Min Heap contains %d node(s)\n", minheap_int->used_size);
	printf("Min Heap has allocation for %d node(s)\n",
			minheap_int->total_size);

	count = minheap_int->used_size;

	if (count != 0) {
		depth = 1;
		while (count >>= 1) { /* count is modified */
			depth++;
		}

		count = minheap_int->used_size; /* Reset count to right value */

		index = 0;
		max_count_at_level = 0;
		for (level = 1; level <= depth; level++) {
			printf("Elements at level %d\n", level);

			if (level == depth) {
				max_count_at_level = count;
			}
			else {
				max_count_at_level += (1 << (level - 1));
			}

			while (index < max_count_at_level) {
				printf("%d  ", minheap_int->heap_nodes[index]);
				index++;
			}
			printf("\n");
		}
	}

	return;

} /* end minheap_int_print */
