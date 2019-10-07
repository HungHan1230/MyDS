#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tempTextMAX 128

typedef struct {
  char* dic;
} Dic;

void ROT13(char*, char*);
void KMP(char*, char*, int*, int, Dic*);
int calLps(char*, int*);

int main() {
  unsigned int currentSize = 0;
  char* cipherText = malloc(tempTextMAX);
  char* article = malloc(tempTextMAX);
  char pattern[6];
  int ch, i, j, sumOfLps;
  int lps[5];
  Dic answer[52];
  pattern[5] = '\0';
  // ---------------------- input cipherText
  ch = EOF;
  i = 0;
  currentSize = tempTextMAX;
  while ((ch = getchar()) != '\n' && ch != EOF) {
    cipherText[i++] = (char)ch;
    if (i == currentSize) {
      currentSize = i + tempTextMAX;
      cipherText = realloc(cipherText, currentSize);
    }
  }
  cipherText[i] = '\0';
  // ---------------------- input article
  ch = EOF;
  i = 0;
  currentSize = tempTextMAX;
  while ((ch = getchar()) != '\n' && ch != EOF) {
    article[i++] = (char)ch;
    if (i == currentSize) {
      currentSize = i + tempTextMAX;
      article = realloc(article, currentSize);
    }
  }
  article[i] = '\0';
  // ---------------------- input answer Dictionary
  for (j = 0; j < 52; j++) {
    ch = EOF;
    i = 0;
    currentSize = tempTextMAX;
    answer[j].dic = malloc(tempTextMAX);
    while ((ch = getchar()) != '\n' && ch != EOF) {
      answer[j].dic[i++] = (char)ch;
      if (i == currentSize) {
        currentSize = i + tempTextMAX;
        answer[j].dic = realloc(answer[j].dic, currentSize);
      }
    }
    answer[j].dic[i] = '\0';
  }

  ROT13(cipherText, pattern);
  sumOfLps = calLps(pattern, lps);
  printf("%s\n", pattern);
  printf("%d\n", sumOfLps);
  KMP(article, pattern, lps, sumOfLps, answer);
  free(cipherText);
  free(article);
  for (j = 0; j < 52; j++) {
    free(answer[j].dic);
  }
  return 0;
}

void ROT13(char* inputText, char* outputText) {
  int i;
  for (i = 0; i < strlen(inputText); i++) {
    if (inputText[i] > 'A' && inputText[i] < 'Z') {
      printf("%c", (inputText[i] - 'A' + 13) % 26 + 'A');
      if (i < 5) {
        outputText[i] = (inputText[i] - 'A' + 13) % 26 + 'A';
      }
    } else {
      printf("%c", (inputText[i] - 'a' + 13) % 26 + 'a');
      if (i < 5) {
        outputText[i] = (inputText[i] - 'a' + 13) % 26 + 'a';
      }
    }
  }
  printf("\n");
}

int calLps(char* inputPattern, int* lpsArray) {
  int sum, i, j;
  lpsArray[0] = 0;
  j = 0;
  for (i = 1; i < strlen(inputPattern); i++) {
    if (inputPattern[j] == inputPattern[i]) {
      j++;
      lpsArray[i] = j;
    } else {
      j = 0;
      if (inputPattern[j] == inputPattern[i]) {
        j++;
        lpsArray[i] = j;
      } else {
        lpsArray[i] = 0;
      }
    }
  }
  sum = 0;
  for (i = 0; i < strlen(inputPattern); i++) {
    sum = sum + lpsArray[i];
  }
  return sum;
}

void KMP(char* inputArticle,
         char* checkPattern,
         int* lpsArray,
         int sum,
         Dic* ans) {
  printf("entering KMP()...\n");
  int i, j, numOfKey, currentSize;
  int* key_index;
  i = 0;
  j = 0;
  numOfKey = 0;
  currentSize = tempTextMAX;
  key_index = malloc(tempTextMAX);
  while (i < strlen(inputArticle)) {
    if (inputArticle[i] == checkPattern[j]) {
      if (j == 4) {
        key_index[numOfKey] = i - 4 + sum;
        printf("%d\n", key_index[numOfKey]);
        numOfKey++;
        if (numOfKey == currentSize) {
          currentSize = numOfKey + tempTextMAX;
        }
        j = lpsArray[j];
        i++;
      } else {
        i++;
        j++;
      }
    } else if (j == 0) {
      i++;
    } else {
      j = lpsArray[j];
    }
  }
  for (i = 0; i < numOfKey; i++) {
    if (key_index[i] - 'A' > 26) {
      printf("%s", &ans[key_index[i] - 'A' - ('a' - 'Z' - 1)].dic[2]);
      printf(" ");
    } else if (key_index[i] - 'A' < 0) {
    } else {
      printf("%s", &ans[key_index[i] - 'A'].dic[2]);
      printf(" ");
    }
  }
  free(key_index);
}
