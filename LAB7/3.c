#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long *FS;
int *split;
long long move_count = 0;

long long pow2(int e) { long long r = 1; while (e-- > 0) r *= 2; return r; }

void hanoi3(int count, int offset, int src, int dst, int aux) {
    if (count == 0) return;
    hanoi3(count - 1, offset, src, aux, dst);
    move_count++;
    printf("Move disk %d: peg %d -> peg %d\n", offset + count - 1, src, dst);
    hanoi3(count - 1, offset, aux, dst, src);
}

void frame_stewart(int n, int offset, int src, int dst, int spare1, int spare2) {
    if (n == 0) return;
    if (n == 1) {
        move_count++;
        printf("Move disk %d: peg %d -> peg %d\n", offset, src, dst);
        return;
    }
    int k = split[n];
    frame_stewart(k, offset, src, spare1, dst, spare2);
    hanoi3(n - k, offset + k, src, dst, spare2);
    frame_stewart(k, offset, spare1, dst, src, spare2);
}

int main(void) {
    int n;
    printf("Enter number of disks n: ");
    if (scanf("%d", &n) != 1 || n < 1) return 1;

    FS = calloc(n + 1, sizeof(long long));
    split = calloc(n + 1, sizeof(int));
    FS[0] = 0;
    for (int m = 1; m <= n; m++) {
        long long best = LLONG_MAX;
        int bestk = 1;
        for (int k = 1; k < m; k++) {
            long long cand = 2 * FS[k] + pow2(m - k) - 1;
            if (cand < best) { best = cand; bestk = k; }
        }
        if (m == 1) { best = 1; bestk = 0; }
        FS[m] = best;
        split[m] = bestk;
    }

    printf("Minimum moves for n=%d disks (4 pegs): %lld\n\n", n, FS[n]);

    move_count = 0;
    frame_stewart(n, 1, 0, 3, 1, 2);
    printf("\nTotal moves: %lld\n", move_count);

    free(FS); free(split);
    return 0;
}
