#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 52
#define SIZE 100
#define a_ascii 97
#define A_ascii 65
#define rot 13
#define Bsize 100000
struct dic {
  char key;
  char s[size];
};
int ff(char p[], int fal[]) {
  printf("enter ff function...\n");

  int sum = 0, largest, i, lenth;
  lenth = strlen(p);
  for (i = 5; i > 0; i--)
    p[i] = p[i - 1];
  fal[0] = 0;
  largest = 0;
  for (i = 2; i <= lenth; i++) {
    while (largest > 0 && p[largest + 1] != p[i])
      largest = fal[largest];
    if (p[largest + 1] == p[i])
      largest++;
    fal[i] = largest;
    sum += p[i];
  }

  return sum;
}
int kmp(char p[], char a[], int fal[]) {
  printf("kmp executing...\n");

  int i = 1, j = 0, la, lp;
  la = strlen(a);
  lp = strlen(p);
  while (i < la && j < lp) {
    if (a[i] == p[j]) {
      i++;
      j++;
    } else if (j == 0)
      j++;
    else
      j = fal[j - 1] + 1;
  }
  return ((j == lp) ? (i - lp) : (-1));
}
int main() {
  int i, j = 0, len_c, r, fal[size], sum;
  char *p, cip[Bsize], article[Bsize],
      AB[size] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ\0",
      ab[size] = "abcdefghijklmnopqrstuvwxyz\0";
  struct dic ans[SIZE];
  freopen("hw1.txt", "r", stdin);
  p = fgets(cip, Bsize, stdin);
  printf("cip %s\n", cip);
  p = fgets(article, Bsize, stdin);
  for (i = 0; i < size; i++) {
    scanf("\n%c,", &ans[i].key);
    p = fgets(ans[i].s, SIZE, stdin);
    printf("read %d : %c, %s\n", i, ans[i].key, p);
  }
  printf("ans.key : %c, ans.value : %s\n", ans[50].key, ans[50].s);

  // there's no close function for file stream
//   fclose(stdin);

  len_c = strlen(cip);
  for (i = 0; i < len_c; i++) {
    if ((cip[i] - 'A') < 26) {
      r = ((cip[i] - 'A') + rot) % 26;
      cip[i] = AB[r];
    } else {
      r = ((cip[i] - 'a') + rot) % 26;
      cip[i] = ab[r];
    }
  }
  printf("cip2 %s\n", cip);
  // cip[6] is the 7 posistion. so here you should set up the cip[5].
  cip[5] = '\0';
  printf("cip[5] %s\n", cip);
  sum = ff(cip, fal);
  printf("fal[4]:%d\n",fal[4]);

  printf("sum %d\n", sum);
  printf("enter while loop...\n");
  while (j >= 0) {
    if (j)
      j += 3;
    if ((j - A_ascii) < 26)
      printf("%s\n", ans[j - A_ascii].s);
    else
      printf("%s\n", ans[j - a_ascii + 26].s);
    printf("j-A_ascii %c\n", (j - A_ascii));
    j = kmp(cip, article + j, fal);
    if (j != -1)
      printf("%d\n", j + 3);
  }
  return 0;
}
