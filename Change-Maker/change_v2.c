#include<stdio.h>
#include<stdlib.h>
int main(){
int n,count=0,t,a;
int *deno;
int curr;
int *used;
int *countarr;
scanf("%d",&n);
deno = (int*)malloc(sizeof(int)*n);
countarr = (int*)malloc(sizeof(int)*n);
used = (int*)malloc(sizeof(int)*n);
for(int i=0; i<n; i++) {
	scanf("%d",&deno[i]);
	scanf("%d",&countarr[i]);
}
for(int i=0; i<n; i++) {
	for (int j=i+1; j<n; j++) {
        	if (deno[i] < deno[j]) {
                	a = deno[i];
                	deno[i] = deno[j];
                	deno[j] = a;
                	a = countarr[i];
                	countarr[i] = countarr[j];
                	countarr[j] = a;
        	}
	}
}
scanf("%d",&t);
for(int i=0; i<t; i++) {
	scanf("%d",&curr);
	for(int j=0;j<n;j++){
		count=0;
		while(curr>=deno[j] && curr!=0){
			if(countarr[j]>0) {
				countarr[j]--;
				curr-=deno[j];
				count++;
			}
			else {
				break;
			}
		}
		used[j]=count;
	}
	if(curr!=0)
		printf("Not possible");
	else {
		for(int j=0;j<n;j++){
			printf("%d: %d ",deno[j], used[j]);
		}
	}
	printf("\n");
}
printf("Remaining amount:\n");
for(int j=0;j<n;j++){
	printf("%d: %d ",deno[j], countarr[j]);
}
return 0;
}
