#include <stdio.h>
#include <string.h>
#define max 1024

int lps(char* want, int* answer) {
  int len = 5, key = -1, i = 0, count = 0;
  answer[0] = -1;
  key = -1;

  for (i = 1; i < len; i++) {
    while (key >= 0 && want[key + 1] != want[i])
      key = answer[key];
    if (want[key + 1] == want[i])
      key++;
    answer[i] = key;
  }

  for (i = 0; i < 5; i++) {
    // printf("%d\n",answer[i]);									/check the answer array
    // lps number
    count += (answer[i] + 1);
  }

  return count;
}
int failure(int index, int* an) {
  return an[index];
}
int pare(char* set,
         int setnum,
         char* pattern,
         int pattern_num,
         int* index,
         int* an,
         int catch) {
  int count = 0;
  int i = 0, j = 0;
  while (i < setnum) {
    while (i < setnum && j < pattern_num) {
      if (set[i] == pattern[j]) {
        i++;
        j++;
      } 
	  else if (j == 0){
		  i++;
	  }        
      else
        j = an[j - 1] + 1;
      // j = failure(j - 1, an) + 1;
    }
    index[count++] = i - 5 + catch;
    j = 0;
  }
  count--;
  return count;
}
void find_dictionary(int* index, int number) {
  char dic[max];
  char* pointer;
  char alph[5], string[max];
  int i = 0, lengh = 0;
  while (fgets(dic, max, stdin) != NULL && i < number) {
    lengh = strlen(dic);
    dic[--lengh] = 0;
    //		printf("%s\n",dic);
    pointer = strtok(dic, ",");
    strcpy(alph, pointer);
    pointer = strtok(NULL, "\n");
    strcpy(string, pointer);
    //		printf("%s",alph);
    //		printf("%s",string);

    if (alph[0] == index[i] && i == 0) {
      printf("%s", string);
      i++;
    } else if (alph[0] == index[i] && i != 0) {
      printf(" %s", string);
      i++;
    }
  }
  printf("\n");
  return;
}
int main() {
  int strengh = 0, i = 0;
  char insert[max];

  fgets(insert, max, stdin);
  strengh = strlen(insert);
  insert[--strengh] = 0;

  for (i = 0; i < strengh; i++) {
    if (insert[i] <= 77)
      insert[i] += 13;
    else if (insert[i] >= 77 && insert[i] <= 90)
      insert[i] -= 13;
    else if (insert[i] > 90 && insert[i] <= 109)
      insert[i] += 13;
    else
      insert[i] -= 13;
  }

  printf("%s\n", insert);

  char pattern[6];

  for (i = 0; i < 5; i++)
    pattern[i] = insert[i];

  printf("%s\n", pattern);

  int an[7], catch = 0;

  catch = lps(pattern, an);
  printf("%d\n", catch);
  // for(i=0;i<5;i++)printf("%d\n",an[i]);

  // find the word and return index
  char sentence[4096];
  fgets(sentence, 4096, stdin);
  strengh = strlen(sentence);
  sentence[strengh - 1] = 0;  // sure that data in
  // printf("%s\n",sentence);

  int index[max], number = 0;
  number = pare(sentence, strengh - 1, pattern, 5, index, an, catch);

  for (i = 0; i < number; i++)
    printf("%d\n", index[i]);

  find_dictionary(index, number);

  return 0;
}