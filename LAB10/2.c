
#include <stdio.h>
#define N 1000005

int p[N], sz[N], active[N];
int R, C;

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return 0;

    if (sz[a] < sz[b]) {
        int t = a; a = b; b = t;
    }
    p[b] = a;
    sz[a] += sz[b];
    return 1;
}

int main() {
    int k, r, c, count = 0;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    scanf("%d%d%d", &R, &C, &k);

    for (int i = 0; i < k; i++) {
        printf("Enter land cell (row column): ");
        scanf("%d%d", &r, &c);

        int x = (r - 1) * C + c - 1;

        if (!active[x]) {
            active[x] = 1;
            p[x] = x;
            sz[x] = 1;
            count++;

            for (int j = 0; j < 4; j++) {
                int nr = r + dr[j], nc = c + dc[j];
                if (nr >= 1 && nr <= R &&
                    nc >= 1 && nc <= C) {
                    int y = (nr - 1) * C + nc - 1;
                    if (active[y] && unite(x, y))
                        count--;
                }
            }
        }
        printf("Islands: %d\n", count);
    }
    return 0;
}
