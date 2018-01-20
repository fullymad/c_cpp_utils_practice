#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "common_utils.h"

#define SORT_ALGO_MERGE 1
#define SORT_ALGO_QUICK 2
#define SORT_ALGO_RADIX_MSD 3

/******************************************************************************
 * Use given sort algorithm to sort an array of integers
 * Input:
 *   argv[1] - Name of file containing the integers one to a line with a header
 *     line that tells the number of integers that follow
 *
 *   argv[2] - Sorting algorithm to use. Valid values are 'merge', 'quick' and
 *     'radix_msd'
 *****************************************************************************/

int
main(
	int		argc,
	char	*argv[]
)
{
	IntArray		*in_data;
	unsigned int	sort_algo = 0;
	int				result = 0;

	assert(argc == 3 && argv[1] != NULL && argv[2] != NULL);

	if (strcmp(argv[2], "merge") == 0) {
		sort_algo = SORT_ALGO_MERGE;
	}
	else if (strcmp(argv[2], "quick") == 0) {
		sort_algo = SORT_ALGO_QUICK;
	}
	else if (strcmp(argv[2], "radix_msd") == 0) {
		sort_algo = SORT_ALGO_RADIX_MSD;
	}
	else {
		printf("Unsupported sort algorithm '%s'\n", argv[2]);
		result = 1;
	}

	if (sort_algo != 0) {
		in_data = create_int_array_from_file(argv[1]);

		if (in_data != NULL) {

			print_IntArray("Input integer array", in_data);

			switch (sort_algo) {
			case SORT_ALGO_MERGE:
				merge_sort(in_data);
				break;
			case SORT_ALGO_QUICK:
				quick_sort(in_data);
				break;
			case SORT_ALGO_RADIX_MSD:
				radix_msd_sort(in_data);
				break;
			default:
				break;
			}

			print_IntArray("Sorted integer array", in_data);

			free_int_array(in_data);
		}
	}

	return result;

} /* end main */
