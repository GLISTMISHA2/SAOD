#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void FillInc(long long int A[], int n){
    for(int i=0;i<n;i++){
        A[i] = i+1;
    }
}
void FillDec(long long int A[], int n) {
    int k = n;
    for (int i = 0; i < n; i++) {
        A[i] = k;
        k--;
    }
}
void FillRand(long long int A[],int n){
    srand(time(NULL));
    for(int i=0;i<n;i++){
        A[i]= rand();
    }
}

int SelectSort(long long int A[],int n){
    int C = 0;
    int M = 0;
    for(int i =0 ; i<n-1;i++){
        int k = i;
        for (int j = i+1;j<n;j++){
            C++;
            if(A[j]<A[k]){
                k = j;
            }
        }
        //A[j]<-->A[k]
        M = M+3;
        long long int x = A[i];
        A[i] = A[k];
        A[k] = x;

    }
    return M+C;
}

void PrintMas(long long int A[],int n){
    for (int i=0;i<n;i++){
        printf("%lld ",A[i]);
    }
    printf("\n");
}
int main(){
    //int C = 0; сравнения
    //int M = 0; перессылки
    int n10 = 10;
    int n100 = 100;
    long long int A_1[n10];
    long long int A_2[n10];
    long long int A_3[n10];
    long long int A_11[n100];
    long long int A_22[n100];    
    long long int A_33[n100];
    FillInc(A_1,n10);
    int res1 = SelectSort(A_1,n10);

    FillDec(A_2,n10);
    int res2 = SelectSort(A_2,n10);

    FillRand(A_3,n10);
    int res3 = SelectSort(A_3,n10);

    FillInc(A_11,n100);
    int res11 = SelectSort(A_11,n100);

    FillDec(A_22,n100);
    int res22 = SelectSort(A_22,n100);

    FillRand(A_33,n100);
    int res33 = SelectSort(A_33,n100);


    int teor1=(3*(10-1))+(10*10-10)/2;
    int teor2=(3*(100-1))+(100*100-100)/2;


    printf(" ________________________________________\n");
    printf("|   N   |  M+C  |      Исходный M+С     |\n");
    printf("|       |       |_______________________|\n");
    printf("|       |Теорет.| Убыв. | Случ. | Возр. |\n");
    printf("|_______|_______|_______|_______|_______|\n");
    printf("|   10  |   %d  |  %d   | %d    |   %d  |\n",teor1,res2,res3,res1);
    printf("|_______|_______|_______|_______|_______|\n");
    printf("|  100  |  %d | %d  | %d  | %d  |\n",teor2,res22,res33,res11);
    printf("|_______|_______|_______|_______|_______|\n");
}