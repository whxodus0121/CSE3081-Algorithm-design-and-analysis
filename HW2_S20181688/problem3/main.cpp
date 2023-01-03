#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int flag[1001][1001];

int check_card(int* l, int* r, int* t, int ls, int rs, int ts) {

    int i, j;
    /*
    int** flag;

    flag = (int**)malloc(sizeof(int) * (ls + 1));
    for (i = 0; i <= ls; i++) {

        flag[i] = (int*)malloc(sizeof(int) * (rs + 1));
    }
   
    for (i = 0; i <= ls; i++) {
        for (j = 0; j <= rs; j++) {

            flag[i][j] = 0;
        }
    }
    */
    for (i = 0; i <= 1000; i++) {
        for (j = 0; j <= 1000; j++) {

            flag[i][j] = 0;
        }
    }

    flag[0][0] = 1;

    for (i = 1; i <= ls; i++) {
        if (l[i - 1] == t[i - 1] && flag[i - 1][0] == 1) {

            flag[i][0] = 1;
        }
    }

    for (j = 1; j <= rs; j++) {
        if (r[j - 1] == t[j - 1] && flag[0][j - 1] == 1) {

            flag[0][j] = 1;
        }
    }

    for (i = 1; i <= ls; i++) {

        for (j = 1; j <= rs; j++) {

            if (flag[i][j - 1] == 1 && t[i + j - 1] == r[j - 1])
                flag[i][j] = 1;

            else if (flag[i - 1][j] == 1 && t[i + j - 1] == l[i - 1])
                flag[i][j] = 1;
        }
    }

    if (flag[ls][rs] == 1) return 1;
    else return 0;

    free(flag);
}

int main() {

    FILE* fp1, * fp2;
    int i, left_size, right_size, testcase_size[2], result[2];
    int* left_hand, * right_hand, * testcase[2];


    fp1 = fopen("input.txt", "r");
    fp2 = fopen("output.txt", "w");

    fscanf(fp1, "%d", &left_size);
    left_hand = (int*)malloc(sizeof(int) * left_size);
    for (i = 0; i < left_size; i++) {
        fscanf(fp1, "%d", &left_hand[i]);
    }

    fscanf(fp1, "%d", &right_size);
    right_hand = (int*)malloc(sizeof(int) * right_size);
    for (i = 0; i < right_size; i++) {
        fscanf(fp1, "%d", &right_hand[i]);
    }

    fscanf(fp1, "%d", &testcase_size[0]);
    testcase[0] = (int*)malloc(sizeof(int) * testcase_size[0]);
    for (i = 0; i < testcase_size[0]; i++) {
        fscanf(fp1, "%d", &testcase[0][i]);
    }

    result[0] = check_card(left_hand, right_hand, testcase[0], left_size, right_size, testcase_size[0]);

    fscanf(fp1, "%d", &testcase_size[1]);
    testcase[1] = (int*)malloc(sizeof(int) * testcase_size[1]);
    for (i = 0; i < testcase_size[1]; i++) {
        fscanf(fp1, "%d", &testcase[1][i]);
    }

    result[1] = check_card(left_hand, right_hand, testcase[1], left_size, right_size, testcase_size[1]);

    fprintf(fp2, "%d%d\n", result[0], result[1]);
    
    free(right_hand);
    free(left_hand);
    fclose(fp1);
    fclose(fp2);

    return 0;
}