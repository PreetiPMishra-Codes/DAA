#include <stdio.h>
#include <stdlib.h>
static int cmp(const void*a,const void*b){ long long x=*(long long*)a,y=*(long long*)b; return (x>y)-(x<y); }
int main(void){
    int n; if(scanf("%d",&n)!=1) return 1;
    long long*s=malloc(n*sizeof(long long)),*e=malloc(n*sizeof(long long));
    for(int i=0;i<n;i++) if(scanf("%lld %lld",&s[i],&e[i])!=2) return 1;
    qsort(s,n,sizeof(long long),cmp); qsort(e,n,sizeof(long long),cmp);
    int i=0,j=0,cur=0,best=0;
    while(i<n){
        if(s[i]<e[j]){ cur++; i++; if(cur>best) best=cur; }
        else { cur--; j++; }
    }
    printf("%d\n",best);
    return 0;
}
