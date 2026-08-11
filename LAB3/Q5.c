#include <stdio.h>

int main() {
    int n;
    printf("Enter n (power of 2): ");
    scanf("%d", &n);
    int A[n][n], B[n][n], C[n][n];
    int a[n], b[n], c[n];
    printf("Enter matrix A (n x n, must follow M1,M2 / M2,M1 pattern):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) scanf("%d", &A[i][j]);
    printf("Enter matrix B (same pattern):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) scanf("%d", &B[i][j]);
    for (int d = 0; d < n; d++) { a[d] = A[0][d]; b[d] = B[0][d]; }
    for (int m = 0; m < n; m++) {
        int sum = 0;
        for (int l = 0; l < n; l++) sum += a[l] * b[l ^ m];
        c[m] = sum;}
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) C[i][j] = c[i ^ j];
    printf("Result matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%d ", C[i][j]);
        printf("\n");}
    return 0;
}
