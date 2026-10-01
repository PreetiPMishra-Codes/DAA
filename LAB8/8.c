/* Q8 Optimal BST. Input: n, p[1..n], q[0..n]. Time O(n^3), Space O(n^2) */
#include <stdio.h>
int main(void) {
    int n; scanf("%d", &n);
    double p[n + 1], q[n + 1], e[n + 2][n + 2], w[n + 2][n + 2]; int root[n + 2][n + 2];
    for (int i = 1; i <= n; i++) scanf("%lf", &p[i]);
    for (int i = 0; i <= n; i++) scanf("%lf", &q[i]);
    for (int i = 1; i <= n + 1; i++) e[i][i-1] = w[i][i-1] = q[i-1];
    for (int l = 1; l <= n; l++)
        for (int i = 1; i + l - 1 <= n; i++) {
            int j = i + l - 1; e[i][j] = 1e18; w[i][j] = w[i][j-1] + p[j] + q[j];
            for (int r = i; r <= j; r++) {
                double t = e[i][r-1] + e[r+1][j] + w[i][j];
                if (t < e[i][j]) e[i][j] = t, root[i][j] = r;
            }
        }
    printf("Expected cost = %.4f, root = k%d\n", e[1][n], root[1][n]);
    return 0;
}
