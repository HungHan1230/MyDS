#include <stdio.h> 
#include <string.h>

#define MAX 1024 

void computeLPSArray(char* pat, int M, int* lps); 
  
// Prints occurrences of txt[] in pat[] 
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
	        else 
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


void rot13( char * str ) 

    {
        int i = 0;

        /* Do this until  find a '\0' */
        for( i = 0; str[ i ] != '\0' ; i++ ){

            /* Use the pointer notation if passed a pointer. */
            /* If the letter is between a and m ,simply sum it. */
            if( *( str + i ) >= 'a' && *( str + i ) < 'n')
                *( str + i ) += 13;       

            /* If the letter is between the n and z ,do the opposite.*/
            else if( *( str + i ) >= 'n' && *( str + i ) <= 'z')
                *( str + i ) -= 13;
        }
    	printf("%s\n",str);
	}
    
// Driver program to test above function 
int main() 
	{   
		int q;
		char ciphertext[MAX];
	    char txt[255];
	    char pat[5] ;
	

		scanf("%s", ciphertext);
	
		scanf("%s", txt);
	
	//KMP Start   	
    int M = 5;
    int N = strlen(txt); 
    int sumoflps = 0;
  
    // create lps[] that will hold the longest prefix suffix 
    // values for pattern 
    int lps[M];
    int a;
    char temp[100];
	char strs[52][200];
	int n = 52;
	int f;
    
	for (f = 0; f < n; f++)
		{
	    scanf("%s", temp);
	    strcpy(strs[f] , temp+2);
	}

   	rot13(ciphertext);
   	
	printf("%s\n", ciphertext );
	
   	for(q = 0; q < 5; q++) 
	   {
    	pat[q]=ciphertext[q];
  	}
	printf("%s\n", pat );
	
    
    // Preprocess the pattern (calculate lps[] array) 
    computeLPSArray(pat, M, lps); 
  
    int i = 0; // index for txt[] 
    int j = 0; // index for pat[] 
    char str1[40];
	
    for (a =0; a<M;a++){
        sumoflps+=lps[a];
        
    }
    printf("%d\n", sumoflps); 
    while (i < N) { 
        if (pat[j] == txt[i]) { 
            j++; 
            i++; 
        } 
  
        if (j == M) { 
           
			printf("%d\n", i - j + sumoflps ); 
			strcat(str1, strs[i - j + sumoflps-65]);
			strcat(str1, " ");
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
    
	printf("%s\n",str1);

	return 0;  
} 