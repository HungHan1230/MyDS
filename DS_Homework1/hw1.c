#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char key[10];
  char value[20];
} Data;

int sumoflps;
char indexArray[3];
char txt[400];
char passwd[10];
char ciphertext[100];

char fgetstr[20];
char* result = NULL;
Data data[52];

void Read() {
  int count = 0;

    // scanf("%s", ciphertext);
  fgets(ciphertext, sizeof(ciphertext), stdin);
    // scanf("%[^\n]s\n", txt);
  fgets(txt, sizeof(txt), stdin);
    // while (fgets(txt, sizeof(txt), stdin)) {
  //   printf("adsf");
  // }

  memset(fgetstr, '\0', sizeof(fgetstr));
  while ((fgets(fgetstr, sizeof(fgetstr), stdin)) != NULL) {
    result = strtok(fgetstr, ",");
    strcpy(data[count].key, result);
    result = strtok(NULL, ",");
    strcpy(data[count].value, result);
    // printf("\nkey : %s, value : %s\n",data[count].key,data[count].value);
    count += 1;
  }
}
void ROT13CaesarPasswd() {
  int i;
  int move = 13;

  for (i = 0; i < strlen(ciphertext); i++) {
    if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
      ciphertext[i] = ((ciphertext[i] - 'A') + move) % 26 + 'A';
    } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
      ciphertext[i] = ((ciphertext[i] - 'a') + move) % 26 + 'a';
    }
  }
  printf("%s", ciphertext);
}

void ConstructKey() {
  for (int i = 0; i < 5; i++) {
    passwd[i] = ciphertext[i];
  }
  printf("%s\n", passwd);
}
// Fills lps[] for given patttern pat[0..M-1]
void computeLPSArray(char* pat, int M, int* lps) {
  // length of the previous longest prefix suffix
  int len = 0;

  lps[0] = 0;  // lps[0] is always 0

  // the loop calculates lps[i] for i = 1 to M-1
  int i = 1;
  while (i < M) {
    if (pat[i] == pat[len]) {
      len++;
      lps[i] = len;
      i++;
    } else  // (pat[i] != pat[len])
    {
      // This is tricky. Consider the example.
      // AAACAAAA and i = 7. The idea is similar
      // to search step.
      if (len != 0) {
        len = lps[len - 1];

        // Also, note that we do not increment
        // i here
      } else  // if (len == 0)
      {
        lps[i] = 0;
        i++;
      }
    }
  }
  for (int lpsIndex = 0; lpsIndex < strlen(pat); lpsIndex++) {
    sumoflps += lps[lpsIndex];
  }
  printf("%d\n", sumoflps);
}
// Prints occurrences of txt[] in pat[]
void KMPSearch(char* pat, char* txt) {
  int M = strlen(pat);
  int N = strlen(txt);

  // create lps[] that will hold the longest prefix suffix
  // values for pattern
  int lps[M];

  // Preprocess the pattern (calculate lps[] array)
  computeLPSArray(pat, M, lps);

  int i = 0;  // index for txt[]
  int j = 0;  // index for pat[]

  int indexCount = 0;
  while (i < N) {
    if (pat[j] == txt[i]) {
      j++;
      i++;
    }

    if (j == M) {
      //   printf("Found pattern at index %d\n", i - j);
      indexArray[indexCount] = (i - j) + sumoflps;
      j = lps[j - 1];
      indexCount++;
    }
    // mismatch after j matches
    else if (i < N && pat[j] != txt[i]) {
      // Do not match lps[0..lps[j-1]] characters,
      // they will match anyway
      if (j != 0)
        j = lps[j - 1];
      else
        i = i + 1;
    }
  }
}
void FindAnswer() {
  int passwdSize = sizeof(indexArray);
  int dataSize = sizeof(data) / sizeof(Data);

  char finalAnswer[100];
  memset(finalAnswer, '\0', sizeof(finalAnswer));

  for (int i = 0; i < sizeof(indexArray); i++) {
    printf("%d\n", indexArray[i]);
  }

  for (int i = 0; i < dataSize; i++) {
    for (int j = 0; j < passwdSize; j++) {
      int d = data[i].key[0];
      if (d == indexArray[j]) {
        strcat(finalAnswer, data[i].value);
      }
    }
  } 

  for(int index; index< strlen(finalAnswer);index++){
        if(finalAnswer[index] == '\n')
            finalAnswer[index] = ' ';
  }
  printf("%s \n", finalAnswer);  
}
// Driver program to test above function
int main() {
  Read();
  ROT13CaesarPasswd();
  ConstructKey();
  KMPSearch(passwd, txt);
  FindAnswer();
  return 0;
}
