
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct IntArray {
	unsigned int	count;
	int				*data;
} IntArray;

extern IntArray *
create_int_array_from_file(
	const char	*file_name
);

extern void
print_IntArray(
	const char		*heading,
	const IntArray	*int_array
);

extern void
free_int_array(
	IntArray	*int_array
);

extern void
merge_sort(
	IntArray 	*in_data
);

extern void
quick_sort(
	IntArray 	*in_data
);

extern void
radix_msd_sort(
	IntArray 	*in_data
);
