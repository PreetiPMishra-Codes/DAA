
#include <stdio.h>
#include "heap.h"
int main(void){
    int n; if(scanf("%d",&n)!=1) return 1;
    Heap h=hnew(n+1); long long mn=1LL<<60;
    for(int i=0;i<n;i++){ long long x; if(scanf("%lld",&x)!=1) return 1; if(x&1) x*=2; if(x<mn) mn=x; hpush(&h,-x); }
    long long best=-h.a[0]-mn;
    while(-h.a[0]%2==0){
        long long x=-hpop(&h)/2; if(x<mn) mn=x; hpush(&h,-x);
        long long d=-h.a[0]-mn; if(d<best) best=d;
    }
    printf("%lld\n",best);
    return 0;
}
