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
/* UTILITY FUNCTIONS */
/* Function to push a node */
void push(struct Node** head_ref, char new_data[256]) {
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
/* Function to find the only person left
   after one in every m-th node is killed
   in a circle of n nodes */
void getJosephusPosition(int m) {
  if (m == 0) {
    printf("Nobody is going to die. \nWhat a wonderful day!\n");
  } else if (m == 1) {
    printf("Oops, everyone is going to die.\n");
  } else {
    struct Node* head = malloc(sizeof(struct Node));
    struct Node* prev = head;
    char file_name[] = "Josephus_data.txt";
    int count = 0;
    char line[256];

    printf("\nRead data from %s... \n", file_name);
    file = fopen(file_name, "r");
    if (file == NULL) {
      printf("No file!\n");
      exit(1);
    }

    while (fgets(line, 256, file)) {
      if (count == 0) {
        line[strlen(line) - 1] = '\0';
        strcpy(head->data, line);
        printf("%s is appended. \n", line);
      }
      // using another pointer prev for Josephus later
      else {
        line[strlen(line) - 1] = '\0';
        prev->next = malloc(sizeof(struct Node));
        strcpy(prev->next->data, line);
        printf("%s is appended. \n", line);
        prev = prev->next;
      }
      count++;
    }
    printf("---------------\nEveryone is ready. Start killing...\n");
    printf(
        "Which side would you like to start "
        "killing?\n\n\t(1)rigth\n\t(2)left\n");
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
        // printf("month: %d, Date: %d\n", (1 + p->tm_mon), p->tm_mday);
        printf("\nFinish killing.\n%s is the final survivor of %d/%d.\n",
               ptr1->data, (1 + p->tm_mon), p->tm_mday);
        // printf("\nFinish killing.\n%s is the final survivor of %d/%d.\n",
        //        ptr1->data, 8, 27);

        break;
      case 2:
        prev->next = head;  // Connect last
                            // node to first
        // printf("test: %s\n",head->next->data);
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
        // printf("month: %d, Date: %d\n", (1 + p->tm_mon), p->tm_mday);
        printf("\nFinish killing.\n%s is the final survivor of %d/%d.\n",
               ptr12->data, (1 + p->tm_mon), p->tm_mday);
        // printf("\nFinish killing.\n%s is the final survivor of %d/%d.\n",
        //        ptr12->data, 8, 27);
        break;
    }

    // printf(
    //     "Last person left standing "
    //     "(Josephus Position) is %s\n ",
    //     ptr1->data);
  }
}
int main() {
  int m;
  time(&timep);
  p = gmtime(&timep);
  // printf("%d %d %d\n", (1900 + p->tm_year), (1 + p->tm_mon), p->tm_mday);
  //   printf("%s %d; %d; %d\n", wday[p->tm_wday], p->tm_hour, p->tm_min,
  //   p->tm_sec);
  printf("month: %d, Date: %d\n", (1 + p->tm_mon), p->tm_mday);
  m = (1 + p->tm_mon) * p->tm_mday % 5;
  printf("%d * %d mod 5 = %d\n", (1 + p->tm_mon), p->tm_mday, m);
  // printf("%d * %d mod 5 = %d\n", 8, 27, m);
  getJosephusPosition(m);

  return 0;
}
// Create a circular linked list of
// size N.
// struct Node* head = malloc(sizeof(struct Node));
// head->data = 1;
// struct Node* prev = head;
// for (int i = 2; i <= n; i++) {
//   prev->next = malloc(sizeof(struct Node));
//   prev->data = i;
//   prev = prev->next;
// }

// struct Node* head = malloc(sizeof(struct Node));
// strcpy(head->data, "Jim");
// struct Node* prev = head;
// prev->next = malloc(sizeof(struct Node));
// strcpy(prev->next->data, "Tom");
// prev = prev->next;
// prev->next = malloc(sizeof(struct Node));
// strcpy(prev->next->data, "Henry");
// prev = prev->next;
// prev->next = malloc(sizeof(struct Node));
// strcpy(prev->next->data, "Hank");
// prev = prev->next;
// prev->next = malloc(sizeof(struct Node));
// strcpy(prev->next->data, "WenJ");
// prev = prev->next;
// prev->next = malloc(sizeof(struct Node));
// strcpy(prev->next->data, "Cody");
// prev = prev->next;
// prev->next = malloc(sizeof(struct Node));
// strcpy(prev->next->data, "Edward");
// prev = prev->next;
// prev->next = malloc(sizeof(struct Node));
// strcpy(prev->next->data, "Ben");
// prev = prev->next;
// prev->next = malloc(sizeof(struct Node));
// strcpy(prev->next->data, "Sine");
// prev = prev->next;
// prev->next = malloc(sizeof(struct Node));
// strcpy(prev->next->data, "PinTsai");
// prev = prev->next;
// prev->next = malloc(sizeof(struct Node));
// strcpy(prev->next->data, "Patty");
// prev = prev->next;
// prev->next = malloc(sizeof(struct Node));
// strcpy(prev->next->data, "Helen");
// prev = prev->next;
// prev->next = malloc(sizeof(struct Node));
// strcpy(prev->next->data, "Haoze");
// prev = prev->next;
// prev->next = malloc(sizeof(struct Node));
// strcpy(prev->next->data, "Yuling");
// prev = prev->next;