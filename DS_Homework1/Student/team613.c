#include <stdio.h>
#include <string.h>
#define maxrot 900000
#define maxsource 900000
#define MaxLine 900000

struct dic {
  char keys;
  char* value;
};

void rmNewLine(char* line) {
  int i = 0;
  while (line[i] != '\0' && line[i] != '\n') {
    i++;
  }
  line[i] = '\0';
}
void fail(char* pat, int failure[]) {
  int n = strlen(pat);
  failure[0] = -1;
  int i, j;
  for (j = 1; j < n; j++) {
    i = failure[j - 1];
    while ((pat[j] != pat[i + 1]) && (i >= 0)) {
      i = failure[i];
    }
    if (pat[j] == pat[i + 1]) {
      failure[j] = i + 1;
    } else {
      failure[j] = -1;
    }
  }
}
int pmatch(char* string, char* pat, int failure[], int index) {
  int i = index;
  int j = 0;
  int lens = strlen(string);
  int lenp = strlen(pat);
  while (i < lens && j < lenp) {
    if (string[i] == pat[j]) {
      i++;
      j++;
    } else if (j == 0) {
      i++;
    } else {
      j = failure[j - 1] + 1;
    }
  }
  return j == lenp ? (i - lenp) : -1;
}

int main() {
  char rot[maxrot];
  int i;
  fgets(rot, maxrot, stdin);
  rmNewLine(rot);
  for (i = 0; i < strlen(rot); i++) {
    int roti = rot[i];
    if (roti <= 90 && roti >= 65) {
      roti = (((rot[i] % 65) + 13) % 26) + 65;
      rot[i] = roti;
    } else {
      roti = (((rot[i] % 97) + 13) % 26) + 97;
      rot[i] = roti;
    }
  }
  printf("%s\n", rot);
  char cypher[6];
  strncpy(cypher, rot, 5);
  printf("%s\n", cypher);
  int failure[5];
  fail(cypher, failure);
  int key = 5;
  for (i = 0; i < 5; i++) {
    key += failure[i];
  }
  printf("%d\n", key);
  int sum[50000];
  int isum=0;
  char source[maxsource];
  int index=0;
  char line[MaxLine];
  fgets(source,maxsource,stdin);
  rmNewLine(source);
  index=pmatch(source,cypher,failure,index);
  if(index==-1){
  	return 0;
  }
  printf("%d\n",index+key);
  sum[isum]=index+key;
  isum++;
  while(index<strlen(source)){
  	index+=5;
  	index=pmatch(source,cypher,failure,index);
  	if(index==-1){
  		break;
  	}
  	printf("%d\n",index+key);
  	sum[isum]=index+key;
  	isum++;
  }
  struct dic alpha[52];
  int indexa=0;
  while(fgets(line,MaxLine,stdin)){
  	rmNewLine(line);
  	char *ptr=line;
  	alpha[indexa].keys=*ptr;
  	alpha[indexa].value=strdup(line+2);
  	indexa++;
  }
  for(i=0;i<isum;i++){
  	if(sum[i]<=90&&sum[i]>=65){
  		printf("%s ",alpha[sum[i]-65].value);
  	}
  	else if(sum[i]<=122&&sum[i]>=97){
  		printf("%s ",alpha[sum[i]-97+26].value);
  	}
  }
  printf("\n");
  return 0;
}
