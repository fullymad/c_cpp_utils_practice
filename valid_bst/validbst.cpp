/******************************************************************************
https://www.hackerrank.com/challenges/ctci-is-binary-search-tree/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=trees
******************************************************************************/
#include <unordered_set>
using namespace std;

/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node struct is defined as follows:
	struct Node {
		int data;
		Node* left;
		Node* right;
	}
*/

bool validBST(
	Node*   node,
	int		min,
	int		max
	//std::unordered_map<int, bool>  &data_set
) {
	int			data, left_data, right_data;
	//pair<iterator, bool>	ins_result;

	if (node == NULL) {
		return true;
	}

	// If duplicate found, BST is invalid
	//ins_result = data_set.emplace(node->data, true);
	//if (ins_result.second == false) {
	//	result = false;
	//}

	data = node->data;

	if (node->left != NULL) {
		left_data = node->left->data;
		if (left_data >= data || left_data < min || left_data > max) {
			return false;
		}
	}

	if (node->right != NULL) {
		right_data = node->right->data;
		if (right_data <= data || right_data < min || right_data > max) {
			return false;
		}
	}

	if (!validBST(node->left, min, data - 1) ||
		!validBST(node->right, data + 1, max)) {
		return false;
	}

	return true;

} // end validBST
    
bool checkBST(Node* root) {
	int		min = 0;
	int		max = 10000;

	//std::unordered_map<int, bool>	data_set; // Stores unique data values

	if (root == NULL) {
		return true;
	}

	return validBST(root, min, max);
}
