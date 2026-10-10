#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(void){
    static char S[1000005]; int K; if(scanf("%1000000s %d",S,&K)!=2) return 1;
    int n=strlen(S),cnt[256]={0}; int last[256];
    for(int i=0;i<256;i++) last[i]=-1000000000;
    for(int i=0;i<n;i++) cnt[(unsigned char)S[i]]++;
    char*out=malloc(n+1);
    for(int i=0;i<n;i++){
        int b=-1;
        for(int c=0;c<256;c++)
            if(cnt[c]>0 && i-last[c]>=K && (b<0||cnt[c]>cnt[b])) b=c;
        if(b<0){ printf("\"\" (impossible)\n"); return 0; }
        out[i]=(char)b; cnt[b]--; last[b]=i;
    }
    out[n]=0; printf("%s\n",out);
    return 0;
}
