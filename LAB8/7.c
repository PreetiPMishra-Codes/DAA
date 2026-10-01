/* Q7 Rod cutting + reconstruction. Input: n, P[1..n]. Time O(n^2), Space O(n) */
#include <stdio.h>
#include <limits.h>
int main(void) {
    int n; scanf("%d", &n);
    int P[n + 1], r[n + 1], cut[n + 1];
    for (int i = 1; i <= n; i++) scanf("%d", &P[i]);
    r[0] = 0;
    for (int j = 1; j <= n; j++) {
        r[j] = INT_MIN;
        for (int i = 1; i <= j; i++) if (P[i] + r[j-i] > r[j]) r[j] = P[i] + r[j-i], cut[j] = i;
    }
    printf("Max revenue = %d\nPieces:", r[n]);
    for (int j = n; j; j -= cut[j]) printf(" %d", cut[j]);
    puts("");
    return 0;
}
