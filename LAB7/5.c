#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int n;
    printf("Enter n (n > 1): ");
    if (scanf("%d", &n) != 1 || n <= 1) return 1;

    int shots_count, idx = 0;
    int *shots;
    if (n == 2) {
        shots_count = 2;
        shots = malloc(shots_count * sizeof(int));
        shots[idx++] = 1;
        shots[idx++] = 1;
    } else {
        shots_count = 2 * (n - 2);
        shots = malloc((shots_count + 1) * sizeof(int));
        for (int i = 2; i <= n - 1; i++) shots[idx++] = i;
        for (int i = n - 1; i >= 2; i--) shots[idx++] = i;
    }

    printf("Shot sequence (%d shots): ", shots_count);
    for (int i = 0; i < shots_count; i++) printf("%d ", shots[i]);
    printf("\n\n");

    int *possible = malloc((n + 2) * sizeof(int));
    int all_ok = 1;

    for (int start = 1; start <= n; start++) {
        memset(possible, 0, (n + 2) * sizeof(int));
        possible[start] = 1;

        for (int s = 0; s < shots_count; s++) {
            possible[shots[s]] = 0;
            int remaining = 0;
            for (int p = 1; p <= n; p++) if (possible[p]) remaining++;
            if (remaining == 0) break;

            int *next_possible = calloc(n + 2, sizeof(int));
            for (int p = 1; p <= n; p++) {
                if (possible[p]) {
                    if (p - 1 >= 1) next_possible[p - 1] = 1;
                    if (p + 1 <= n) next_possible[p + 1] = 1;
                }
            }
            memcpy(possible, next_possible, (n + 2) * sizeof(int));
            free(next_possible);
        }

        int escaped = 0;
        for (int p = 1; p <= n; p++) if (possible[p]) escaped++;
        if (escaped > 0) {
            all_ok = 0;
            printf("Start %d: NOT caught!\n", start);
        }
    }

    printf(all_ok ? "Validation PASSED: every start guaranteed caught.\n"
                  : "Validation FAILED.\n");

    free(shots);
    free(possible);
    return 0;
}
