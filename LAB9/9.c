#include <stdio.h>
#include <stdlib.h>
int main(void){
    int n; if(scanf("%d",&n)!=1) return 1;
    long long*w=malloc(2*n*sizeof(long long)); int*sq=calloc(2*n,sizeof(int)),*L=malloc(2*n*sizeof(int)),*R=malloc(2*n*sizeof(int)),*dep=calloc(2*n,sizeof(int));
    int*seq=malloc(n*sizeof(int));
    for(int i=0;i<n;i++){ if(scanf("%lld",&w[i])!=1) return 1; sq[i]=1; seq[i]=i; }
    int m=n,cnt=n;
    while(m>1){
        int bi=-1,bj=-1; long long bs=0;
        for(int i=0;i<m;i++)
            for(int j=i+1;j<m;j++){
                long long s=w[seq[i]]+w[seq[j]];
                if(bi<0||s<bs){bs=s;bi=i;bj=j;}
                if(sq[seq[j]]) break;      
            }
        w[cnt]=bs; L[cnt]=seq[bi]; R[cnt]=seq[bj];
        seq[bj]=cnt++;     
        for(int k=bi;k<m-1;k++) seq[k]=seq[k+1];
        m--;
    }
    for(int k=cnt-1;k>=n;k--){ dep[L[k]]=dep[k]+1; dep[R[k]]=dep[k]+1; }
    long long cost=0;
    for(int i=0;i<n;i++){ printf("w=%lld depth=%d\n",w[i],dep[i]); cost+=w[i]*dep[i]; }
    printf("Hu-Tucker cost = %lld\n",cost);
    long long*P=calloc(n+1,sizeof(long long)); for(int i=0;i<n;i++) P[i+1]=P[i]+w[i];
    long long*C=calloc((size_t)n*n,sizeof(long long));
    for(int len=2;len<=n;len++) for(int i=0;i+len<=n;i++){
        int j=i+len-1; long long b=-1;
        for(int k=i;k<j;k++){ long long c=C[i*n+k]+C[(k+1)*n+j]; if(b<0||c<b)b=c; }
        C[i*n+j]=b+P[j+1]-P[i];
    }
    printf("DP optimum     = %lld  %s\n",C[n-1],C[n-1]==cost?"(match)":"(MISMATCH)");
    return 0;
}
