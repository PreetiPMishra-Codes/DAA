
#include <stdio.h>
#define N 100005

int p[N], xr[N];

int find(int x) {
    if (p[x] == x) return x;
    int par = p[x];
    p[x] = find(par);
    xr[x] ^= xr[par];
    return p[x];
}

int main() {
    int V, E, u, v;
    scanf("%d%d", &V, &E);

    for (int i = 1; i <= V; i++) p[i] = i;

    for (int i = 0; i < E; i++) {
        printf("Enter edge (u v): ");
        scanf("%d%d", &u, &v);

        int a = find(u), b = find(v);
        int pu = xr[u], pv = xr[v];

        if (a == b) {
            if ((pu ^ pv) != 1)
                printf("Edge rejected: not bipartite\n");
            else
                printf("Edge accepted\n");
        } else {
            p[a] = b;
            xr[a] = pu ^ pv ^ 1;
            printf("Edge accepted\n");
        }
    }
    return 0;
}
