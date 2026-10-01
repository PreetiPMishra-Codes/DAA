/* Q2 Number of combinations. Input: n, coins[n], V. Time O(nV), Space O(V) */
#include <stdio.h>
#include <string.h>
int main(void) {
    int n, V; scanf("%d", &n);
    int C[n]; for (int i = 0; i < n; i++) scanf("%d", &C[i]);
    scanf("%d", &V);
    long long d[V + 1]; memset(d, 0, sizeof d); d[0] = 1;
    for (int i = 0; i < n; i++)
        for (int v = C[i]; v <= V; v++) d[v] += d[v - C[i]];
    printf("%lld\n", d[V]);
    return 0;
}
