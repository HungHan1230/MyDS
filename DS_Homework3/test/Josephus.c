#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* structure for a node in circular
   linked list */
struct Node {
  int data;
  struct Node* next;
};

/* Function to find the only person left
   after one in every m-th node is killed
   in a circle of n nodes */
void getJosephusPosition(int m, int n) {
  if (m == 0) {
    printf("Nobody dead.\n");
  } 
  else if (m == 1) {
    printf("Everyone dead.\n");
  } 
  else {
    // Create a circular linked list of
    // size N.
    struct Node* head = malloc(sizeof(struct Node));
    head->data = 1;
    struct Node* prev = head;
    for (int i = 2; i <= n; i++) {
      prev->next = malloc(sizeof(struct Node));
      prev->next->data = i;
      prev = prev->next;
    }
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

    printf(
        "Last person left standing "
        "(Josephus Position) is %d\n ",
        ptr1->data);
  }
}

/* Driver program to test above functions */
int main() {
  int n = 14, m = 2;

  // char* wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  time_t timep;
  struct tm* p;
  time(&timep);
  p = gmtime(&timep);
  // printf("%d %d %d\n", (1900 + p->tm_year), (1 + p->tm_mon), p->tm_mday);
  //   printf("%s %d; %d; %d\n", wday[p->tm_wday], p->tm_hour, p->tm_min,
  //   p->tm_sec);
  printf("month: %d, Date: %d\n", (1 + p->tm_mon), p->tm_mday);
  //m = (1 + p->tm_mon) * p->tm_mday % 3;
  m = 8 * 25 % 3;
  printf("%d * %d mod 3 = %d\n",(1 + p->tm_mon), p->tm_mday, m);

  getJosephusPosition(m, n);

  return 0;
}