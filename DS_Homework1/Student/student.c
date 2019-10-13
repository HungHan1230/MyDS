#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int failure_table(char pattern[], int failure[]) {
  failure[0] = 0;
  int n = strlen(pattern);
  int i = 1, len = 0, sum = 0;
  while (i < n) {
    if (pattern[i] == pattern[len]) {  //���\�ǰt
      len++;
      failure[i++] = len;
    } else if (len > 0) {  //�ǰt���Ѧ�����>0�A���s�i�J�^��H�s�������~���
      len = failure[len - 1];
    } else {
      failure[i++] = 0;
    }
  }
  for (int i = 0; i < n; i++) {  // sum of prefix
    sum += failure[i];
  }
  for (i = n - 1; i > 0;
       i--) {  //�������Ჾ�@��A�Ĥ@��]�w��-1
    failure[i] = failure[i - 1];
  }
  failure[0] = -1;

  return sum;
}
int KMP(char s[], char pattern[], int match_table[]) {
  int lens = strlen(s), lenp = strlen(pattern);
  int i = 0, j = 0;
  int failure[lenp];
  int num_match = 0;
  failure_table(pattern, failure);
  while (i < lens && j < lenp) {
    if (j == lenp - 1 && pattern[j] == s[i]) {  //�P�_�O�_match
      match_table[num_match++] = i - j;
      j = failure[j];
    }
    if (s[i] == pattern[j]) {
      i++;
      j++;
    } 
    else
      j = failure[j];
    if (j == -1) {
      j = 0;
      i++;
    }
  }
  return num_match;
}
void ROT13(char ciphertext[], char pattern[]) {
  for (int i = 0; i < strlen(ciphertext); i++) {
    if ((ciphertext[i] >= 65 && ciphertext[i] <= 77) ||
        (ciphertext[i] >= 97 && ciphertext[i] <= 109))
      ciphertext[i] += 13;
    else if ((ciphertext[i] >= 78 && ciphertext[i] <= 90) ||
             (ciphertext[i] >= 110 && ciphertext[i] <= 122))
      ciphertext[i] -= 13;
    printf("%c", ciphertext[i]);  //�L�X�ѽX�᪺ciphertext
  }
  for (int i = 0; i < 5; i++) {
    pattern[i] = ciphertext[i];
    printf("%c", pattern[i]);  //�L�Xpattern
  }
  printf("\n");
}
int main() {
  struct dic {
    char key[52];
    char value[52][500];
  } d;
  char s[1000000], pattern[6], ciphertext[100000];
  int match_table[100000], failure[6], num_match = 0, sum = 0;
  fgets(ciphertext, 100000, stdin);  //Ū�J���
  fgets(s, 1000000, stdin);
  for (int i = 0; i < 52; i++) {
    scanf("%c,", &d.key[i]);
    scanf("%[^\n]", d.value[i]);
    getchar();
  }
  ROT13(ciphertext, pattern);             //����ROT13
  sum = failure_table(pattern, failure);  //�p��sum
  printf("%d\n", sum);
  num_match = KMP(s, pattern, match_table);  //����KMP
  for (int i = 0; i < num_match; i++) {
    match_table[i] += sum;
    printf("%d\n", match_table[i]);  //��match��index�[�Wsum�æL�X
  }
  for (int i = 0; i < num_match; i++) {  // search the table by key
    for (int j = 0; j < 52; j++) {
      if (match_table[i] == d.key[j]) {
        printf("%s ", d.value[j]);
        break;
      }
    }
  }
  printf("\n");
  return 0;
}
