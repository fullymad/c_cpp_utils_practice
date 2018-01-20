/*
  Reverse a linked list and return pointer to the head
  The input list will have at least one element  
  Node is defined as 
*/
#include <stdio.h>

  typedef struct Node
  {
     int data;
     struct Node *next;
  } Node;

Node* Reverse(Node *head)
{
  // Complete this method
	Node	*new_head;
	Node	*save_next;

	if (head == NULL) {
		new_head = NULL;
	}
	else if (head->next != NULL) {
		save_next = head->next;
		new_head = Reverse(head->next);
		save_next->next = head;
		head->next = NULL;
	}
	else {
		new_head = head;
	}

	return new_head;
}

int
main() {
			return 0;
}
