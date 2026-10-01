/* Q5 Max-sum increasing subsequence. Input: n, A[n]. Time O(n^2), Space O(n) */
#include <stdio.h>
int main(void) {
    int n; scanf("%d", &n);
    int A[n]; long long s[n], best = 0;
    for (int i = 0; i < n; i++) scanf("%d", &A[i]);
    for (int i = 0; i < n; i++) {
        s[i] = A[i];
        for (int j = 0; j < i; j++) if (A[j] < A[i] && s[j] + A[i] > s[i]) s[i] = s[j] + A[i];
        if (s[i] > best) best = s[i];
    }
    printf("%lld\n", best);
    return 0;
}
