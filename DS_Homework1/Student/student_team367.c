#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct{
	char key;
	char sent[100];
}Key;

void result(Key*,int*,int,int);
void decrypt(char*,char*);
int preprocess(char*,int*);
int kmpmatch (char*,char*,int*);


int main(){
	char ciphertxt[256];
	char article[1024];
	char pattern[6];
	char tmp[100];
	char *ptr=NULL;
	int location[20];
	int lps[5];
	int sum,tmpl=0;
	int idx=0,cnt=0,lenS;
	Key dic[52];

	scanf("%s",ciphertxt);
	decrypt(ciphertxt,pattern);
	sum=preprocess(pattern,lps);
	printf("%s\n%s\n%d\n",ciphertxt,pattern,sum);

	while(getchar()!='\n')continue;
	fgets(article,1024,stdin);

	while(fgets(tmp,100,stdin)!=NULL){
		lenS=strlen(tmp);
		if(tmp[lenS-1]=='\n')tmp[lenS-1]='\0';
		dic[idx].key=tmp[0];
		strcpy(dic[idx++].sent,tmp+2);
	}

	ptr=article;
	while((tmpl=kmpmatch(ptr,pattern,lps))!=-1){
		ptr+=tmpl+1;
		if(cnt==0)location[cnt]=tmpl;
		else location[cnt]=location[cnt-1]+tmpl+1;
		printf("%d\n",location[cnt]+sum);
		cnt++;
	}

	result(dic,location,cnt,sum);
	
	return 0;
}

void decrypt(char* ciphertxt,char* pattern){
	int len=strlen(ciphertxt);
	int mov;
	for(int i=0;i<len;i++){
		if(ciphertxt[i]>96){
			mov=(ciphertxt[i]-'a'+13)%26;
			ciphertxt[i]='a'+mov;
		}else{
			mov=(ciphertxt[i]-'A'+13)%26;
			ciphertxt[i]='A'+mov;
		}
	}
	strncpy(pattern,ciphertxt,5);
	pattern[5]='\0';
}

int preprocess(char* pattern,int* lps){
	int i=1,j=0,sum=0;	//int len=strlen(pattern);
	lps[0]=0;
	while(i!=5){	//len
		if(pattern[j]==pattern[i]){
			lps[i]=j+1;
			sum+=lps[i];
			i++;j++;
		}
		else{
			if(j==0){
				lps[i++]=0;
			}
			else{
				j=lps[j-1];
			}
		}
	}
	return sum;
}

int kmpmatch (char* string,char* pat,int* lps){
	int i=0,j=0;
	int lens=strlen(string);
	int lenp=strlen(pat);
	while(i<lens&&j<lenp){
		if(string[i]==pat[j]){
			i++;j++;
		}
		else if(j==0)i++;
		else j=lps[j-1];
	}
	return ((j==lenp)?(i-lenp):-1);
}

void result(Key* dic,int* location,int cnt,int sum){
	int tmp;
	for(int i=0;i<cnt;i++){
		if(location[i]<=90)
			tmp=location[i]-64-1+sum;
		else
			tmp=26+location[i]-97+sum;
		printf("%s",dic[tmp].sent);
		if(i!=cnt-1)printf(" ");
	}
}
