/*
Xor is same as add except that it ignores carry. So if digit is 0 in one number, no carry possible, Only if digit is 1, carry can occur. So -
1) find number of zeroes
2) two to the power of number of zeroes gives result
*/

#include <math.h>
#include <stdio.h>

long int solve(long int n) {
    unsigned long int t = 0;
    long int count=0;
    while(n)
    {
        t=n&1;
        if(t==0)
         count++;   
        n>>=1;
    }
    count = pow(2,count);
    return count;
}

int main() {
    long int n; 
    scanf("%li", &n);
    long int result = solve(n);
    printf("%ld\n", result);
    return 0;
}
