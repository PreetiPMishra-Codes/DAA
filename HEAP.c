#ifndef HEAP_H
#define HEAP_H
#include <stdlib.h>
typedef struct { long long *a; int n; } Heap;
static Heap hnew(int cap){ Heap h; h.a=malloc(sizeof(long long)*(cap>0?cap:1)); h.n=0; return h; }
static void hpush(Heap*h,long long x){
    int i=h->n++; h->a[i]=x;
    while(i>0){ int p=(i-1)/2; if(h->a[p]<=h->a[i]) break;
        long long t=h->a[p]; h->a[p]=h->a[i]; h->a[i]=t; i=p; }
}
static long long hpop(Heap*h){
    long long r=h->a[0]; h->a[0]=h->a[--h->n]; int i=0;
    for(;;){ int l=2*i+1,s=i;
        if(l<h->n && h->a[l]<h->a[s]) s=l;
        if(l+1<h->n && h->a[l+1]<h->a[s]) s=l+1;
        if(s==i) break;
        long long t=h->a[s]; h->a[s]=h->a[i]; h->a[i]=t; i=s; }
    return r;
}
#endif
