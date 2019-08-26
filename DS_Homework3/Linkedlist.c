#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Link list node */
struct Node {
  char data[10];
  struct Node* next;
};

FILE* file;

// This function rotates a linked list counter-clockwise and
// updates the head. The function assumes that k is smaller
// than size of linked list. It doesn't modify the list if
// k is greater than or equal to size
void rotate(struct Node** head_ref, int k) {
  if (k == 0)
    return;

  // Let us understand the below code for example k = 4 and
  // list = 10->20->30->40->50->60.
  struct Node* current = *head_ref;

  // current will either point to kth or NULL after this loop.
  //  current will point to node 40 in the above example
  int count = 1;
  while (count < k && current != NULL) {
    current = current->next;
    count++;
  }

  // If current is NULL, k is greater than or equal to count
  // of nodes in linked list. Don't change the list in this case
  if (current == NULL)
    return;

  // current points to kth node. Store it in a variable.
  // kthNode points to node 40 in the above example
  struct Node* kthNode = current;

  // current will point to last node after this loop
  // current will point to node 60 in the above example
  while (current->next != NULL)
    current = current->next;

  // Change next of last node to previous head
  // Next of 60 is now changed to node 10
  current->next = *head_ref;

  // Change head to (k+1)th node
  // head is now changed to node 50
  *head_ref = kthNode->next;

  // change next of kth node to NULL
  // next of 40 is now NULL
  kthNode->next = NULL;
}
/* Function to reverse the linked list */
static void reverse(struct Node** head_ref) {
  struct Node* prev = NULL;
  struct Node* current = *head_ref;
  struct Node* next = NULL;
  while (current != NULL) {
    // Store next
    next = current->next;

    // Reverse current node's pointer
    current->next = prev;

    // Move pointers one position ahead.
    prev = current;
    current = next;
  }
  *head_ref = prev;
}
// Main function that inserts nodes of linked list q into p at
// alternate positions. Since head of first list never changes
// and head of second list  may change, we need single pointer
// for first list and double pointer for second list.
void merge(struct Node* p, struct Node** q) {
  struct Node *p_curr = p, *q_curr = *q;
  struct Node *p_next, *q_next;

  // While there are avialable positions in p
  while (p_curr != NULL && q_curr != NULL) {
    // Save next pointers
    p_next = p_curr->next;
    q_next = q_curr->next;

    // Make q_curr as next of p_curr
    q_curr->next = p_next;  // Change next pointer of q_curr
    p_curr->next = q_curr;  // Change next pointer of p_curr

    // Update current pointers for next iteration
    p_curr = p_next;
    q_curr = q_next;
  }

  *q = q_curr;  // Update head pointer of second list
}
/* Function to change the order of the linked list*/
void OddEven(struct Node** head) {
  if ((*head) || (*head)->next) {
    struct Node* previous = (*head);
    struct Node* current = (*head)->next;
    while (current && current->next) {
      struct Node* tmp = previous->next;
      previous->next = current->next;
      current->next = current->next->next;
      previous->next->next = tmp;
      current = current->next;
      previous = previous->next;
    }
  }
}

/* UTILITY FUNCTIONS */
/* Function to push a node */
void push(struct Node** head_ref, char new_data[10]) {
  // printf("pushing data : %s\n",new_data);
  /* allocate node */
  struct Node* new_node = malloc(sizeof(struct Node));

  /* put in the data  */
  //*new_node->data = new_data;
  strcpy(new_node->data, new_data);

  /* link the old list off the new node */
  new_node->next = (*head_ref);

  /* move the head to point to the new node */
  (*head_ref) = new_node;
}

/* Function to print linked list */
void printList(struct Node* node, int num) {
  printf("List%d: ", num);
  while (node != NULL) {
    printf("%s ", node->data);
    node = node->next;
  }
  printf("\n");
}

void ReadData(struct Node** head_ref, struct Node** head_ref2) {
  char file_name[] = "LinkedList_data.txt";
  char line[100];
  char* result = NULL;
  char* delim = " ";
  // char * pch;
  memset(line, '\0', sizeof(line));

  file = fopen(file_name, "r");
  if (!file) {
    fprintf(stderr, "failed to open file answer_dic.csv\n");
  }
  int count = 0;

  while (fgets(line, 100, file) != NULL) {
    line[strlen(line) - 1] = '\0';
    result = strtok(line, delim);
    while (result != NULL) {
      if (count == 0) {
        push(head_ref, result);
      } else {
        push(head_ref2, result);
      }
      // printf("%s\t", result);
      result = strtok(NULL, delim);
    }
    count++;
  }

  // push(head_ref, "love");
  // push(head_ref, "is");
  // push(head_ref, "if");
  // push(head_ref, "I");
  // push(head_ref, "know");
  // push(head_ref, "what");

  // push(head_ref2, "you");
  // push(head_ref2, "it");
  // push(head_ref2, "is");
  // push(head_ref2, "because");
  // push(head_ref2, "of");
}

int main() {
  struct Node* head = NULL;
  struct Node* head2 = NULL;
  printf(
      "Follow the given instruction to run the code operation. \n1. "
      "push \n2. rotate \n3. reverse\n4. merge\n5. odd even \n");
  /*push data to the linked lists */
  printf("\n1.push\nStart creating a list from file. \n");
  ReadData(&head, &head2);
  printf("The linked lists \n");
  printList(head, 1);
  printList(head2, 2);

  /*Rotate the linked lists, k = 4 */
  printf("\n\n2.Rotate\nRotate the linked list by given k = 4.\n");

  rotate(&head, 4);
  rotate(&head2, 4);
  printf("Rotated Linked lists \n");
  printList(head, 1);
  printList(head2, 2);

  /*Reverse the linked lists */
  printf("\n\n3.Reverse\nReverse the linked.\n");
  reverse(&head);
  reverse(&head2);
  printf("Reversed Linked lists \n");
  printList(head, 1);
  printList(head2, 2);

  /*Merge the two linked lists */
  printf("\n\n4.Merge\nMerge List2 to List1.\n");
  merge(head, &head2);
  printList(head, 1);
  printList(head2, 2);

  /*Merge the two linked lists */
  printf("\n\n5.OddEven\nChange the order by OddEven.\n");
  OddEven(&head);
  printList(head, 1);
  /*Think about what can merge function be a little bit different than just
   * append it to the tail of List1. */
  /*Pop. Delete the last two node */
  /*printf("\n\n7.Pop\nDelete the last two nodes.\n");*/
  /*Find the finall answer by changing the numbers to ASCII */

  printf("\n");

  return 0;
}
