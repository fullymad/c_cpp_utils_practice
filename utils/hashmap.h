#ifndef _HASHMAP_H_
#define _HASHMAP_H_

const unsigned int HASHMAP_DEFAULT_CAPACITY = 64;

template <class K, class V>
class HashMap
{
public:
	HashMap();
	HashMap(unsigned int capacity);
	inline unsigned int get_count() {
		return _count;
	};
	void put(const K key, const V value);
	unsigned int hash_code(const K key);
	void remove(const K key);
	void print(const char* msg_header);

	//std::optional<V>
	//find(<K>);
private:
	unsigned int _count;
	unsigned int _capacity;
	ListNode<std::pair<K, V> > **map_array;
};

template <typename K>
size_t hash_code_impl(const K key);

#include "hashmap.cpp"
#endif
