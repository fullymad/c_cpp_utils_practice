#include <iostream>
#include <string>
#include <exception>
using namespace std;

#include "listnode.h"
#include "hashmap.h"

int
main(
	int		argc,
	char	*argv[]
)
{
	try {
		std::pair<string,int> pair1("raksha", 16);

		ListNode<int> list_int(10);
		ListNode<int> list_int2(22);
		ListNode<string> str_node("dad");
		HashMap<string, int> map(32);
		HashMap<unsigned int, int> map_int(32);
		int i = list_int.get_data();
		list_int.set_next(&list_int2);
		int second = list_int.get_next()->get_data();

		string s1 = "madhu";

		cout << s1 << endl;
		cout << list_int.get_data() << endl;
		cout << str_node.get_data() << endl;
		cout << second << endl;

		cout << pair1.first << "..." << pair1.second << endl;

		map.print("String map that is empty");
		map.put("gold", 1);

		unsigned int shifted = (64 >> 1) - 1;
		cout << shifted << endl;

		map_int.print("Int map that is empty");
		map_int.put(75, 1);
		map_int.put(75 + 3 * 64, 30);
		map_int.put(75 + 5 * 64, 500);
		map_int.put(75 + 3 * 64, 3000); /* Update middle element */
		map_int.print("Int map after updating middle element");

		map_int.put(75 + 5 * 64, 5000); /* Update first element */
		map_int.print("Int map after updating first element");
		map_int.remove(23);

		map.print("String map");
		map_int.print("Int map");
		map.remove("gold");
		map.print("String map after removing only element");

		map.put("silver", 200);
		map.put("bronze", 400);
		map.put("aluminum", 600);

		map.print("String map after added 3");

		map.remove("silver");
		map.print("String map after removing last element");

		map.remove("aluminum");
		map.print("String map after removing first element");

		map.put("lion", 745);
		map.put("tiger", 845);
		map.put("snake", 945);
		map.put("coyote", 1045);
		map.put("rhino", 1145);
		map.print("String map after adding 5 elements");
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}

	exit(0);

} /* end main */
