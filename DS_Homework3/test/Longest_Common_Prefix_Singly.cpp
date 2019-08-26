// C++ Program to find the longest common prefix 
// in an array of strings 
#include <bits/stdc++.h> 
using namespace std; 

// Structure for a node in the linked list 
struct Node { 
	char data; 
	Node* next; 
}; 

// Function to print the data in the linked list 
// Remaining nodes represent the longest common prefix 
void printLongestCommonPrefix(Node* head) 
{ 
	// If the linked list is empty there is 
	// no common prefix 
	if (head == NULL) { 
		cout << "There is no common prefix\n"; 
		return; 
	} 

	// Printing the longest common prefix 
	cout << "The longest common prefix is "; 
	while (head != NULL) { 
		cout << head->data; 
		head = head->next; 
	} 
} 

// Function that creates a linked list of characters 
// for the first word in the array of strings 
void Initialise(Node** head, string str) 
{ 
	// We calculate the length of the string 
	// as we will insert from the last to the 
	// first character 
	int l = str.length(); 

	// Inserting all the nodes with the characters 
	// using insert at the beginning technique 
	for (int i = l - 1; i >= 0; i--) { 
		Node* temp = new Node; 
		temp->data = str[i]; 
		temp->next = *head; 
		*head = temp; 
	} 

	// Since we have passed the address of the 
	// head node it is not required to return 
	// anything 
} 

// Function to delete all the nodes 
// from the unmatched node till the end of the 
// linked list 
void deleteNodes(Node* head) 
{ 
	// temp is used to facilitate the deletion of nodes 
	Node* current = head; 
	Node* next; 
	while (current != NULL) { 
		next = current->next; 
		free(current); 
		current = next; 
	} 
} 

// Function that compares the character of the string with 
// the nodes of the linked list and deletes all nodes after 
// the characters that do not match 
void longestCommonPrefix(Node** head, string str) 
{ 
	int i = 0; 

	// Use the pointer to the previous node to 
	// delete the link between the unmatched node 
	// and its prev node 
	Node* temp = *head; 
	Node* prev = *head; 
	while (temp != NULL) { 

		// If the current string finishes or if the 
		// the characters in the linked list do not match 
		// with the character at the corresponding position 
		// delete all the nodes after that. 
		if (str[i] == '\0' || temp->data != str[i]) { 

			// If the first node does not match then there 
			// is no common prefix 
			if (temp == *head) { 
				free(temp); 
				*head = NULL; 
			} 

			// Delete all the nodes starting from the 
			// unmatched node 
			else { 
				prev->next = NULL; 
				deleteNodes(temp); 
			} 
			break; 
		} 

		// If the character matches, move to next 
		// node and store the address of the current 
		// node in prev 
		prev = temp; 
		temp = temp->next; 
		i++; 
	} 
} 

int main() 
{ 
	string arr[] = { "geeksforgeeks", "geeks", "geek", "geezer", 
					"geekathon" }; 
	int n = sizeof(arr) / sizeof(arr[0]); 

	struct Node* head = NULL; 

	// A linked list is created with all the characters 
	// of the first string 
	Initialise(&head, arr[0]); 

	// Process all the remaining strings to find the 
	// longest common prefix 
	for (int i = 1; i < n; i++) 
		longestCommonPrefix(&head, arr[i]); 

	printLongestCommonPrefix(head);
    printf("\n"); 
} 
