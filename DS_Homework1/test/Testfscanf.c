#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char key[10];
  char value[20];
} Data;

FILE* file;
char csvdata[50];

void ReadFile() {
  file = fopen("answer_dic.csv", "r");
  //   fscanf(file, "%s", csvdata);
  //   printf("%s\n", csvdata);
  int count = 0;
  while (fscanf(file, "%[^\n]%*c", csvdata) != EOF) {
    printf("%d : %s\n", count, csvdata);
    count++;
  }
  char fgetstr[20];
  memset(fgetstr, '\0', sizeof(fgetstr));
  // fgets(fgetstr, sizeof(fgetstr), stdin);
  // printf("%s", fgetstr);

  while (fgets(fgetstr, sizeof(fgetstr), stdin)) {
    printf("print: %s\n",fgetstr);
  }

  fclose(file);
}
/*
 while(fscanf(fp, "%s", buff)!=EOF){
   printf("%s ", buff );
   }
 */

int main() {
  ReadFile();
  return 0;
}