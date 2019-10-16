#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1001

void makelps(int lps[], char name[]) {  //�аO�̪����ۦP�e���
  int i = 1, j = 1, k = 1;
  char current[100], tmp[100], *ptr;
  lps[0] = 0;
  for (i = 2; i <= strlen(name); i++) {
    if (i < strlen(name)) {
      strncpy(current, name, i);
      current[i] = '\0';
    } else {
      strcpy(current, name);
    }
    for (j = 1; j < strlen(current); j++) {
      strncpy(tmp, current, strlen(current) - j);
      tmp[strlen(current) - j] = '\0';
      ptr = current + j;
      if (strcmp(tmp, ptr) == 0) {  //���׼аO
        lps[k] = strlen(ptr);
        k++;
        break;
      }
      if (j == strlen(current) - 1) {  //���s�}�l
        lps[k] = 0;
        k++;
      }
    }
  }
}
int main() {
  char ansline[MAX_LINE][MAX_LINE];  // ans
  char cline[100];                   // ciphertext
  char aline[MAX_LINE];              // article
  // char filename[MAX_LINE];
  char targetline[6];
  char keyindex, tmpline[MAX_LINE];
  int failure[5];  // failure2[5];
  int record[MAX_LINE];
  int i = -1, j = 0, n = 0, key, sum = 0;

  int lps[MAX_LINE];
  // FILE *fp;
  // scanf("%s",filename);//Ū�ɦW
  // fp = (fopen(filename,"r"));
  // if(fp==NULL){
  //    printf("No such file\n");
  //    return 0;;//�}�ɽT�{
  //}
  fgets(cline, MAX_LINE, stdin);
  // printf("my %s",cline);
  fgets(aline, MAX_LINE, stdin);
  // printf("%s",aline);
  while (ansline[i][0] != 'z') {
    // printf("%s",ansline[i++]);
    i++;
    fgets(ansline[i], MAX_LINE, stdin);
    // i++;
  }
  // printf("%s",ansline[i]);
  // printf("\nOrigin: %s",cline);
  for (i = 0; i < strlen(cline) - 1; i++) {
    key = ((cline[i] - 'a') + 13) % 26;
    cline[i] = 'a' + key;
  }
  
//   int move = 13;

//   for (int i = 0; i < strlen(cline); i++) {
//     if (cline[i] >= 'A' && cline[i] <= 'Z') {
//       cline[i] = ((cline[i] - 'A') + move) % 26 + 'A';
//     } else if (cline[i] >= 'a' && cline[i] <= 'z') {
//       cline[i] = ((cline[i] - 'a') + move) % 26 + 'a';
//     }
//   }
  printf("%s", cline);
  strncpy(targetline, cline, 5);
  printf("%s\n", targetline);
  // system("pause");
  //
  n = strlen(targetline);
  failure[0] = -1;
  i = 0;
  j = 0;
  for (j = 1; j < n; j++) {
    i = failure[j - 1];
    while ((targetline[j] != targetline[i + 1]) && (i >= 0)) {
      i = failure[i];
    }
    if (targetline[j] == targetline[i + 1]) {
      failure[j] = i + 1;
    } else
      failure[j] = -1;
  }
  /*for(i=0;i<5;i++){
      failure2[i]=failure[i]+1;
      //printf("%d",failure2[i]);
      sum+=failure2[i];
  }
  printf("%d\n",sum);*/
  makelps(lps, targetline);
  for (i = 0; i < 5; i++) {
    sum += lps[i];
    // printf("lps:%d\n",lps[i]);
  }
  printf("%d\n", sum);
  //
  i = 0;
  j = 0;
  n = 0;
  while (i < strlen(aline) && j < strlen(targetline)) {
    if (aline[i] == targetline[j]) {
      i++;
      j++;
      // printf("1\n");
    } else if (j == 0) {
      i++;
    } else {
      // printf("2\n");
      j = lps[j - 1];
      // printf("3\n");
    }
    if (j == strlen(targetline)) {
      record[n++] = i - j;
      // printf("ans:%d\n",record[n-1]);
      i = i - 4;
      j = 0;
      continue;
    }
  }
  /*
  while(i<strlen(aline) && j<strlen(targetline)){
      if(aline[i] ==targetline[j]){
          i++;
          j++;
      }
      else if(j==0){
          i++;
      }
      else{
          j = failure[j-1]+1;
      }
      if( j == strlen(targetline) ){
          record[n++]=i-j;
          //printf("ans:%d\n",record[n-1]);
          j=0;
          continue;
      }
  }
  */
  // printf("xx:%d\n",n);
  i = 0;
  for (i = 0; i < n; i++) {
    record[i] = record[i] + sum;
    printf("%d\n", record[i]);
  }
  for (i = 0; i < n;) {
    // record[i]=record[i]+sum;
    if (i > 0)
      printf(" ");
    // printf("%d\n",record[i]);
    do {
      keyindex = record[i++];
    } while (keyindex <= 'a' && 'z' <= keyindex);
    j = 0;
    while (keyindex != ansline[j][0] && j < 52) {
      j++;
    }
    if (j < 52) {
      strcpy(tmpline, ansline[j]);
      j = strlen(tmpline);
      tmpline[j - 1] = '\0';
      for (j = 0; j < strlen(tmpline); j++) {
        tmpline[j] = tmpline[j + 1];
      }
      for (j = 0; j < strlen(tmpline); j++) {
        tmpline[j] = tmpline[j + 1];
      }
      printf("%s", tmpline);
    }
  }
  // printf(" ");
  //

  // fclose(fp);
  return 0;
}
