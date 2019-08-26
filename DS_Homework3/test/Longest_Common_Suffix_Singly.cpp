// C++ program to find the Longest Common 
// suffix in linked lists 
#include <bits/stdc++.h> 
using namespace std; 

/* Linked list node */
struct Node 
{ 
	char data; 
	struct Node* next; 
}; 

/* Function to insert a node at the beginning of 
the linked list */
void push(struct Node **head_ref, int new_data) 
{ 
	struct Node* new_node = new Node; 
	new_node->data = new_data; 
	new_node->next = *head_ref; 
	*head_ref = new_node; 
} 

/* Function to reverse the linked list */
struct Node *reverseList(struct Node *head_ref) 
{ 
	struct Node *current, *prev, *next; 
	current = head_ref; 
	prev = NULL; 

	while (current != NULL) 
	{ 
		next = current->next; 
		current->next = prev; 
		prev = current; 
		current = next; 
	} 
	return prev; 
} 


// Utility function to print last n nodes 
void printLastNNode(struct Node* head, int n) 
{ 
	// if n == 0 
	if (n <= 0) 
		return; 

	// Move reference pointer n positions ahead 
	struct Node* ref_ptr = head; 
	while (ref_ptr != NULL && n--) 
		ref_ptr = ref_ptr->next; 

	// Now move main and reference pointers at 
	// same speed. By the end of this loop, 
	// reference pointer would point to end and 
	// main pointer would point to n-th node 
	// from end. 
	Node *main_ptr = head; 
	while (ref_ptr != NULL) { 
		main_ptr = main_ptr->next; 
		ref_ptr = ref_ptr->next; 
	} 

	// Print last n nodes. 
	while (main_ptr != NULL) 
	{ 
	cout << main_ptr->data; 
	main_ptr = main_ptr->next; 
	} 
} 

// Prints the Longest Common suffix in 
// linked lists 
void longestCommSuffix(Node *h1, Node *h2) 
{ 
	// Reverse Both Linked list 
	h1 = reverseList(h1); 
	h2 = reverseList(h2); 

	// Now we print common nodes from head 
	Node *temp1 = h1, *temp2 = h2; 
	int count = 0; 
	while (temp1!=NULL&&temp2!=NULL) 
	{ 
		// If a node is not common, break 
		if (temp1 -> data != temp2 -> data) 
			break; 

		// Keep printing while there are 
		// common nodes. 
		count++; 
		temp1 = temp1 -> next; 
		temp2 = temp2 -> next; 
	} 

	// Reversing linked lists to retain 
	// original lists. 
	h1 = reverseList(h1); 
	h2 = reverseList(h2); 

	printLastNNode(h1, count); 
} 

// Driver program to test above 
int main() 
{ 
	struct Node *h1 = NULL, *h2 = NULL; 

	// creating the 1 linked list 
	push(&h1,'g'); 
	push(&h1,'n'); 
	push(&h1,'i'); 
	push(&h1,'k'); 
	push(&h1,'l'); 
	push(&h1,'a'); 
	push(&h1,'w'); 

	// creating the 2 linked list 
	push(&h2,'g'); 
	push(&h2,'n'); 
	push(&h2,'i'); 
	push(&h2,'n'); 
	push(&h2,'e'); 
	push(&h2,'t'); 
	push(&h2,'s'); 
	push(&h2,'i'); 
	push(&h2,'l'); 

	longestCommSuffix(h1, h2); 

    printf("\n");

	return 0; 
} 
