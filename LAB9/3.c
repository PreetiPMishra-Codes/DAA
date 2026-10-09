#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
typedef struct{long long d,f;} St;
static int cmp(const void*a,const void*b){ long long x=((St*)a)->d,y=((St*)b)->d; return (x>y)-(x<y); }
int main(void){
    long long D,F; int n; if(scanf("%lld %lld %d",&D,&F,&n)!=3) return 1;
    St*s=malloc(n*sizeof(St));
    for(int i=0;i<n;i++) if(scanf("%lld %lld",&s[i].d,&s[i].f)!=2) return 1;
    qsort(s,n,sizeof(St),cmp);
    Heap h=hnew(n); int i=0,stops=0; long long reach=F;
    while(reach<D){
        while(i<n && s[i].d<=reach) hpush(&h,-s[i++].f);
        if(h.n==0){ printf("-1 (target unreachable)\n"); return 0; }
        reach+=-hpop(&h); stops++;
    }
    printf("%d\n",stops);
    return 0;
}
