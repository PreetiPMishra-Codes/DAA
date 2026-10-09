
#include <stdio.h>
#include "heap.h"
int main(void){
    int n; if(scanf("%d",&n)!=1) return 1;
    Heap h=hnew(n+1);
    for(int i=0;i<n;i++){ long long x; if(scanf("%lld",&x)!=1) return 1; hpush(&h,x); }
    long long cost=0;
    while(h.n>1){ long long a=hpop(&h),b=hpop(&h); cost+=a+b; hpush(&h,a+b); }
    printf("%lld\n",cost);
    return 0;
}
