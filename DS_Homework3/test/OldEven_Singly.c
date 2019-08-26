// Iterative C program to reverse a linked list
#include <stdio.h>
#include <stdlib.h>

/* Link list node */
struct Node {
  int data;
  struct Node* next;
};

/* Function to push a node */
void push(struct Node** head_ref, int new_data) {
  struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
  new_node->data = new_data;
  new_node->next = (*head_ref);
  (*head_ref) = new_node;
}

/* Function to print linked list */
void printList(struct Node* head) {
  struct Node* temp = head;
  while (temp != NULL) {
    printf("%d  ", temp->data);
    temp = temp->next;
  }
}

/* Function to change the order of the linked list*/
void OddEven(struct Node** head){
    if((*head) || (*head)->next){
        struct Node* previous = (*head);
        struct Node* current = (*head)->next;
        while(current && current->next){
            struct Node* tmp = previous->next;
            previous->next = current->next;
            current->next = current->next->next;
            previous->next->next = tmp;
            current = current->next;
            previous = previous -> next;            
        }
    }
        
    /* 
    if ((*head) != NULL || (*head)->next != NULL || (*head)->next != NULL){
        struct Node* tmp = (struct Node*)malloc(sizeof(struct Node));
        struct Node* odd = (*head);
        struct Node* even = (*head)->next;

        while(even != NULL && even->next != NULL){
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }
        odd->next = tmp;
    }
    */

    /*
     if (head == null || head.next == null || head.next.next == null) return head;//如果該連結串列內節點數在兩個及以下直接返回頭節點
        ListNode tmp = head.next;//暫存偶節點的第一個
        ListNode odd = head;//奇節點的第一個
        ListNode even = head.next;//偶節點的第一個
        while (even != null && even.next != null) {//迴圈條件，偶節點遇空時結束
            odd.next = even.next;//奇節點指向偶節點的下一個節點
            odd = odd.next;//重新整理奇連結串列指標
            even.next = odd.next;//偶節點指向奇節點的下一個節點
            even = even.next;//重新整理偶連結串列指標
        }
        odd.next = tmp;//連線雙鏈表
     */
}

/* Driver program to test above function*/
int main() {
  /* Start with the empty list */
  struct Node* head = NULL;

  push(&head, 1);
  push(&head, 2);
  push(&head, 3);
  push(&head, 4);
  push(&head, 5);

  OddEven(&head);

  printList(head);  
  printf("\n");
}