#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "common_utils.h"

/* Information on each bucket in radix sort */
typedef struct BucketInfo {
	unsigned int	count; /* Number of elements for this digit value */
	unsigned int	offset; /* Offset in array for elements for this digit */
	unsigned int	next_offset; /* Next offset for adding element to bucket */
} BucketInfo;

/*****************************************************************************
 * Swaps given 2 integers with each other
 *
 * Input:
 *  first - Pointer to the first integer
 *  second - Pointer to the second integer
 *
 ****************************************************************************/
void
swap_ints(
	int		*first,
	int		*second
)
{
	int		temp;

	assert(first != NULL && second != NULL);

	temp = *first;
	*first = *second;
	*second = temp;

	return;

} /* end swap_ints */

/*****************************************************************************
 * Prints the contents of the given bucket info structure
 *
 * Input:
 *  bucket_info - Pointer to bucket info structure
 *  count - Number of buckets
 ****************************************************************************/
/*
static void
print_bucket_info(
	BucketInfo	*bucket_info,
	unsigned int	count
)
{
	unsigned int	i;

	assert(bucket_info != NULL);

	for (i = 0; i < count; i++) {
		printf("Bucket %u, count %u, offset %u, next_offset %u\n",
			i, bucket_info[i].count, bucket_info[i].offset,
			bucket_info[i].next_offset);
	}

	return;

} end print_bucket_info */

/*****************************************************************************
 * Reads in an array of integers from given input file. First line of file gives
 * the number of integers following it. If found more integers in file, ignores
 * the rest. If found less, throws an error and returns NULL.
 *
 * Input:
 *   file_name - Input file containing integers
 *
 * Returns:
 *   IntArray with memory allocated for structure and data inside, NULL on
 *   error
 *   Caller needs to invoke free_int_array when done with it
 ****************************************************************************/
IntArray *
create_int_array_from_file(
	const char	*file_name
)
{
	FILE		*fd;
	IntArray	*int_array = NULL;
	unsigned int	count = 0;
	int			value;
	int			i;

	assert(file_name != NULL);
	assert(file_name[0] != '\0');

	fd = fopen(file_name, "r");

	if (fd == NULL) {
		printf("Error opening file %s\n", file_name);
	}
	else {
		int_array = (IntArray *)malloc(sizeof(IntArray));
		assert(int_array != NULL);

		int_array->count = 0;
		int_array->data = NULL;

		if (fscanf(fd, "%u", &count) == 0 || count <= 0) {
			printf("Error getting count from file OR count <= 0\n");
			free_int_array(int_array);
			int_array = NULL;
		}
		else {
			int_array->count = count;
			int_array->data = (int *)malloc(sizeof(int *) * count);
			for (i = 0; i < count; i++) {
				if (fscanf(fd, "%d", &value) == EOF) {
					printf("Insufficient integers, expected = %u, "
						"actual = %d\n", count, i);
					free_int_array(int_array);
					int_array = NULL;

					break;
				}
				else {
					int_array->data[i] = value;
				}
			}
		}

		fclose(fd);
	}

	return(int_array);

} /* end create_int_array_from_file */

/*****************************************************************************
 * Prints the data in the given IntArray, with one integer to a line
 *
 * Input:
 *   heading - Description of what the array is
 *     (Optional - can be NULL or a blank string)
 *   int_arry - IntArray to print
 ****************************************************************************/
void
print_IntArray(
	const char		*heading,
	const IntArray	*int_array
)
{
	int i;
	unsigned int count = 0;

	if (heading != NULL && heading[0] != '\0') {
		printf("%s\n", heading);
	}

	if (int_array == NULL) {
		printf("IntArray is NULL\n");
	}
	else {
		printf("IntArray has %u elements as below\n", int_array->count);

		if (int_array->data != NULL) {
			count = int_array->count;
			for (i = 0; i < count; i++) {
				printf("%d\n", int_array->data[i]);
			}
		}
	}

	return;

} /* end print_IntArray */

/******************************************************************************
 * Releases the memory occupied by the given IntArray
 *****************************************************************************/
void
free_int_array(
	IntArray	*int_array
)
{
	if (int_array == NULL) {
		printf("WARNING: IntArray to free is NULL\n");
	}
	else {
		if (int_array->data != NULL) {
			free(int_array->data);
		}
		free(int_array);
	}

	return;

} /* end free_int_array */

/******************************************************************************
 * Merges the 2 contiguous ranges of individually sorted elements into an
 * overall sorted order.
 *
 * Input:
 *   in_data - Input array bounded by the given ranges
 *   low_i - Start of the first range
 *   mid_i - End of the first range
 *   high_i - End of the second range (mid_i + 1, being the start)
 *   temp_data - Used as temporary buffer to copy from in_data before merging
 *    back into in_data
 *
 * Modifies the elements in range low_i to high_i of input array.
 *****************************************************************************/
static void
merge_sort_merge(
	int		*in_data,
	int		low_i,
	int		mid_i,
	int		high_i,
	int		*temp_data
)
{
	int		i;
	int		left_i;
	int		right_i;

	assert(in_data != NULL && temp_data != NULL);

	if (low_i >= high_i) {
		return;
	}

	/* Copy the input values into the temporary area */
	for (i = low_i; i <= high_i; i++) {
		temp_data[i] = in_data[i];
	}

	/* Copy back from temporary area to main in the sorted order */
	left_i = low_i;
	right_i = mid_i + 1;
	i = low_i;

	while (left_i <= mid_i && right_i <= high_i) {
		if (temp_data[left_i] <= temp_data[right_i]) {
			in_data[i] = temp_data[left_i];
			left_i++;
		}
		else {
			in_data[i] = temp_data[right_i];
			right_i++;
		}
		i++;
	}

	/* Copy any left-over from the left range */
	while (left_i <= mid_i) {
		in_data[i] = temp_data[left_i];
		left_i++;
		i++;
	}

	return;

} /* end merge_sort_merge */

/******************************************************************************
 * Sorts the 2 halves of the given range and merges the results into a sorted
 * order
 *
 * Input:
 *   in_data - Input array of integers
 *   low_i - Lower boundary (as index into in_data)
 *   high_i - Higher boundary (as index into in_data)
 *   temp_data - Used as temporary buffer to copy from in_data before merging
 *    back into in_data
 *****************************************************************************/
static void
merge_sort_range(
	int		*in_data,
	int		low_i,
	int		high_i,
	int		*temp_data
)
{
	int			mid_i;

	assert(in_data != NULL && temp_data != NULL);

	if (low_i >= high_i) {
		return;
	}

	mid_i = (low_i + high_i) / 2;
	merge_sort_range(in_data, low_i, mid_i, temp_data);
	merge_sort_range(in_data, mid_i + 1, high_i, temp_data);
	merge_sort_merge(in_data, low_i, mid_i, high_i, temp_data);

	return;

} /* end merge_sort_range */

/******************************************************************************
 * Use merge sort to sort an array of integers
 *
 * Input:
 *   in_data - Input array of integers (modified after sorting)
 *****************************************************************************/
void
merge_sort(
	IntArray	*in_data
)
{
	unsigned int count;
	int	*temp_data = NULL;

	assert(in_data != NULL && in_data->data != NULL);

	count = in_data->count;
	if (count > 1) {
		temp_data = (int *)malloc(sizeof(int *) * count);
		assert(temp_data != NULL);

		merge_sort_range(in_data->data, 0, count - 1, temp_data);
		free(temp_data);
	}

	return;

} /* end merge_sort */

/******************************************************************************
 * Partitions the given range of elements around a pivot value and returns the
 * index of the pivot value. Uses the middle element for pivot.
 *
 * Modifies the elements in range low_i to high_i of input array.
 *
 * Input:
 *   in_data - Input array bounded by the given ranges
 *   low_i - Start of the range
 *   high_i - End of the range
 *
 * Returns:
 *   Index of the pivot value around which partitioned
 *****************************************************************************/
static unsigned int
quick_sort_partition(
	int		*in_data,
	int		low_i,
	int		high_i
)
{
	int		mid_i;
	int		pivot;
	int		left_i;
	int		right_i;

	assert(in_data != NULL);

	/* Choose the pivot value from the middle element */
	mid_i = (low_i + high_i) / 2;
	pivot = in_data[mid_i];

	left_i = low_i;
	right_i = high_i;

	while (left_i <= right_i) {
		while (in_data[left_i] < pivot) {
			left_i++;
		}

		while (in_data[right_i] > pivot) {
			right_i--;
		}

		if (left_i <= right_i) {
			/* Swap elements */
			swap_ints(in_data + left_i, in_data + right_i);
			left_i++;
			right_i--;
		}
	}

	return left_i;

} /* end quick_sort_partition */

/******************************************************************************
 * Partitions the 2 halves of the given range and returns the index of the
 * 'middle' element.
 *
 * Input:
 *   in_data - Input array of integers
 *   low_i - Lower boundary (as index into in_data)
 *   high_i - Higher boundary (as index into in_data)
 *****************************************************************************/
static void
quick_sort_range(
	int		*in_data,
	int		low_i,
	int		high_i
)
{
	int			mid_i;

	assert(in_data != NULL);

	if (low_i >= high_i) {
		return;
	}

	mid_i = quick_sort_partition(in_data, low_i, high_i);

	if (low_i < mid_i - 1) {
		quick_sort_range(in_data, low_i, mid_i - 1);
	}
	if (mid_i < high_i) {
		quick_sort_range(in_data, mid_i, high_i);
	}

	return;

} /* end quick_sort_range */

/******************************************************************************
 * Use quick sort to sort an array of integers
 *
 * Input:
 *   in_data - Input array of integers (modified after sorting)
 *****************************************************************************/
void
quick_sort(
	IntArray	*in_data
)
{
	unsigned int count;

	assert(in_data != NULL && in_data->data != NULL);

	count = in_data->count;
	if (count > 1) {
		quick_sort_range(in_data->data, 0, count - 1);
	}

	return;

} /* end quick_sort */

/******************************************************************************
 * Sorts given data into buckets for digits 0 - 9 based on given position of
 * digit. Sorted data will be in temp_data.
 *
 * Input:
 *   in_data - Input array of integers
 *   low_i - Lower boundary (as index into in_data)
 *   high_i - Higher boundary (as index into in_data)
 *   temp_data - Used as temporary buffer to copy from in_data into buckets
 *   digit_pos - Position of digit that is the basis for grouping into buckets.
 *    One's position is 1, 10's is 2 and so on.
 *
 * Output:
 *   temp_data - Locations low_i to high_i modified with sorted buckets
 *****************************************************************************/
static void
radix_msd_sort_range(
	int		*in_data,
	int		low_i,
	int		high_i,
	int		*temp_data,
	unsigned int	digit_pos
)
{
	BucketInfo	bucket_info[10];
	int				i;
	int				digit;
	unsigned int	place_value;
	unsigned int	bucket_offset;
	unsigned int	next_offset;
	unsigned int	bucket_start_pos;
	unsigned int	bucket_end_pos;

	assert(in_data != NULL && temp_data != NULL);
	assert(low_i <= high_i);
	assert(digit_pos >= 1);

	if (low_i == high_i) {
		temp_data[low_i] = in_data[low_i];
		return;
	}

	/* Get place value for the digit position */
	place_value = 1;
	for (i = 0; i < digit_pos - 1; i++) {
		place_value *= 10;
	}

	/* Initialize each bucket size to 0 */
	for (i = 0; i < 10; i++) {
		bucket_info[i].count = 0;
	}

	/* Count bucket size for digits 0 - 9 */
	for (i = low_i; i <= high_i; i++) {
		digit = (in_data[i] / place_value) % 10;
		bucket_info[digit].count++;
	}

	/* Determine offset into array where each bucket starts */
	bucket_offset = 0; /* Offset for 1st bucket */
	for (i = 0; i < 10; i++) {
		bucket_info[i].offset = bucket_offset;
		bucket_info[i].next_offset = bucket_offset;
		bucket_offset += bucket_info[i].count; /* Offset for next bucket */
	}

	/* Group the input values into buckets based on given digit position */
	for (i = low_i; i <= high_i; i++) {
		digit = (in_data[i] / place_value) % 10;
		next_offset = bucket_info[digit].next_offset++;
		temp_data[low_i + next_offset] = in_data[i];
	}

	/* For each bucket, group by the next digit position */
	if (digit_pos > 1) { /* Not yet reached least significant digit */
		for (i = 0; i < 10; i++) {
			if (bucket_info[i].count > 0) { /* Non-empty bucket */
				bucket_start_pos = low_i + bucket_info[i].offset;
				bucket_end_pos = bucket_start_pos + bucket_info[i].count - 1;
				radix_msd_sort_range(temp_data, bucket_start_pos,
					bucket_end_pos, in_data, digit_pos - 1);
			}
		}
	}

	return;

} /* end radix_msd_sort_range */

/******************************************************************************
 * Use MSD radix sort to sort an array of integers
 *
 * ASSUMES non-negative integers in input
 *
 * Input:
 *   in_data - Input array of integers (modified after sorting)
 *****************************************************************************/
void
radix_msd_sort(
	IntArray	*in_data
)
{
	int			i;
	unsigned int count;
	int			max_vaue;
	unsigned int max_digits;
	int			*temp_data;

	assert(in_data != NULL && in_data->data != NULL);

	count = in_data->count;

	if (count <= 1){
		return;
	}

	/* Get the largest number in the input */
	for (i = 0; i < count; i++) {
		if (i == 0) {
			max_vaue = in_data->data[i];
		}
		else {
			if (in_data->data[i] > max_vaue) {
				max_vaue = in_data->data[i];
			}
		}
	}

	/* Get the maximum number of digits in any of the input integers */
	max_digits = 1;
	while ((max_vaue /= 10) != 0) {
		max_digits++;
	}

	temp_data = (int *)malloc(sizeof(int *) * count);
	assert(temp_data != NULL);

	radix_msd_sort_range(in_data->data, 0, count - 1, temp_data, max_digits);

	/* If odd number of iterations, copy final sorted data from temp_data */
	if (max_digits % 2 == 1) {
		for (i = 0; i < count; i++) {
			in_data->data[i] = temp_data[i];
		}
	}

	free(temp_data);

	return;

} /* end radix_msd_sort */
