/* Q1 Min coin change. Input: n, coins[n], V. Time O(nV), Space O(V) */
#include <stdio.h>
#include <limits.h>
int main(void) {
    int n, V; scanf("%d", &n);
    int C[n]; for (int i = 0; i < n; i++) scanf("%d", &C[i]);
    scanf("%d", &V);
    int d[V + 1]; d[0] = 0;
    for (int v = 1; v <= V; v++) {
        d[v] = INT_MAX;
        for (int i = 0; i < n; i++)
            if (C[i] <= v && d[v - C[i]] < INT_MAX && d[v - C[i]] + 1 < d[v]) d[v] = d[v - C[i]] + 1;
    }
    printf("%d\n", d[V] == INT_MAX ? -1 : d[V]);
    return 0;
}
