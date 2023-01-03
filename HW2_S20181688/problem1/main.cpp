#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(x,y) (x)<(y) ? (x):(y)
#define max(x,y) (x)>(y) ? (x):(y)

void gapped_alignment(int, int, char*, char*, int, int, int);

void gapped_alignment(int size_x, int size_y, char* x, char* y, int s, int f, int p) {

    int i, j, result, m = 0, n = 0, xcount = 0, ycount = 0,hit=0,count=0,temp=0;
    int* xgap, * ygap;
    int** S, ** flag;
    FILE* fp;

    S = (int**)malloc(sizeof(int*) * (size_x + 1));
    for (i = 0; i < size_x+1; i++) {

        S[i] = (int*)malloc(sizeof(int) * (size_y + 1));
    }
    flag = (int**)malloc(sizeof(int*) * (size_x + 1));
    for (i = 0; i < size_x+1; i++) {

        flag[i] = (int*)malloc(sizeof(int) * (size_y + 1));
    }
    /*
    for (i = 0; i <= size_x; i++) {
        for (j = 0; j <= size_y; j++) {
            S[i][j] = 0;
            flag[i][j] = 0;
        }
    }
    */
    /*
    for (i = 0; i <= size_x; i++) {
        for (j = 0; j <= size_y; j++) {
            if (i == 0) S[i][j] = (-1) * p * j;
            else if (j == 0 ) S[i][j] = (-1) * p * i;
            else {

                if (x[i - 1] == y[j - 1]) result = S[i - 1][j - 1] + s;
                else result = S[i - 1][j - 1] - f;

                if (result < S[i - 1][j] - p) result = S[i - 1][j] - p;
                else if (result < S[i][j - 1] - p) result = S[i][j - 1] - p;
                S[i][j] = result;

                if (S[i - 1][j - 1] > S[i - 1][j] && S[i - 1][j - 1] > S[i][j - 1]) flag[i - 1][j - 1] = 0;
                else if (S[i - 1][j] > S[i - 1][j] && S[i - 1][j] > S[i - 1][j - 1]) flag[i - 1][j - 1] = 1;
                else if (S[i][j - 1] > S[i - 1][j - 1] && S[i][j - 1] > S[i][j - 1]) flag[i - 1][j - 1] = 2;
                else flag[i - 1][j - 1] = 0;
            }

        }
    }
    */

    for (i = 1; i <= size_x; i++) {

        S[i][0] = (-1) * p * i;
        flag[i][0] = 2;
    }

    for (i = 0; i <= size_y; i++) {
        
        S[0][i] = (-1) * p * i;
        flag[0][i] = 1;
    }

    for (i = 1; i <= size_x; i++) {
        for (j = 1; j <= size_y; j++) {

            if (x[i - 1] == y[j - 1])
                hit = s;
            else
                hit = (-1) * f;
            
            if (S[i - 1][j - 1] + hit >= S[i][j - 1] - p && S[i - 1][j - 1] + hit >= S[i - 1][j] - p) {
                
                S[i][j] = S[i - 1][j - 1] + hit;
                flag[i][j] = 0;
            }
            else if (S[i][j - 1] - p > S[i - 1][j - 1] + hit && S[i][j - 1] - p > S[i - 1][j] - p) {

                S[i][j] = S[i][j - 1] - p;
                flag[i][j] = 1;
            }
            else if (S[i-1][j] - p > S[i - 1][j - 1] + hit && S[i-1][j] - p >= S[i][j-1] - p) {

                S[i][j] = S[i-1][j] - p;
                flag[i][j] = 2;
            }
        }
    }

    i = size_x;
    j = size_y;

    while (i>=0&&j>=0) {

        if (flag[i][j] == 0) {

            i--;
            j--;
        }
        else if (flag[i][j] == 2) {
            
            i--;
            ycount++;     
        }
        else {
            
            j--;
            xcount++;
        }
        count++;
        //if (i == 0 && j == 0) break;
    }
    temp = count;
    
    xgap = (int*)malloc(sizeof(int) * count);
    ygap = (int*)malloc(sizeof(int) * count);

    i = size_x ;
    j = size_y ;

    while (temp!=0) {

        if (flag[i][j] == 0) {

            i--;
            j--;
        }
        else if (flag[i][j] == 2) {

            ygap[m] = i;
            m++;
            i--;
        }
        else {

            xgap[n] = j;
            n++;
            j--;
        }
        temp--;
    }


    fp = fopen("output.txt", "w");
    fprintf(fp, "%d\n", S[size_x][size_y]);
    fprintf(fp, "%d\n", count);
    

    fprintf(fp, "%d\n", xcount);
    for (i = xcount - 1; xcount >= 1 && i >= 0; i--) {
        fprintf(fp, "%d\n", xgap[i]+1);
    }

    fprintf(fp, "%d\n", ycount);
    for (i = ycount - 1; ycount >= 1 && i >= 0; i--) {

        fprintf(fp, "%d\n", ygap[i]+1);
    }
    free(S);
    free(flag);
    free(xgap);
    free(ygap);
    fclose(fp);
}

int main(void) {

    FILE* fp;
    char file_name[30];
    int size_x = 0, size_y = 0;
    int s = 0, f = 0, p = 0;
    char* x, * y;

    fp = fopen("input.txt", "r");
    fscanf(fp, "%s", file_name);
    fscanf(fp, "%d %d %d", &s, &f, &p);
    fclose(fp);

    fp = fopen(file_name, "rb");

    fread(&size_x, sizeof(int), 1, fp);
    fread(&size_y, sizeof(int), 1, fp);

    x = (char*)malloc(sizeof(char) * size_x + 1);
    y = (char*)malloc(sizeof(char) * size_y + 1);

    fread(x, sizeof(char), size_x, fp);
    x[size_x] = '\0';
    fread(y, sizeof(char), size_y, fp);
    y[size_y] = '\0';

    gapped_alignment(size_x, size_y, x, y, s, f, p);
        
    fclose(fp);
    return 0;
}