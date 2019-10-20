#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

time_t timep;
struct tm* p;
int direction = 0;
char NumForRotate[5];
char NumForKill[5];
char NumForDirection[5];

/* structure for a node in circular
   linked list */
struct Node {
  char data[30];
  struct Node* next;
};

/* Function to print linked list */
void printList(struct Node* node) {
  while (node != NULL) {
    if (node->next != NULL) {
      printf("%s -> ", node->data);
      node = node->next;
    } else {
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
void rotate(struct Node** head_ref, struct Node** prev, int k) {
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
  int count = 0;
  char line[256];

  freopen("data.txt", "r", stdin);
  fgets(NumForRotate, sizeof(NumForRotate), stdin);
  fgets(NumForDirection, sizeof(NumForDirection), stdin);
  fgets(NumForKill, sizeof(NumForKill), stdin);

  while (fgets(line, 256, stdin)) {
    if (count == 0) {
      line[strlen(line) - 1] = '\0';
      strcpy((*head)->data, line);
      //   printf("%s is appended. \n", line);
    }
    // using another pointer prev for Josephus later
    else {
      // take out the '\n' charater, or the result of execution would be pretty
      // awful!
      if (line[strlen(line) - 1] == '\n')
        line[strlen(line) - 1] = '\0';
      (*prev)->next = malloc(sizeof(struct Node));
      strcpy((*prev)->next->data, line);
      //   printf("%s is appended. \n", line);
      *prev = (*prev)->next;
    }
    count++;
  }
  fclose(stdin);
}
/* Function to find the only person left
   after one in every m-th node is killed
   in the circular linked list. */
void getJosephusPosition() {
  struct Node* head = malloc(sizeof(struct Node));
  struct Node* prev = head;
  int m,NumRotate,NumDirection;
  ReadData(&head, &prev);
  m = atoi(NumForKill);
  NumRotate = atoi(NumForRotate);
  printList(head);

  //   printf("---------------\nChange order by odd even function.\n");
  OddEven(&head);
  printList(head);

  //   printf("---------------\nChange order by rotate function with index =
  //   %d.\n",m);
  rotate(&head, &prev, NumRotate);
  printList(head);

  //   printf("---------------\nEveryone is ready. Start elimination.\n");
  // printf(
  //     "Which side would you like to start "
  //     "?\n\n\t(1)rigth\n\t(2)left\n");
  // scanf("%d", &direction);
  // int direction = m % 2 + 1;
  NumDirection = atoi(NumForDirection);

  switch (NumDirection) {
    case 1:
      // printf("right\n");
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
        printf("%s is killed!\n", ptr2->next->data);
        ptr2->next = ptr1->next;
        ptr1 = ptr2->next;
      }
      printf("%s\n", ptr1->data);
      break;
    case 2:
      // printf("left\n");
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
        printf("%s is killed!\n", ptr22->next->data);
        ptr22->next = ptr12->next;
        ptr12 = ptr22->next;
      }
      printf("%s\n", ptr12->data);
      break;
  }
}

int main() {
  getJosephusPosition();
  return 0;
}
