
#include <stdio.h>
#define N 100005

int p[N], sz[N], active[N], order[N];
long long w[N], sum[N], ans[N];

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;

    if (sz[a] < sz[b]) {
        int t = a; a = b; b = t;
    }
    p[b] = a;
    sz[a] += sz[b];
    sum[a] += sum[b];
}

int main() {
    int n, m, u, v;
    int eu[N], ev[N];

    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        printf("Enter weight of vertex %d: ", i);
        scanf("%lld", &w[i]);
        p[i] = i;
    }

    for (int i = 0; i < m; i++) {
        printf("Enter edge (u v): ");
        scanf("%d%d", &eu[i], &ev[i]);
    }

    for (int i = 1; i <= n; i++) {
        printf("Enter deletion vertex %d: ", i);
        scanf("%d", &order[i]);
    }

    ans[n] = 0;

    for (int i = n; i >= 1; i--) {
        int x = order[i];
        active[x] = 1;
        sz[x] = 1;
        sum[x] = w[x];

        for (int j = 0; j < m; j++) {
            u = eu[j];
            v = ev[j];
            if (active[u] && active[v])
                unite(u, v);
        }

        long long best = sum[find(x)];
        for (int j = 1; j <= n; j++)
            if (active[j] && find(j) == j &&
                sum[j] > best)
                best = sum[j];

        ans[i - 1] = best;
    }

    for (int i = 1; i <= n; i++)
        printf("After deletion %d: %lld\n", i, ans[i]);

    return 0;
}
