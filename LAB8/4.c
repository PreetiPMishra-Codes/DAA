/* Q4 LIS (strict). Input: n, A[n]. Time O(n log n), Space O(n) */
#include <stdio.h>
int main(void) {
    int n; scanf("%d", &n);
    int t[n], len = 0;
    for (int i = 0, x; i < n; i++) {
        scanf("%d", &x);
        int lo = 0, hi = len;
        while (lo < hi) { int mid = (lo + hi) / 2; if (t[mid] < x) lo = mid + 1; else hi = mid; }
        t[lo] = x; if (lo == len) len++;
    }
    printf("%d\n", len);
    return 0;
}
