#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

FILE* file;
time_t timep;
struct tm* p;
int direction = 0;

/* structure for a node in circular
   linked list */
struct Node {
  char data[30];
  struct Node* next;
};

/* Function to print linked list */
void printList(struct Node* node) {
  printf("\n");
  while (node != NULL) {
    if (node->next != NULL) {
      printf("%s -> ", node->data);
      node = node->next;
    } 
    else {
      printf("%s ", node->data);
      node = node->next;
    }
  }
  printf("\n");
}

/* UTILITY FUNCTIONS */
/* Function to push a node */
void push(struct Node** head_ref, char new_data[256]) {
  struct Node* new_node = malloc(sizeof(struct Node));
  strcpy(new_node->data, new_data);
  new_node->next = (*head_ref);
  (*head_ref) = new_node;
}
/* Function to reverse linked list */
void reverse(struct Node* head_ref) {
  struct Node* prev = NULL;
  struct Node* current = head_ref;
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
  head_ref = prev;
}
// This function rotates a linked list counter-clockwise and
// updates the head. The function assumes that k is smaller
// than size of linked list. It doesn't modify the list if
// k is greater than or equal to size
void rotate(struct Node** head_ref,struct Node** prev, int k) {
  if (k == 0)
    return;
  // Let us understand the below code for example k = 4 and
  // list = 10->20->30->40->50->60.
  // The final answer would be : 50->60->10->20->30->40
  struct Node* current = *head_ref;
  // current will either point to kth or NULL after this loop.
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
  struct Node* kthNode = current;
  // current will point to "last node" after this loop
  while (current->next != NULL)
    current = current->next;
  // Change next of "last node" to previous head(origin head)
  current->next = *head_ref;
  // Change head to (k+1)th node
  // head is now changed to node 50
  *head_ref = kthNode->next;
  // change next of kth node to NULL
  // next of 40 is now NULL
  kthNode->next = NULL;
  *prev = kthNode;  
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

void ReadData(struct Node** head, struct Node** prev) {
  char file_name[] = "data.txt";
  int count = 0;
  char line[256];

//   printf("\nRead data from %s... \n", file_name);
  file = fopen(file_name, "r");
  if (file == NULL) {
    printf("No file!\n");
    exit(1);
  }

  while (fgets(line, 256, file)) {
    if (count == 0) {
      line[strlen(line) - 1] = '\0';
      strcpy((*head)->data, line);
    //   printf("%s is appended. \n", line);
    }
    // using another pointer prev for Josephus later
    else {
      line[strlen(line) - 1] = '\0';
      (*prev)->next = malloc(sizeof(struct Node));
      strcpy((*prev)->next->data, line);
    //   printf("%s is appended. \n", line);
      *prev = (*prev)->next;
    }
    count++;
  }
}
/* Function to find the only person left
   after one in every m-th node is killed
   in the circular linked list. */
void getJosephusPosition(int m) {
  struct Node* head = malloc(sizeof(struct Node));
  struct Node* prev = head;
  ReadData(&head, &prev);
  printf("\n");
  printList(head);

//   printf("---------------\nChange order by odd even function.\n");
  OddEven(&head);
  printList(head);

//   printf("---------------\nChange order by rotate function with index = %d.\n",m);
  rotate(&head,&prev, m);
  printList(head);

//   printf("---------------\nEveryone is ready. Start elimination.\n");
  printf(
      "Which side would you like to start "
      "?\n\n\t(1)rigth\n\t(2)left\n");
  scanf("%d", &direction);

  switch (direction) {
    case 1:      
      prev->next = head;  // Connect last
                          // node to first

      /* while only one node is left in the
      linked list*/
      struct Node *ptr1 = head, *ptr2 = head;
      while (ptr1->next != ptr1) {
        // Find m-th node
        int count = 1;        
        while (count != m) {
          ptr2 = ptr1;
          ptr1 = ptr1->next;
          count++;
        }
        /* Remove the m-th node */
        ptr2->next = ptr1->next;
        ptr1 = ptr2->next;
      }
      printf("\nFinish elimination.\n%s is the final survivor of %d/%d.\n",
             ptr1->data, (1 + p->tm_mon), p->tm_mday);

      break;
    case 2:      
      prev->next = head;  // Connect last
                          // node to first
      reverse(head);      

      /* while only one node is left in the
      linked list*/
      struct Node *ptr12 = head, *ptr22 = head;
      while (ptr12->next != ptr12) {
        // Find m-th node
        int count = 1;
        while (count != m) {
          ptr22 = ptr12;
          ptr12 = ptr12->next;
          count++;
        }
        /* Remove the m-th node */
        ptr22->next = ptr12->next;
        ptr12 = ptr22->next;
      }
      printf("\nFinish elimination.\n%s is the final survivor of %d/%d.\n",
             ptr12->data, (1 + p->tm_mon), p->tm_mday);
      break;
  }
}

int main() {
  int m;
  time(&timep);
  p = gmtime(&timep);
  printf("Today is %d/%d.\n", (1 + p->tm_mon), p->tm_mday);
  m = (1 + p->tm_mon) * p->tm_mday % 5;  
  printf("%d * %d mod 5 = %d\n", (1 + p->tm_mon), p->tm_mday, m);
  // printf("%d * %d mod 5 = %d\n", 8, 27, m);
  if (m == 0) {
    printf("default m = 2\n");
    m = 2;
  } 
  else
    printf("m = %d\n", m);

  getJosephusPosition(m);

  return 0;
}
