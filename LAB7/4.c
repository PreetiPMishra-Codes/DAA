#include <stdio.h>
#include <stdlib.h>

int is_legal(unsigned mask, int i) {
    if (i == 1) return 1;
    if (!((mask >> (i - 2)) & 1)) return 0;
    for (int j = 1; j <= i - 2; j++)
        if ((mask >> (j - 1)) & 1) return 0;
    return 1;
}

int main(void) {
    int n;
    printf("Enter number of switches n: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 22) return 1;

    unsigned N = 1u << n;
    unsigned all_on = N - 1, all_off = 0;

    int *dist = malloc(N * sizeof(int));
    int *parent_state = malloc(N * sizeof(int));
    int *parent_move = malloc(N * sizeof(int));
    unsigned *queue = malloc(N * sizeof(unsigned));
    for (unsigned s = 0; s < N; s++) dist[s] = -1;

    int head = 0, tail = 0;
    dist[all_on] = 0;
    queue[tail++] = all_on;

    while (head < tail) {
        unsigned s = queue[head++];
        if (s == all_off) break;
        for (int i = 1; i <= n; i++) {
            if (is_legal(s, i)) {
                unsigned t = s ^ (1u << (i - 1));
                if (dist[t] == -1) {
                    dist[t] = dist[s] + 1;
                    parent_state[t] = s;
                    parent_move[t] = i;
                    queue[tail++] = t;
                }
            }
        }
    }

    printf("Minimum moves: %d\n\n", dist[all_off]);

    int *moves = malloc((dist[all_off] + 1) * sizeof(int));
    int m = dist[all_off];
    unsigned cur = all_off;
    while (cur != all_on) {
        moves[--m] = parent_move[cur];
        cur = parent_state[cur];
    }

    unsigned state = all_on;
    for (int k = 0; k < dist[all_off]; k++) {
        int sw = moves[k];
        state ^= (1u << (sw - 1));
        printf("Move %d: toggle switch %d -> %s\n", k + 1, sw, ((state >> (sw - 1)) & 1) ? "ON" : "OFF");
    }

    free(dist); free(parent_state); free(parent_move); free(queue); free(moves);
    return 0;
}
