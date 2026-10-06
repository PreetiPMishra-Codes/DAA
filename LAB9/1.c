#include <stdio.h>
#include <stdlib.h>
int main(void){
    int n; double W;
    if(scanf("%d %lf",&n,&W)!=2) return 1;
    double *v=malloc(n*sizeof(double)),*w=malloc(n*sizeof(double)),*l=malloc(n*sizeof(double));
    char *used=calloc(n,1);
    for(int i=0;i<n;i++) if(scanf("%lf %lf %lf",&v[i],&w[i],&l[i])!=3) return 1;
    double t=0,total=0,rem=W;
    while(rem>1e-12){
        int b=-1; double bd=1e-12;
        for(int i=0;i<n;i++) if(!used[i]){
            double d=v[i]/w[i]-l[i]*t;
            if(d>bd){bd=d;b=i;}
        }
        if(b<0) break;
        double take=w[b]<rem?w[b]:rem;
        printf("t=%.3f take %.3f of item %d (density %.3f) -> +%.3f\n",t,take,b+1,bd,take*bd);
        total+=take*bd; t+=take; rem-=take; used[b]=1;
    }
    printf("Total value = %.4f\n",total);
    return 0;
}
