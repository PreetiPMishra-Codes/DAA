#include <stdio.h>
#include <stdlib.h>

typedef struct { int r, c; } Coin;

long long min_moves(int n) {
    long long coins = (long long)n * (n + 1) / 2;
    return coins / 3;
}

void build_upward(int n, Coin *arr, int *count) {
    int k = 0;
    for (int r = 0; r < n; r++)
        for (int c = 0; c <= r; c++)
            arr[k++] = (Coin){r, c};
    *count = k;
}

void build_downward(int n, Coin *arr, int *count) {
    int k = 0;
    for (int r = 0; r < n; r++)
        for (int c = 0; c <= r; c++)
            arr[k++] = (Coin){n - 1 - r, r - c};
    *count = k;
}

int coin_in_set(Coin x, Coin *set, int n) {
    for (int i = 0; i < n; i++)
        if (set[i].r == x.r && set[i].c == x.c) return 1;
    return 0;
}

int main(void) {
    int n;
    printf("Enter number of rows n: ");
    if (scanf("%d", &n) != 1 || n < 1) return 1;

    long long coins = (long long)n * (n + 1) / 2;
    printf("Coins: %lld\n", coins);
    printf("Minimum moves: %lld\n\n", min_moves(n));

    Coin *up = malloc(coins * sizeof(Coin));
    Coin *down = malloc(coins * sizeof(Coin));
    int cu, cd;
    build_upward(n, up, &cu);
    build_downward(n, down, &cd);

    int moves_shown = 0;
    for (int i = 0; i < cu; i++) {
        if (!coin_in_set(up[i], down, cd)) {
            for (int j = 0; j < cd; j++) {
                if (down[j].r != -1 && !coin_in_set(down[j], up, cu)) {
                    printf("coin (%d,%d) -> (%d,%d)\n", up[i].r, up[i].c, down[j].r, down[j].c);
                    down[j] = (Coin){-1, -1};
                    moves_shown++;
                    break;
                }
            }
        }
    }
    printf("\nCoins relocated: %d\n", moves_shown);

    free(up); free(down);
    return 0;
}
