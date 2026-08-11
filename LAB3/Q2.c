#include <stdio.h>

int weight[1000];
int solve(int idx[], int n, int ref) {
    if (n==0) return -1;
    if (n==1) {
        if (ref== -1) return idx[0];
        return (weight[idx[0]] < weight[ref]) ? idx[0] : -1;}
    int half=n/2;
    int sumA=0,sumB=0;
    for (int i=0;i<half;i++) sumA+=weight[idx[i]];
    for (int i=half;i<2*half;i++) sumB+=weight[idx[i]];
    if (sumA<sumB) return solve(idx,half,ref);
    if (sumA>sumB) return solve(idx+half,half,ref);
    int newRef=idx[0];
    if (n%2==1) return solve(&idx[n - 1],1,newRef);
    return -1;
}
int main() {
    int n;
    printf("Enter number of coins: ");
    scanf("%d,&n);
    int idx[n];
    printf("Enter weight of each coin: ");
    for (int i=0;i<n;i++) {
        scanf("%d", &weight[i]);
        idx[i]=i; }
    int result=solve(idx, n, -1);
    if (result==-1) printf("No defective coin found, all are perfect.\n");
    else printf("Defective (lighter) coin is at position %d\n", result + 1);
    return 0;}
