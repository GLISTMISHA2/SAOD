#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void FillInc(int A[], int n){
    for(int i=0;i<n;i++){
        A[i] = i+1;
    }
}
void FillDec (int A[], int n){
    for(int i=0;i<n;i++){
        A[i] = n-i;
    }
}
void FillRand(int A[],int n){
    srand(time(NULL));
    for(int i=0;i<n;i++){
        A[i]= rand();
    }
}
unsigned long long int CheckSum(int A[],int n){
    unsigned long long int sum=0;
    for(int i=0;i<n;i++){
        sum = sum + A[i];
    }
    return (unsigned long long int) sum;
}
int RunNumber(int A[],int n){
    int count = 1;
        for (int i=1;i<n;i++){
            if (A[i]<A[i-1]){
                count++;
            }
    }
    return count;
}
void PrintMas(int A[],int n){
    for (int i=0;i<n;i++){
        printf("%d ",A[i]);
    }
    printf("\n");
}

int main(){
    int n = 10;
    //scanf("%d",&n);
    int A[n];
    unsigned long long int sum;
    FillInc(A,n);
    printf("Возрастающий массив: ");
    PrintMas(A,n);
    sum = CheckSum(A,n);
    printf("Контрольная сумма: %lld\n",sum);
    printf("Количество серий: %d\n",RunNumber(A, n));

    FillDec(A,n);
    printf("Убывающий массив: ");
    PrintMas(A,n);
    sum = CheckSum(A,n);
    printf("Контрольная сумма: %lld\n",sum);
    printf("Количество серий: %d\n",RunNumber(A,n));

    FillRand(A,n);
    printf("Случайный массив: ");
    PrintMas(A,n);
    sum = CheckSum(A,n);
    printf("Контрольная сумма: %lld\n",sum);
    printf("Количество серий: %d\n",RunNumber(A,n));
}