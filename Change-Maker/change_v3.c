#include <stdio.h>
#include <stdlib.h>
#define INF 999

int A = 0;
int N = 0;

void coinChange(int d[N+1], int C[A+1], int S[A+1]) {
    int i, p, min, coin;
    C[0] = 0;
    S[0] = 0;
    for(p = 1; p <= A; p++) {
        min = INF;
        for(i = 1; i <= N; i++) {
            if(d[i] <= p) {
                if(1 + C[p - d[i]] < min) {
                    min = 1 + C[p - d[i]];
                    coin = i;
                }
            }
        }
        C[p] = min;
        S[p] = coin;
    }
}

void coinSet(int d[N+1], int S[A+1]) {
    int a = A;
    int freq[N+1];
    for(int i = 0 ;i<N+1;i++) {
            freq[i]=0;
    }
    while(a > 0) {
        freq[S[a]]++;
        a = a - d[S[a]];
    }
    for(int i = 0 ; i < N+1 ; i++) {
        if(freq[i] > 0)
            printf("%d : %d\n", d[i], freq[i]);
    }
}

void display(int arr[A+1]) {
    int c;
    for(c = 0; c <= A; c++) {
        printf("%d", arr[c]);
    }
    printf("\n");
}

int main(void) {

    int V = 0;
    int n = 0;
    printf("Enter number of denominations:\n");
    scanf("%d", &n);
    N=n;
    int *coins = (int*)malloc ((n+1)*( sizeof(int)));
    coins[0] = 0;
    printf("Enter denominations:\n");
    for(int i=1;i<=n;i++)
        scanf("%d", &coins[i]);
    
    int cnum = 0;
    printf("Enter number of test cases:\n");
    scanf("%d", &cnum);

    int *currencies = (int*)malloc((cnum)*(sizeof(int)));
    printf("Enter the test cases:\n");
    for(int i = 0 ; i<cnum;i++) {
        scanf("%d", &currencies[i]);
    }
    for(int i = 0 ; i<cnum;i++) {
        A=currencies[i];
        int *C = (int*)malloc ((A+1)*(sizeof(int)));
        int *S = (int*)malloc ((A+1)*(sizeof(int)));
        coinChange(coins, C, S);
        if(C[A] == 999)
            printf("Change not possible for amount %d\n", currencies[i]);
        else
        {
            printf("Min. no. of coins required to make change for amount %d = %d\n", currencies[i], C[A]);
            printf("Coin Set\n");
            coinSet(coins, S);
        }
    }        
    return 0;
}
