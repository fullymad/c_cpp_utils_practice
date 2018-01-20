#include <exception>

template <typename K>
size_t hash_code_impl(const K key)
{
	exception e;

	throw e;
}

template <>
size_t hash_code_impl(const string key)
{
	std::hash<std::string> hash_fn;

	return hash_fn(key);
}


template <>
size_t hash_code_impl(const unsigned int key)
{
	return key;
}

template <class K, class V>
HashMap<K, V>::HashMap() :
	HashMap<K, V>::HashMap(HASHMAP_DEFAULT_CAPACITY)
{
}

template <class K, class V>
HashMap<K, V>::HashMap(
	unsigned int	capacity
)
{
	int i;

	_count = 0;
	_capacity = capacity; 

	map_array = new ListNode<std::pair<K, V> > *[_capacity];

	for (i = 0; i < _capacity; i++) {
		map_array[i] = NULL;
	}
}

template <class K, class V>
void HashMap<K, V>::put(
	const K	key,
	const V	value
)
{
	unsigned int hash_key;
	ListNode<pair<K, V> > *new_list_node;
	ListNode<pair<K, V> > *list_node;

	hash_key = hash_code(key) % _capacity;

	list_node = map_array[hash_key];

	/* Search linked list for this key */
	while (list_node != NULL) {
		/* If key found, update value */
		if (list_node->get_data().first == key) {
			list_node->get_data().second = value;
			break;
		}
		else {
			list_node = list_node->get_next();
		}
	}

	/* If key not found, add to head of list and update main array */
	if (list_node == NULL) {
		new_list_node = new ListNode<pair<K, V> >(pair<K, V>(key, value));
		new_list_node->set_next(map_array[hash_key]);
		map_array[hash_key] = new_list_node;
		_count++;
	}

	return;
}

template <class K, class V>
void HashMap<K, V>::remove(
	const K	key
)
{
	unsigned int hash_key;
	ListNode<pair<K, V> > *prev_list_node = NULL;
	ListNode<pair<K, V> > *list_node;

	hash_key = hash_code(key) % _capacity;

	list_node = map_array[hash_key];

	/* Search linked list for this key */
	while (list_node != NULL) {
		if (list_node->get_data().first == key) {
			break;
		}
		else {
			prev_list_node = list_node;
			list_node = list_node->get_next();
		}
	}

	/* If key found, remove it from the list */
	if (list_node != NULL) {
		if (prev_list_node == NULL) {
			/* First element in list for this hash key */
			map_array[hash_key] = list_node->get_next();
		}
		else {
			prev_list_node->set_next(list_node->get_next());
		}

		delete list_node;
		_count--;
	}
	else {
		cout << "Key " << key << " not found, so could not remove" << endl;
	}

	return;
}

template <class K, class V>
unsigned int HashMap<K, V>::hash_code(
	const K	key
)
{
	return hash_code_impl(key);
}

template <class K, class V>
void HashMap<K, V>::print(
	const char *msg_header
)
{
	int i;
	ListNode<pair<K, V> > *list_node;
	ListNode<pair<K, V> > *next_list_node;

	if (msg_header != NULL && msg_header[0] != '\0') {
		cout << msg_header << endl;
	}

	cout << "Count of elements in hash map: " << this->get_count() << endl;

	for (i = 0; i < _capacity; i++) {
		list_node = map_array[i];

		if (list_node != NULL) {
			cout << "Hash index: " << i << endl;
			cout << "Key/Value pair(s): " << endl;

			next_list_node = list_node;
			while (next_list_node != NULL) {
				cout << "\t" << next_list_node->get_data().first << ": "
					<< next_list_node->get_data().second << endl;
				next_list_node = next_list_node->get_next();
			}
		}
	}

	return;

}
