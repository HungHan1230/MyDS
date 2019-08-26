#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h> // time 函數所需之標頭檔
double pi(int n)
{
    srand(5);
    int count = 0;
    double x, y;
    for (int i = 0; i < n; ++i)
    {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1)
            ++count;
    }
    return (double)count / n * 4;
}
int main()
{
    // 儲存時間用的變數
    time_t start, end;
    // 開始計算時間
    start = time(NULL);
    // 主要計算
    double result = pi(1e8);
    // 結束計算時間
    end = time(NULL);
    // 計算實際花費時間
    double diff = difftime(end, start);

    printf("PI = %f\n", result);
    printf("Time = %f\n", diff);
}