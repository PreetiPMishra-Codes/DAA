#include <stdio.h>
#include <stdlib.h>
int main(void){
    int n; if(scanf("%d",&n)!=1) return 1;
    int*r=malloc(n*sizeof(int)),*c=malloc(n*sizeof(int));
    for(int i=0;i<n;i++){ if(scanf("%d",&r[i])!=1) return 1; c[i]=1; }
    for(int i=1;i<n;i++) if(r[i]>r[i-1]) c[i]=c[i-1]+1;
    for(int i=n-2;i>=0;i--) if(r[i]>r[i+1] && c[i]<=c[i+1]) c[i]=c[i+1]+1;
    long long sum=0; for(int i=0;i<n;i++){ sum+=c[i]; printf("%d ",c[i]); }
    printf("\nTotal = %lld\n",sum);
    return 0;
}
