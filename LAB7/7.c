#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int n;
long long **m;
int **s;

void print_optimal_parens(int i, int j) {
    if (i == j) { printf("A%d", i); return; }
    printf("(");
    print_optimal_parens(i, s[i][j]);
    print_optimal_parens(s[i][j] + 1, j);
    printf(")");
}

int main(void) {
    printf("Enter number of matrices n: ");
    if (scanf("%d", &n) != 1 || n < 1) return 1;

    int *p = malloc((n + 1) * sizeof(int));
    printf("Enter %d dimensions p[0..%d]:\n", n + 1, n);
    for (int i = 0; i <= n; i++) {
        printf("p[%d]: ", i);
        if (scanf("%d", &p[i]) != 1 || p[i] <= 0) return 1;
    }

    m = malloc((n + 1) * sizeof(long long *));
    s = malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        m[i] = calloc(n + 1, sizeof(long long));
        s[i] = calloc(n + 1, sizeof(int));
    }

    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = LLONG_MAX;
            for (int k = i; k < j; k++) {
                long long cost = m[i][k] + m[k + 1][j] + (long long)p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) { m[i][j] = cost; s[i][j] = k; }
            }
        }
    }

    printf("\nMinimum scalar multiplications: %lld\n", m[1][n]);
    printf("Optimal parenthesisation: ");
    print_optimal_parens(1, n);
    printf("\n");

    for (int i = 0; i <= n; i++) { free(m[i]); free(s[i]); }
    free(m); free(s); free(p);
    return 0;
}
