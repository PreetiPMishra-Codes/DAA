#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max_int(int a, int b) { return a > b ? a : b; }

int **egg_drop_dp(int E, int F) {
    int **dp = malloc((E + 1) * sizeof(int *));
    for (int e = 0; e <= E; e++) dp[e] = calloc(F + 1, sizeof(int));

    for (int f = 0; f <= F; f++) dp[1][f] = f;
    for (int e = 0; e <= E; e++) dp[e][0] = 0;
    for (int e = 0; e <= E; e++) if (F >= 1) dp[e][1] = 1;

    for (int e = 2; e <= E; e++) {
        for (int f = 2; f <= F; f++) {
            int best = INT_MAX;
            for (int x = 1; x <= f; x++) {
                int worst = 1 + max_int(dp[e - 1][x - 1], dp[e][f - x]);
                if (worst < best) best = worst;
            }
            dp[e][f] = best;
        }
    }
    return dp;
}

int main(void) {
    int E, F;
    printf("Enter E and F: ");
    if (scanf("%d %d", &E, &F) != 2 || E < 1 || F < 0) return 1;

    int **dp = egg_drop_dp(E, F);
    printf("Minimum trials for E=%d, F=%d: %d\n", E, F, dp[E][F]);

    if (E == 2) {
        int t = 0;
        while (t * (t + 1) / 2 < F) t++;
        printf("Closed-form check (2 eggs): %d\n", t);
    }

    for (int e = 0; e <= E; e++) free(dp[e]);
    free(dp);
    return 0;
}
