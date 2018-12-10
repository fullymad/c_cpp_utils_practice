/******************************************************************************
https://www.hackerrank.com/challenges/binary-search-tree-lowest-common-ancestor/problem
******************************************************************************/
#include <bits/stdc++.h>

using namespace std;

class Node {
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d) {
            data = d;
            left = NULL;
            right = NULL;
        }
};

class Solution {
    public:
  		Node* insert(Node* root, int data) {
            if(root == NULL) {
                return new Node(data);
            } else {
                Node* cur;
                if(data <= root->data) {
                    cur = insert(root->left, data);
                    root->left = cur;
                } else {
                    cur = insert(root->right, data);
                    root->right = cur;
               }

               return root;
           }
        }

/*The tree node has data, left child and right child 
class Node {
    int data;
    Node* left;
    Node* right;
};

*/
  
// Developed code is below (the above was already provided along with 'main'
    Node *lca(Node *root, int v1,int v2) {
		// Write your code here.
        Node *child;
        Node *result = NULL;

        if (root == NULL) {
            result = NULL;
        }
        // If elements on left and right subtrees, it is the LCA
        else if ((v1 < root->data && v2 > root->data) ||
            (v2 < root->data && v1 > root->data)) {
            result = root;
        }
        // If node has one of the 2 values, it is the LCA
        else if (v1 == root->data || v2 == root->data) {
            result = root;
        }
        else {
            // Get LCA from the child that has the 2 elements
            child = (v1 > root->data) ? root->right : root-> left;
            result = lca(child, v1, v2);
        }
        
        return result;
    }

}; //End of Solution
