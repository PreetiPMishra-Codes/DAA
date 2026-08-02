#include <stdio.h>

long long moves = 0;

void toh(int n, char src, char dst, char aux) {
    if (n == 0) return;
    toh(n - 1, src, aux, dst);
    moves++;
    toh(n - 1, aux, dst, src);
}

int main() {
    printf("N\tsimulated Moves\ttheoretical (2^n - 1)\n");
    for (int n = 1; n <= 10; n++) {
        moves = 0;
        toh(n, 'A', 'C', 'B');
        printf("%d\t%lld\t\t%lld\n", n, moves, (1LL << n) - 1);
    }
    return 0;
}
