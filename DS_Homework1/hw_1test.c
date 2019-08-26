#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[10];
    char value[20];
} Data;

#define MAX_LINE_SIZE 20

FILE* file;
char passwd[100];
char article;
char* text;
char mytext[400];
char* CipherText;
char* key;
char keyarray[5];
Data data[52];
int indexArray[3];
int sumoflps;

void ReadData();
void CaesarPasswd();
void computeLPSArray(char* pat, int M, int* lps);
void KMPSearch(char* pat, char* txt);
void findAnswer();

int main() {
    //int num = 0, flag = 1;
    CipherText =
        "rnernvfgurguveqcynargsebzgurFhanaqgurbaylnfgebabzvpnybowrpgxabjagbuneo"
        "beyvsr";
    printf("Here's the ciphertext : %s \n", CipherText);
    
    //Read article.txt and answer_dic.csv from disk.
    ReadData();
    printf("\n");

    //Using ROT13 algorithm to find out the password from CipherText.
    CaesarPasswd();
    printf("\n");
    
    //KMP algorithm implementation    
    printf("KMP searching...\n");
    printf("pattern: %s \n", key);
    printf("text: %s \n\n", text);
    KMPSearch(key, text);    
}

void ReadData() {
    char file_name[] = "answer_dic.csv";
    char line[MAX_LINE_SIZE];
    char* result = NULL;
    int count = 0;

    file = fopen(file_name, "r");

    if (!file) {
        fprintf(stderr, "failed to open file answer_dic.csv\n");
    }

    while (fgets(line, MAX_LINE_SIZE, file) != NULL) {
        result = strtok(line, ",");
        // printf("!!!!!!!!!!!%s\n", result);
        strcpy(data[count].key, result);
        // printf("%d", sizeof(data[count].key));

        // printf("%s \n", result);

        result = strtok(NULL, ",");
        // printf("!!!!!!!!!!!%s\n", result);
        strcpy(data[count].value, result);

        // printf("key: %s , count:%d\n", data[count].key, count);
        // printf("value: %s \n", data[count].value);

        count += 1;
        // break;
        // printf("%s \n", result);
    }
    // printf("value:%s",data[0].value);
    fclose(file);

    // printf("size of data[]: %d\n", sizeof(data) / sizeof(Data));
    // printf("data[0].key: %s\n", data[0].key);
    // printf("data[0].value: %s\n", data[0].value);

    file = fopen("article.txt", "r");
    int countc = 0;

    text = mytext;

    if (file) {
        while (article != EOF) {
            article = fgetc(file);
            if (article != EOF) {
                // printf("count: %d \n", countc);
                // printf("%c", article);
                mytext[countc] = article;
                countc++;
            }
        }
    } else {
        fprintf(stderr, "failed to open file for reading\n");
    }
    fclose(file);
    printf("\narticle:\n %s \n", text);
    // strncpy(txt, article, 360);
}

void CaesarPasswd() {
    int i, j, k, t;
    int move = 13;
    memset(passwd, '\0', sizeof(passwd));

    strncpy(passwd, CipherText, 76);

    // printf("\nsize of CipherText %d\n", strlen(CipherText));
    // printf("\nsize of passwd %d\n", strlen(passwd));

    for (i = 0; i < strlen(passwd); i++) {
        if (passwd[i] >= 'A' && passwd[i] <= 'Z') {
            passwd[i] = ((passwd[i] - 'A') + move) % 26 + 'A';
        } else if (passwd[i] >= 'a' && passwd[i] <= 'z') {
            passwd[i] = ((passwd[i] - 'a') + move) % 26 + 'a';
        }
    }
    printf("Your passwd: %s\n", passwd);

    key = keyarray;

    for (int index = 0; index < 5; index++) {
        *(key + index) = passwd[index];
        // printf("test: %c\n", *(key + index));
    }
    printf("Your key: %s\n", key);

    // printf("Enter message to be encrypted:");
    // scanf("%s", passwd);
    // printf("\nEnter shift amount(1-25):");
    // scanf("%d%*c", &move);
}

// Prints occurrences of txt[] in pat[]
void KMPSearch(char* pat, char* txt) {
    int M = strlen(pat);
    int N = strlen(txt);
    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    // int lps[M];
    int* lps = (int*)malloc(M * sizeof(int));
    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);    
    int i = 0;  // index for txt[]
    int j = 0;  // index for pat[]

    //print lps elements and the sum of lps array
    printf("The elements of the lps array:\n");
    int lpsIndex = strlen(pat);
    sumoflps = 0;
    for(int lpsI = 0; lpsI < lpsIndex; lpsI++){
        printf("element%d : %d\n",lpsI+1,lps[lpsI]);
        sumoflps += lps[lpsI];
    }

    printf("The sum of lps array is: %d \n", sumoflps);



    int indexCount = 0;  // index for indexarray
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            printf("Found %s at position %d \n",pat, i - j);

            indexArray[indexCount] = i - j + sumoflps;

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
    findAnswer();
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
        } else {  // (pat[i] != pat[len])
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0) {
                len = lps[len - 1];
                // Also, note that we do not increment
                // i here
            } else {  // if (len == 0)
                lps[i] = 0;
                i++;
            }
        }
    }
}
void findAnswer() {
    int indexSize = sizeof(indexArray) / sizeof(int);
    int dataSize = sizeof(data) / sizeof(Data);    

    char finalAnswer[100];

    memset(finalAnswer, '\0', sizeof(finalAnswer));

    printf("The key of the index array is: \n");
    for(int indexarrayI = 0; indexarrayI < 3; indexarrayI++){
        printf("key%d : %d\n",indexarrayI, indexArray[indexarrayI]);
    }    

    printf("\nThe final answer is: ");

    for (int i = 0; i < dataSize; i++) {
        for (int j = 0; j < indexSize; j++) {
            int d = data[i].key[0];
            if (d == indexArray[j]) {
                strcat(finalAnswer,data[i].value);
            }
        }
    }
    for(int index; index< strlen(finalAnswer);index++){
        if(finalAnswer[index] == '\n')
            finalAnswer[index] = ' ';
    }
    printf("\n");
    printf("%s \n",finalAnswer);
}