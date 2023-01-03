#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int check_palindrom(int**, char*, int, int, int);


int check_palindrom(int** flag, char* pal, int i, int j, int size) {

    if (j > size) return 0;

    if (pal[i] == pal[j]) {
        if (flag[i + 1][j - 1]==1 || i + 1 == j) {

            return 1;
        }
    }

    return 0;
}



int main(void) {

    FILE* fp1, * fp2;
    int N, i, j, k, n, m, temp = 0, start = 0;
    
    int** flag;
    int* info;

    fp1 = fopen("input.txt", "r");
    fp2 = fopen("ouput.txt", "w");

    //fread(&N,sizeof(int),1,fp1);
    fscanf(fp1, "%d", &N);

    fprintf(fp2, "%d\n", N);

    for (i = 0; i < N; i++) {

        //fread(&j,sizeof(int),1,fp1);
        fscanf(fp1, "%d\n", &j);
       
        char* palindrom = (char*)malloc(sizeof(char) * (j + 2));
        palindrom[0] = ' ';
        for (int q = 1; q <= j; q++) {
            fscanf(fp1, "%c", &palindrom[q]);
        }
        //fread(palindrom,sizeof(char),j,fp1);
        palindrom[j+1] = '\0';

        flag = (int**)malloc(sizeof(int*) * (j + 1));                                        
        for (k = 0; k <= j; k++) {

            flag[k] = (int*)malloc(sizeof(int) * (j + 1));
        }
        
        for (m = 0; m <= j; m++) {
            for (n = m; n <= j; n++) {
                flag[m][n] = 1e9;
            }
        }
       


        for (m = 0; m < j; m++) {
            for (n = 1; m + n <= j; n++) {

                if (m == 0) {

                    flag[n][n] = 1;
                    continue;
                }

                if (check_palindrom(flag, palindrom, n, m + n, j))
                    flag[n][m + n] = 1;

            }
        }

        info = (int*)malloc(sizeof(int) * (j + 1));

        info[0] = 0;
        n = 1;
        for (m = 1; m <= j; m++) {
            info[m] = 1e8;
            for (n =1; n <= m; n++) {

                if (flag[n][m]==1) {
                     if (info[m] > info[n - 1] + 1) info[m] = info[n - 1] + 1;
                }
            }
        }
     
        
        fprintf(fp2, "%d\n", info[j]);
        for (m = 1; m <= j; m++) {
            if (m == 1) {
                temp = info[m];
                start = m;
            }
            else if (info[m] < info[m - 1] && info[m] == temp) {
                
                for (n = start; n <= m; n++) {
                    fprintf(fp2, "%c", palindrom[n]);
                }
                fprintf(fp2, "\n");
                temp += 1;
                start = m + 1;

            }
        }

        free(info);
        free(flag);
        free(palindrom);
    }

    
    fclose(fp1);
    fclose(fp2);


    return 0;
}
