#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    int t = 0; 
    unsigned int num;
    scanf("%d",&t);
    for(int i =0; i<t; i++){
        scanf("%u",&num);
        printf("%u\n",num);
       
       printf("%u",~(num));
    }
}

