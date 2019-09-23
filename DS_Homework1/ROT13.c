#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ROT13CaesarPasswd(char passwd[100]) {
  int i;  
  int move = 13; 

  for (i = 0; i < strlen(passwd); i++) {
    if (passwd[i] >= 'A' && passwd[i] <= 'Z') {
      passwd[i] = ((passwd[i] - 'A') + move) % 26 + 'A';
    } else if (passwd[i] >= 'a' && passwd[i] <= 'z') {
      passwd[i] = ((passwd[i] - 'a') + move) % 26 + 'a';
    }
  }

  printf("%s\n",passwd);
}
int main(){
    // char passwd[100] = "rnern\n";
    char passwd[100] = "liligh";
    ROT13CaesarPasswd(passwd);
    return 0;
}