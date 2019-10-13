#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define false 0
#define  true 1
char Rot13(char c)
{
    if(c>='A'&&c<='Z')
    {
        c = (c+13 - 'A')%26 +'A';
        return c;
    }else if(c>='a'&&c<='z')
    {
        c = (c+13-'a')%26+'a';
        return c;
    }else{
        return '\0';
    }
}
void LPS(char pattern[],int prefix[],int len)
{
    prefix[0] = 0;
    int now=1,prefix_count = 0;
    while(now<len)
    {
        if(pattern[now] == pattern[prefix_count])
        {   prefix_count ++;
            prefix[now] = prefix_count;
            now++;
        }else
        {
            if(prefix_count != 0)
            {
                prefix_count = prefix[prefix_count-1];

            }else
            {
                 prefix[now] = prefix_count;
                now ++;
            }
        }
    }
}
void move_prefix(int prefix[],int len)
{

    for( ;len>0;len--)
    {
        prefix[len] = prefix[len-1];
    }
    prefix[0] = -1;

}
int main()
{   int len,i =0; int time = false;
    char store[500];
    char *pattern = malloc (sizeof(char)*5);
    int prefix[5];
    //fgets(store,100,stdin); len = strlen(store);
    int j=0;
    int total_len=0;
    int locate[10]; int loc = 0;
    int LPS_total =0;
    char  *ptr,print[400]; int sign_print=0;
    while((fgets(store,200,stdin))!=NULL)
    {       //for recomparing at new line
        len = strlen(store);
         //printf("%d    %d   %s\n",i,len,store);
          //  printf("%d\n",time);
       if(time ==false)
        {
            for(i=0;i<len;i++) // answer1
            {
                store[i] = Rot13(store[i]);
                printf("%c",store[i]);
            }
            puts("");
            for(i=0;i<5;i++)
            {
                    pattern[i] = store[i];
            }
            printf("%s \n",pattern); //**answer2

            LPS(pattern,prefix ,5);
            for(i=0;i<5;i++) LPS_total +=prefix[i];
            printf("%d \n",LPS_total);//**answer3
            move_prefix(prefix,5); //�o��|����
           /* for(i=0;i<5;i++)
            {
                printf("%d\n",prefix[i]);
            }*/
        }
        if(time == true)
        {    i=0;

            while(i<len)
            {   //printf("i<len !!!!!!!!!!!!!!!!!!!!!!!!!!");
                if(store[i] == pattern[j])
                {   // printf("%s \n%s\n ",store,pattern);
                    i++; j++;  //�r�@�˳����e�@��
                }
                if(j==5)
                {
                    locate[loc] = i-j+LPS_total +total_len;    //store index to the code array
                    printf("%d\n", locate[loc]); //print the founded index **answer 4
                    loc++;
                    j = prefix[j-1];
                }
               else if(i<len &&store[i]!=pattern[j])
                {
                    if(j!=0)
                    {
                        //printf("%c%d%d\n",store[i],i,j);
                        j = prefix[j-1];
                        if(j==-1)j++;

                    }else{
                       //printf("i++\n");
                        i++;
                    }
                }
            }
              total_len +=len;
         if(store[1]==','&&store[0]>='A'&&store[0]<='z')
            {
            for(i=0;i<loc;i++)
            {
                if(store[0]==locate[i])
                {
                     ptr = store+2;
                     ptr[strlen(ptr)-1] = ' ';
                     strcat(print,ptr);
                     sign_print++;
                    //printf("12 %s",print);
                }
                 else if(sign_print == loc&& print!=NULL)
                    {
                        print[strlen(print)-1] = '\0';
                        printf("%s\n",print);
                        return 0;
                    }
            }
        }
     }  //else end
       time = true;

     memset(store,'\0',500);
    }
    print[strlen(print)-1] = '\0';
    printf("%s\n",print);
}

