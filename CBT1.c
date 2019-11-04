#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct {
  int row;
  int col;
  int value;
} sparseMatrix;

void fastTranspose(sparseMatrix*, sparseMatrix*);
void mult(sparseMatrix*, sparseMatrix*, sparseMatrix*);

int main() {
  /* declare*/
  int i, j, k, tempInput;
  sparseMatrix A[MAX];
  sparseMatrix B[MAX];
  sparseMatrix R[MAX];
  /* input*/
  scanf("%d", &tempInput);
  A[0].row = tempInput;
  scanf("%d", &tempInput);
  A[0].col = tempInput;
  k = 1;
  for (i = 0; i < A[0].row; i++) {
    for (j = 0; j < A[0].col; j++) {
      scanf("%d", &tempInput);
      if (tempInput != 0) {
        A[k].row = i;
        A[k].col = j;
        A[k].value = tempInput;
        k++;
      }
    }
  }
  A[0].value = k - 1;

  scanf("%d", &tempInput);
  B[0].row = tempInput;
  scanf("%d", &tempInput);
  B[0].col = tempInput;
  k = 1;
  for (i = 0; i < B[0].row; i++) {
    for (j = 0; j < B[0].col; j++) {
      scanf("%d", &tempInput);
      if (tempInput != 0) {
        B[k].row = i;
        B[k].col = j;
        B[k].value = tempInput;
        k++;
      }
    }
  }
  B[0].value = k - 1;
  printf("Starting position for each column of B:\n");
  mult(A, B, R);
  /* output*/
  printf("A * B:\n");
  for (i = 0; i < R[0].value + 1; i++) {
    printf("%d ", R[i].row);
    printf("%d ", R[i].col);
    printf("%d", R[i].value);
    printf("\n");
  }
  return 0;
}

void mult(sparseMatrix* inputA, sparseMatrix* inputB, sparseMatrix* output) {
  int i, j, k, aRowNo, bColNo, iStart, sum, totalA, totalB;
  sparseMatrix bTrans[MAX];
  totalA = inputA[0].value;
  totalB = inputB[0].value;
  fastTranspose(inputB, bTrans);
  k = 1;
  i = 1;
  aRowNo = inputA[i].row;
  while (i <= totalA) {
    iStart = i;
    j = 1;
    while (j <= totalB) {
      aRowNo = inputA[i].row;
      bColNo = bTrans[j].row;
      sum = 0;

      while (i <= totalA && j <= totalB && aRowNo == inputA[i].row &&
             bColNo == bTrans[j].row) {
        if (inputA[i].col == bTrans[j].col) {
          sum = sum + inputA[i].value * bTrans[j].value;
          i++;
          j++;
        } else if (inputA[i].col < bTrans[j].col)
          i++;
        else
          j++;
      }
      if (sum != 0) {
        output[k].row = aRowNo;
        output[k].col = bColNo;
        output[k].value = sum;
        k++;
      }
      if (j <= totalB)
        i = iStart;
      while (bColNo == bTrans[j].row && j <= totalB)
        j++;
    }
    while (aRowNo == inputA[i].row && i <= totalA)
      i++;
  }
  output[0].row = inputA[0].row;
  output[0].col = bTrans[0].row;
  output[0].value = k - 1;
}

void fastTranspose(sparseMatrix* b, sparseMatrix* bT) {
  int i, j;
  int rowTerms[b[0].col];
  int startPos[b[0].col];
  for (i = 0; i < b[0].col; i++) {
    rowTerms[i] = 0;
    startPos[i] = 0;
  }
  for (i = 0; i < b[0].value + 1; i++) {
    rowTerms[b[i].col] = rowTerms[b[i].col] + 1;
  }
  startPos[0] = 1;
  for (i = 1; i < b[0].col; i++) {
    startPos[i] = startPos[i - 1] + rowTerms[i - 1];
  }
  for (i = 0; i < b[0].col; i++) {
    printf("%d ", startPos[i]);
  }
  printf("\n");
  bT[0].row = b[0].col;
  bT[0].col = b[0].row;
  bT[0].value = b[0].value;
  for (i = 1; i < b[0].value + 1; i++) {
    j = startPos[b[i].col];
    startPos[b[i].col] = startPos[b[i].col] + 1;
    bT[j].row = b[i].col;
    bT[j].col = b[i].row;
    bT[j].value = b[i].value;
  }
}
