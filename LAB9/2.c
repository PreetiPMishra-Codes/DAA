
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#define SH 20
typedef struct{ char c; long long f; int len; } Sym;
static int cmp(const void*a,const void*b){
    const Sym*x=a,*y=b;
    if(x->len!=y->len) return x->len-y->len;
    return (unsigned char)x->c-(unsigned char)y->c;
}
int main(void){
    int n; if(scanf("%d",&n)!=1) return 1;
    Sym*s=malloc(n*sizeof(Sym));
    long long *f=malloc(2*n*sizeof(long long));
    int *L=malloc(2*n*sizeof(int)),*R=malloc(2*n*sizeof(int)),*dep=calloc(2*n,sizeof(int));
    Heap h=hnew(n+1);
    for(int i=0;i<n;i++){ if(scanf(" %c %lld",&s[i].c,&s[i].f)!=2) return 1; f[i]=s[i].f; hpush(&h,(f[i]<<SH)|i); }
    int cnt=n;
    while(h.n>1){
        int a=hpop(&h)&((1<<SH)-1), b=hpop(&h)&((1<<SH)-1);
        f[cnt]=f[a]+f[b]; L[cnt]=a; R[cnt]=b;
        hpush(&h,(f[cnt]<<SH)|cnt); cnt++;
    }
    for(int k=cnt-1;k>=n;k--){ dep[L[k]]=dep[k]+1; dep[R[k]]=dep[k]+1; }
    long long cost=0;
    for(int i=0;i<n;i++){ s[i].len=dep[i]?dep[i]:1; cost+=s[i].f*s[i].len; }
    qsort(s,n,sizeof(Sym),cmp);
    unsigned long long code=0; int prev=s[0].len;
    printf("sym freq len code\n");
    for(int i=0;i<n;i++){
        if(i>0) code=(code+1)<<(s[i].len-prev);
        prev=s[i].len;
        printf("%c   %lld  %d  ",s[i].c,s[i].f,s[i].len);
        for(int b=s[i].len-1;b>=0;b--) putchar('0'+((code>>b)&1));
        putchar('\n');
    }
    printf("Total encoded length = %lld bits\n",cost);
    return 0;
}
