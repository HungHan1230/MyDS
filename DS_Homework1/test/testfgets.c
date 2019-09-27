#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char key[10];
  char value[20];
} Data;

char fgetstr[20];
char* result = NULL;
Data data[52];

int main() {
  int count = 0;  
  memset(fgetstr, '\0', sizeof(fgetstr)); 

  while (fgets(fgetstr, sizeof(fgetstr), stdin)) {
    // printf("print: %s\n", fgetstr);
    result = strtok(fgetstr,",");
    strcpy(data[count].key, result);
    result = strtok(NULL, ",");
    strcpy(data[count].value, result);
    printf("\nkey : %s, value : %s\n",data[count].key,data[count].value);
    count += 1;    
  }
}