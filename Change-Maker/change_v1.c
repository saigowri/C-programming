#include<stdio.h>
#include<stdlib.h>
int main(){
int n,count=0,t,a;
int *deno;
int curr;
int *countarr;
scanf("%d",&n);
deno = (int*)malloc(sizeof(int)*n);
countarr = (int*)malloc(sizeof(int)*n);
for(int i=0; i<n; i++) {
	scanf("%d",&deno[i]);
	countarr[i]=0;
}
for (int i = 0; i < n; ++i) {
	for (int j = i + 1; j < n; ++j) {
        	if (deno[i] < deno[j]) {
                	a = deno[i];
                	deno[i] = deno[j];
                	deno[j] = a;
        	}
	}
}
scanf("%d",&t);
for(int i=0; i<t; i++) {
	scanf("%d",&curr);
	for(int j=0;j<n;j++){
		count=0;
		while(curr>=deno[j] && curr!=0){
			count++;
			curr-=deno[j];
		}
		countarr[j]=count;
	}
	if(curr!=0)
		printf("Not possible");
	else {
		for(int j=0;j<n;j++){
			printf("%d: %d ",deno[j], countarr[j]);
		}
	}
	printf("\n");
}
return 0;
}
