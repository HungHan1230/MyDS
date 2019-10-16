/*****************************************************************
*
* Assignment 1 - Struct and Array
*
*   Purpose: This program implements the ROT13 algorithm to find the key
*	by decrypting a given secret string and the KMP
*	algorithm to search the matched words with the key and find all the positions of
*	the matched words in the given article. 
*
* 	Limitation: This program does not handle more than 52
*   answer_dic properly. 
*
*   Written by Lam Chin Wai
*   On 14/10/2019
*   For CCU Data Structure Course 
* 
*   Version 1
*  
*****************************************************************/

#include <stdio.h> 
#include <string.h>
#define BUFFERSIZE 1024
void computeLPSArray(char* pat, int M, int* lps); 
  
// Prints occurrences of txt[] in pat[] ,Start KMP Search
void KMPSearch(char* pat, char* txt, char* ciphertext1,char* txt1)   
{ 
    char str[60][200];     //Store answer_dic
    char str1[500];		   //Secret message printout
 	char str2[500];		  //Temp Secret message
	int i =0;			  //for loop i	
	
	for (i=0;i<52;i++){		//read 52 line answer_dic
   		fgets(str[i], 200, stdin);    //store readline to str   
	}
	
   	printf("%s",ciphertext1);    //Printout ROT13 Ciphertext
   	printf("%s\n", txt1 );		//Printout First 5 characters of ciphertext
   	
	int M = strlen(pat); 		//Length of 5 characters of ciphertext
    int N = strlen(txt); 		//Length of Ciphertext
    int sumoflps = 0;			//Default Sum of LPS is 0
  
    // create lps[] that will hold the longest prefix suffix 
    // values for pattern 
    int lps[M]; 
  
    // Preprocess the pattern (calculate lps[] array) 
    computeLPSArray(pat, M, lps); 
  
    i = 0; // index for txt[] 
    int j = 0; // index for pat[] 
    
    //Calculate Sum of LPS and Print
    for (j =0; j<M;j++){
        sumoflps+=lps[j];
    }
    printf("%d\n", sumoflps); 
    
    i = 0; // index for txt[] 
    j = 0; // index for pat[] 
    while (i < N) { 
        if (pat[j] == txt[i]) { 
            j++; 
            i++; 
        } 
  
        if (j == M) { 
            printf("%d\n", i - j+sumoflps); 	//Print the indexes
            if(i-j+sumoflps<=90){				
			strcpy(str2,str[i-j+sumoflps-65]+2);		
  			strcat(str1,str2);
		}
		else if (i-j+sumoflps<=123){
			strcpy(str2,str[i-j+sumoflps-71]+2);
  			strcat(str1,str2);
		}
            j = lps[j - 1]; 
    } 
  
        // mismatch after j matches 
        else if (i < N && pat[j] != txt[i]) { 
            if (j != 0) 
                j = lps[j - 1]; 
            else
                i = i + 1; 
        } 
    }  
	   
    size_t length, c;

     length = strlen(str1);
	
	 //Trim the newline symbol 
     for(c = 0; c < length; ++c)
     {
          if(str1[c] == '\n')
          {
               str1[c] = ' ';
          }    
     }
	 str1[strlen(str1)-1] = 0;   //Delete last character
     printf("%s", str1);    
} 
  
// Fills lps[] for given patttern pat[0..M-1] 
void computeLPSArray(char* pat, int M, int* lps) 
{ 
    // length of the previous longest prefix suffix 
    int len = 0; 
  
    lps[0] = 0; // lps[0] is always 0 
  
    // the loop calculates lps[i] for i = 1 to M-1 
    int i = 1; 
    while (i < M) { 
        if (pat[i] == pat[len]) { 
            len++; 
            lps[i] = len; 
            i++; 
            
        } 
        else // (pat[i] != pat[len]) 
        { 
            if (len != 0) { 
                len = lps[len - 1]; 
              } 
            else // if (len == 0) 
            { 
                lps[i] = 0; 
                i++;                 
            }             
       } 
    } 
} 

//Start ROT13 
void rot13 (char *s) {
    if (s == NULL)
        return;

    int i;
    for (i = 0; s[i]; i++) {
        if (s[i] >= 'a' && s[i] <= 'm') { s[i] += 13; continue; }
        if (s[i] >= 'A' && s[i] <= 'M') { s[i] += 13; continue; }
        if (s[i] >= 'n' && s[i] <= 'z') { s[i] -= 13; continue; }
        if (s[i] >= 'N' && s[i] <= 'Z') { s[i] -= 13; continue; }
    }
}
  
// Driver program to test above function 
int main() 
{ 
    int q;
    char ciphertext[1024];
	char txt[1024];
	char pat[5] ;
	fgets(ciphertext, BUFFERSIZE , stdin);
	fgets(txt, BUFFERSIZE , stdin);
	
	rot13(ciphertext);
	
	for(q = 0; q < 5; q++) 
	{
    	pat[q]=ciphertext[q];
  	}
	
    KMPSearch(pat, txt,ciphertext,pat); 
    return 0; 
} 
