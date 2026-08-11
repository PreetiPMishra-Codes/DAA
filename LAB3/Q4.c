#include <stdio.h>
#include <stdlib.h>

int **alloc(int n) {
    int **m = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) m[i] = calloc(n, sizeof(int));
    return m;}
void freeMat(int **m, int n) {
    for (int i = 0; i < n; i++) free(m[i]);
    free(m);}
void add(int **a, int **b, int **c, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = a[i][j] + b[i][j];}
void sub(int **a, int **b, int **c, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = a[i][j] - b[i][j];}
void strassen(int **a, int **b, int **c, int n) {
    if (n == 1) {
        c[0][0] = a[0][0] * b[0][0];
        return;}
    int k = n / 2;
    int **a11 = alloc(k), **a12 = alloc(k), **a21 = alloc(k), **a22 = alloc(k);
    int **b11 = alloc(k), **b12 = alloc(k), **b21 = alloc(k), **b22 = alloc(k);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            a11[i][j] = a[i][j];
            a12[i][j] = a[i][j + k];
            a21[i][j] = a[i + k][j];
            a22[i][j] = a[i + k][j + k];
            b11[i][j] = b[i][j];
            b12[i][j] = b[i][j + k];
            b21[i][j] = b[i + k][j];
            b22[i][j] = b[i + k][j + k];}
    int **m1 = alloc(k), **m2 = alloc(k), **m3 = alloc(k), **m4 = alloc(k);
    int **m5 = alloc(k), **m6 = alloc(k), **m7 = alloc(k);
    int **t1 = alloc(k), **t2 = alloc(k);
    add(a11, a22, t1, k); add(b11, b22, t2, k); strassen(t1, t2, m1, k);
    add(a21, a22, t1, k); strassen(t1, b11, m2, k);
    sub(b12, b22, t1, k); strassen(a11, t1, m3, k);
    sub(b21, b11, t1, k); strassen(a22, t1, m4, k);
    add(a11, a12, t1, k); strassen(t1, b22, m5, k);
    sub(a21, a11, t1, k); add(b11, b12, t2, k); strassen(t1, t2, m6, k);
    sub(a12, a22, t1, k); add(b21, b22, t2, k); strassen(t1, t2, m7, k);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            c[i][j] = m1[i][j] + m4[i][j] - m5[i][j] + m7[i][j];
            c[i][j + k] = m3[i][j] + m5[i][j];
            c[i + k][j] = m2[i][j] + m4[i][j];
            c[i + k][j + k] = m1[i][j] - m2[i][j] + m3[i][j] + m6[i][j];}
    int **all[] = {a11,a12,a21,a22,b11,b12,b21,b22,m1,m2,m3,m4,m5,m6,m7,t1,t2};
    for (int i = 0; i < 17; i++) freeMat(all[i], k);}
int main() {
    int n;
    printf("Enter size n (power of 2): ");
    scanf("%d", &n);
    int **a = alloc(n), **b = alloc(n), **c = alloc(n);
    printf("Enter matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) scanf("%d", &a[i][j]);
    printf("Enter matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) scanf("%d", &b[i][j]);
    strassen(a, b, c, n);
    printf("Result matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%d ", c[i][j]);
        printf("\n");}
    freeMat(a, n); freeMat(b, n); freeMat(c, n);
    return 0;
}
