#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* file;
/* Link list node */
struct Node {
  char data[10];
  struct Node* next;
};
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
void printList(struct Node* node) {
  printf("List: ");
  while (node != NULL) {
    printf("%s ", node->data);
    node = node->next;
  }
  printf("\n");
}

void ReadData(struct Node** head_ref) {
  char file_name[] = "lps_data.txt";
  printf("Read Data... \n");
  file = fopen(file_name, "r");
  if (file == NULL) {
    printf("No file!\n");
    exit(1);
  }
  
  char line[256];
  while (fgets(line, 256, file)) {
    line[strlen(line) - 1] = '\0';
    push(head_ref, line);
    printf("%s is appended.\n", line);
  }

  // push(head_ref, "geeeks");
  // push(head_ref, "geeeksfor");
  // push(head_ref, "geeeder");
  //push(head_ref, "ge");
}
int _compare(char str1, char str2) {
  if (str1 != str2)
    return 0;
  else {    
    return 1;
  }
}

int compare(char str1[10], char str2[10], char answer[10]) {
  int ans = 0;
  for (int i = 0; i < strlen(str1); i++) {    
    if (_compare(str1[i], str2[i]) == 0) {
      break;
    }
    answer[i] = str1[i];
    ans = 1; 
  }  
  return ans; 
}

void lps(struct Node** head_ref) {
  char str[10];
  char answer[10];

  memset(answer, '\0', sizeof(answer));
  strcpy(str, (*head_ref)->data);  

  struct Node* previous = (*head_ref);
  struct Node* current = (*head_ref)->next;
  while (current && current->next) {
    if (compare(str, current->next->data, answer) == 0)
      printf("There's no longest common prefix exists.\n");
    break;
    current = current->next;

    // struct Node* tmp = previous->next;
    // previous->next = current->next;
    // current->next = current->next->next;
    // previous->next->next = tmp;
    // current = current->next;
    // previous = previous->next;
  }
  printf("The longest common prefix is: %s \n", answer);
}
int main() {
  struct Node* head = NULL;
  ReadData(&head);
  printf("\n");
  printList(head);
  lps(&head);  
}