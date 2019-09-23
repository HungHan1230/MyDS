#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char key[10];
  char value[20];
} Data;

int sumoflps;
char indexArray[5];
char txt[300];
char passwd[20];

void ReadData() {  
  char* result = NULL;
  int count = 0;

  // read answer_dic.csv
  FILE *file = fopen("", "r");

  if (!file) {
    fprintf(stderr, "failed to open file answer_dic.csv\n");
  }

  while (fgets(line, 100, file) != NULL) {
    result = strtok(line, ",");
    strcpy(data[count].key, result);

    result = strtok(NULL, ",");
    strcpy(data[count].value, result);
    count += 1;
  }

  fclose(file);

  // read article.txt
  file = fopen("article.txt", "r");
  int countc = 0;
  text = mytext;

  if (file) {
    while (article != EOF) {
      article = fgetc(file);
      if (article != EOF) {
        mytext[countc] = article;
        countc++;
      }
    }
  } else {
    fprintf(stderr, "failed to open file for reading\n");
  }
  fclose(file);

  file = fopen("Ciphertext.txt", "r");
  fscanf(file, "%s", cipher);  
  CipherText = cipher;
  fclose(file);
}

void ROT13CaesarPasswd() {
  int i;
  int move = 13;

  for (i = 0; i < strlen(passwd); i++) {
    if (passwd[i] >= 'A' && passwd[i] <= 'Z') {
      passwd[i] = ((passwd[i] - 'A') + move) % 26 + 'A';
    } else if (passwd[i] >= 'a' && passwd[i] <= 'z') {
      passwd[i] = ((passwd[i] - 'a') + move) % 26 + 'a';
    }
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
  for (int i = 0; i < sizeof(indexArray); i++) {
    printf("%d\n", indexArray[i]);
  }
  for (int i = 0; i < sizeof(indexArray); i++) {
    printf("%c", indexArray[i]);
  }
  printf("\n");
}

// Driver program to test above function
int main() {
  // GodsaidLettherebelightandtherewaslight.AndGodsawthelight,thatitwalilighsgolilighod:andGoddividelilighdthefrolilighmthelilighdkness.Namingthe,Day,andthedark,Night.Andtherewaseveningandtherewasmorning,thefirstday.
  // yvyvtu
  // liligh 

  // yadtsrifeht,gninromsawerehtdnagninevesawerehtdnA.thgiN,kradehtdgalgana,yaDgalga,ehtgnimaN.ssenkdgalgaehtmgalgaorfehtdgalgaedividdoGdna:doogsawtitaht,thgilehtwasdoGdnA.thgilsawerehtdnathgileberehtteLdiasdoGsA
  // tnytn
  // galga

  //   printf("輸入txt：");
  scanf("%s", txt);

  //   printf("輸入pat：");
  scanf("%s", passwd);

  ROT13CaesarPasswd();

  KMPSearch(passwd, txt);

  FindAnswer();
  return 0;
}